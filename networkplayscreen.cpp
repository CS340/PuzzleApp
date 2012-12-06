//AUTHORS: Anthony Phelps

#include "networkplayscreen.h"
#include "tile.h"
#include "win_menu.h"
#include "mainmenu.h"

#include <QLabel>
#include <QImageReader>
#include <QGridLayout>
#include <QGraphicsView>
#include <QTimer>
#include <math.h>
#include <QDebug>

// the networkplayScreen is the screen for the multi-player game.
// it takes in the file path to the image the user wants to use
// and cuts it up into tiles and displays them on the screen with various
// menu buttons and statistics. It also handles tile clicks and tile swapping.
// It is nearly identical to the single player screen except it sends and recives
// player actions over the network

NetworkPlayScreen::NetworkPlayScreen(QString imgPath, MainWindow *mainWindow, QWidget *parent) : QWidget(parent)
{
    this->imgPath = imgPath;
    this->mainWindow = mainWindow;

    socket = new QTcpSocket(this);
    socket->setSocketOption(QAbstractSocket::KeepAliveOption, 1);

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));

}

//create all sub-widgets and display everything
void NetworkPlayScreen::display(int screenWidth, int screenHeight, int gridSize)
{
    makeCon();;
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    grid = gridSize;
    numMoves = 0;
    seconds = 0;
    percentComplete = grid*grid;
    QFont font("Helvectica", 13);

    //set up scene and view
    QGraphicsScene *gScene = new QGraphicsScene(this);
    gView = new QGraphicsView(gScene);
    gView->setFixedSize(screenWidth, screenHeight);
    gScene->setBackgroundBrush(Qt::black);

    //set up all GridLayouts
    layout = new QGridLayout(gView);
    playGrid = new QGridLayout();
    menuGrid = new QGridLayout();
    layout->setContentsMargins(0,0,0,0);
    playGrid->setContentsMargins(0,0,0,0);
    menuGrid->setContentsMargins(0,0,0,0);
    gView->setLayout(layout);
    layout->addLayout(playGrid, 0, 0);
    layout->addLayout(menuGrid, 1, 0);

    //timer and move labels
    movesLabel = new QLabel("Moves: " + QString::number(numMoves));
    timerLabel = new QLabel("Time: 0:0");
    percentLabel = new QLabel("Percent: 0%");
    opMovesLabel = new QLabel("0");
    opPercentLabel = new QLabel("0%");

    menuGrid->addWidget(timerLabel,0,0,2,0, Qt::AlignHCenter);
    menuGrid->addWidget(new QLabel("Yours"),1,0, Qt::AlignHCenter);
    menuGrid->addWidget(new QLabel("Opponents"),1,1, Qt::AlignHCenter);
    menuGrid->addWidget(movesLabel,2,0);
    menuGrid->addWidget(percentLabel,3,0);
    menuGrid->addWidget(opMovesLabel, 2,1, Qt::AlignHCenter);
    menuGrid->addWidget(opPercentLabel, 3,1, Qt::AlignHCenter);
    movesLabel->setFont(font);
    timerLabel->setFont(font);
    percentLabel->setFont(font);
    opPercentLabel->setFont(font);
    opMovesLabel->setFont(font);

    //menu buttons
    QPushButton *mainMenuButton = new QPushButton("DEBUG WIN");
    QPushButton *giveUpButton = new QPushButton("Give Up");
    menuGrid->addWidget(mainMenuButton, 4, 0);
    menuGrid->addWidget(giveUpButton, 4, 1);
    mainMenuButton->setFont(font);
    giveUpButton->setFont(font);
    connect(mainMenuButton, SIGNAL(clicked()), this, SLOT(mainMenuButtonClicked()));
    connect(giveUpButton, SIGNAL(clicked()), this, SLOT(giveUpButtonClicked()));

    //import image
    QImageReader reader(imgPath);
    reader.setScaledSize(QSize(screenWidth, screenWidth));
    QImage image = reader.read();
    int eHeight = image.height();
    int eWidth = image.width();

    //cut image into tiles and position them
    for(int i = 0; i < grid; i++){
        for(int j = 0; j < grid; j++){
            if(!(i==grid-1 && j==grid-1)){
                QPixmap pixmap = QPixmap::fromImage(image.copy(i*(eWidth/grid), j*(eHeight/grid), eWidth/grid, eHeight/grid));
                QIcon icon(pixmap);
                Tile *button = new Tile(i, j, icon);
                button->setIconSize(QSize(eWidth/grid, eHeight/grid));

                playGrid->addWidget(button, j, i);
                connect(button, SIGNAL(tileClicked(Tile*)), this, SLOT(handleTileClick(Tile*)));
            }
        }
    }

    //make hidden tile
    reader.setFileName(":/black.png");
    QIcon black(QPixmap::fromImage(reader.read()));
    hiddenTile = new Tile(grid-1, grid-1, black);
    hiddenTile->setIconSize(QSize(eWidth/grid, eHeight/grid));
    playGrid->addWidget(hiddenTile, grid-1, grid-1);

    //grid sizing
    for(int i=0; i<layout->columnCount(); i++)
        layout->setColumnMinimumWidth(i, screenWidth);
    layout->setRowMinimumHeight(1, screenHeight-screenWidth);
    for(int i=0; i<playGrid->rowCount(); i++){
        playGrid->setColumnMinimumWidth(i, screenWidth/grid);
        playGrid->setRowMinimumHeight(i, screenWidth/grid);
    }

    shuffle();

    //checks if the shuffle resulted in a winning board
    if(percentComplete == grid*grid)
    {
        playerWin();
    }

    //create and set up the timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    percentLabel->setText("Percent: " + QString::number(calculatePercent()) + "%");

    gView->show();
}

//calculate the percent of the puzzle that is complete
int NetworkPlayScreen::calculatePercent()
{
    if(percentComplete == 0)
    {
        return 0;
    }
    return (int)(100.00 * ((float)percentComplete/(float)(grid*grid))) + 1;
}

//shuffles the tiles into random positions
void NetworkPlayScreen::shuffle()
{
    for(int i = 0; i < grid; i++)
    {
        for(int j = 0; j < grid; j++)
        {
            if(!(i == grid - 1 && j == grid - 1))
            {
                int a = grid - 1;
                int b = grid - 1;

                while(a == grid - 1 && grid - 1)
                {
                    a = rand() % grid;
                    b = rand() % grid;
                }

                Tile *g = dynamic_cast<Tile*>(playGrid->itemAtPosition(i,j)->widget());
                Tile *h = dynamic_cast<Tile*>(playGrid->itemAtPosition(a,b)->widget());

                swapTiles(g,h);
            }
        }
    }
}

//swaps the positions of two tiles
void NetworkPlayScreen::swapTiles(Tile *tile1, Tile *tile2){
    playGrid->removeWidget(tile1);
    playGrid->removeWidget(tile2);

    int x1start = tile1->getX();
    int y1start = tile1->getY();
    int x2start = tile2->getX();
    int y2start = tile2->getY();

    //swap the tiles
    playGrid->addWidget(tile1, y2start, x2start);
    playGrid->addWidget(tile2, y1start, x1start);

    tile1->setX(x2start);
    tile1->setY(y2start);
    tile2->setX(x1start);
    tile2->setY(y1start);

    //update the stats for tiles in the correct positions
    if(x1start == tile1->getInitX() && y1start == tile1->getInitY())
    {
        percentComplete--;
    }
    if(x2start == tile1->getInitX() && y2start == tile1->getInitY())
    {
        percentComplete++;
    }

    if(x2start == tile2->getInitX() && y2start == tile2->getInitY())
    {
        percentComplete--;
    }
    if(x1start == tile2->getInitX() && y1start == tile2->getInitY())
    {
        percentComplete++;
    }

    //checks if the player won
    if(calculatePercent() == 100)
    {
        playerWin();
    }
}

//update the timer
void NetworkPlayScreen::update()
{
    int minutes = (++seconds) / 60;
    timerLabel->setText("Time: " + QString::number(minutes) + ":" + QString::number(seconds-(minutes*60)));
}

//checks if the tile is next to the blank tile and swaps them if it is. Alerts opponent that player moved a tile.
void NetworkPlayScreen::handleTileClick(Tile* t)
{
    if((t->getX()-1 == hiddenTile->getX() && t->getY() == hiddenTile->getY()) || (t->getX() == hiddenTile->getX() && t->getY()-1 == hiddenTile->getY()) || (t->getX()+1 == hiddenTile->getX() && t->getY() == hiddenTile->getY()) || (t->getX() == hiddenTile->getX() && t->getY()+1 == hiddenTile->getY()))
    {
        if(timer->isActive())
        {

            swapTiles(t, hiddenTile);
            movesLabel->setText("Moves: " + QString::number(++numMoves));
            percentLabel->setText("Percent: " + QString::number(calculatePercent()) + "%");
            qDebug() << (int)(10000 - ((log(seconds)-log(1))/(log(1000)-log(1)) + (log(numMoves)-log(1))/(log(1000)-log(1)))*1000);
            socket->write((QString("move:") + mainWindow->getUserName() + ":" + gameName + ":" + QString::number(calculatePercent()) + ":" + QString::number(numMoves)).toUtf8());
        }
    }
}
//DEBUG PURPOSES ONLY! displays the win menu so we don't have to solve the puzzle in our presentation.
void NetworkPlayScreen::mainMenuButtonClicked()
{
    qDebug() << "main menu button clicked.";
    socket->write(QString("finished:" + mainWindow->getUserName() + ":" + gameName + ":" + QString::number(seconds) + ":" + QString::number(numMoves)).toUtf8());
    win_menu *wm = new win_menu(mainWindow, mainWindow);
    wm->display(screenWidth, screenHeight);
}

//takes the user back to the main menu. Alerts opponent that this player quit.
void NetworkPlayScreen::giveUpButtonClicked()
{
    socket->write(QString("quit:" + mainWindow->getUserName() + ":" + gameName).toUtf8());
    MainMenu *mm = new MainMenu(mainWindow, mainWindow);
    mm->display(screenWidth, screenHeight);
    mm->raise();
}

//called if the winning conditions are met. creates a win menu. Alerts opponent that this user has won.
void NetworkPlayScreen::playerWin()
{
    qDebug() << "player won.";
    socket->write(QString("finished:" + mainWindow->getUserName() + ":" + gameName + ":" + QString::number(seconds) + ":" + QString::number(numMoves)).toUtf8());
    win_menu *wm = new win_menu(mainWindow, mainWindow);
    wm->display(screenWidth, screenHeight);
}

//Initializes socket connection
void NetworkPlayScreen::makeCon()
{
    qDebug() << "Connecting...";
    socket->connectToHost("ganymede.sytes.net", 4849);

    if(!socket->waitForConnected(1000))
    {
        qDebug() << "ERROR: " << socket->errorString();
    }
}

//Parses server messages and acts upon them
QString NetworkPlayScreen::parseResponse(QString s)
{
    QStringList parts = s.split(":");
    QString result;
    //Game partner assigned
    if(parts[0] == "partner")
    {
        partner = parts[1];
        gameName = parts[2];
        timer->start(1000);
    }
    //Oppenent made a move
    else if (parts[0] == "move")
    {
        qDebug() << parts[2] << "::" << parts[3];
        opMovesLabel->setText(parts[3]);
        opPercentLabel->setText(parts[2] + QString("%"));
    }
    //Opponent won
    else if (parts[0] == "finished")
    {
        qDebug() << "finished";
        timer->stop();
        opMovesLabel->setText("You");
        opPercentLabel->setText("lose");
        movesLabel->setText("You");
        percentLabel->setText("lose");
    }
    //opponent gave up
    else if (parts[0] == "quit")
    {
        qDebug() << "Quit";
        timer->stop();
        opMovesLabel->setText("Opponent");
        opPercentLabel->setText("Quit");
        movesLabel->setText("Opponent");
        percentLabel->setText("Quit");
    }
    return result;
}

//tells server players name
void NetworkPlayScreen::connected()
{
    qDebug() << "Connected";
    socket->write((QString("new:") + mainWindow->getUserName()).toUtf8());

}

//run when connection disconnects. Here for debugging only
void NetworkPlayScreen::disconnected()
{
    qDebug() << "Disconnected";
}

//run when bytes are written over the socket. Here for debugging only.
void NetworkPlayScreen::bytesWritten(qint64 bytes)
{
    qDebug() << "Wrote Something: " << bytes << "bytes";
}

//indicates socket is ready to be written to. Does so.
void NetworkPlayScreen::readyRead()
{
    qDebug() << "Reading...";
    parseResponse(socket->readLine(1024));
}
