#include "playscreen.h"
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

// the playScreen is the screen for the single player game.
// it takes in the file path to the image the user wants to use
// and cuts it up into tiles and displays them on the screen with various
// menu buttons and statistics. It also handles tile clicks and tile swapping.
PlayScreen::PlayScreen(QString imgPath, MainWindow *mainWindow, QWidget *parent) : QWidget(parent)
{
    this->imgPath = imgPath;
    this->mainWindow = mainWindow;
}

//create all sub-widgets and display everything
void PlayScreen::display(int screenWidth, int screenHeight, int gridSize)
{
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    grid = gridSize;
    numMoves = 0;
    seconds = 0;
    percentComplete = grid*grid;
    QFont font("Helvectica", 13);

    //set up scene and view
    QGraphicsScene *gScene = new QGraphicsScene(this);
    QGraphicsView *gView = new QGraphicsView(gScene);
    gView->setFixedSize(screenWidth, screenHeight);
    gScene->setBackgroundBrush(Qt::black);

    //set up all GridLayouts
    QGridLayout *layout = new QGridLayout(gView);
    playGrid = new QGridLayout();
    QGridLayout *menuGrid = new QGridLayout();
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
    menuGrid->addWidget(movesLabel,0,0);
    menuGrid->addWidget(timerLabel,1,0);
    menuGrid->addWidget(percentLabel,2,0);
    movesLabel->setFont(font);
    timerLabel->setFont(font);
    percentLabel->setFont(font);

    //menu buttons
    QPushButton *winButton = new QPushButton("DEBUG WIN");
    QPushButton *pauseButton = new QPushButton("Pause/Play");
    QPushButton *giveUpButton = new QPushButton("Give Up");
    menuGrid->addWidget(winButton, 0, 1);
    menuGrid->addWidget(pauseButton, 1, 1);
    menuGrid->addWidget(giveUpButton, 2, 1);
    winButton->setFont(font);
    pauseButton->setFont(font);
    giveUpButton->setFont(font);
    connect(winButton, SIGNAL(clicked()), this, SLOT(winButtonClicked()));
    connect(pauseButton, SIGNAL(clicked()), this, SLOT(pauseButtonClicked()));
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
    timer->start(1000);

    percentLabel->setText("Percent: " + QString::number(calculatePercent()) + "%");

    gView->show();
}

//calculate the percent of the puzzle that is complete
int PlayScreen::calculatePercent()
{
    if(percentComplete == 0)
    {
        return 0;
    }
    return (int)(100.00 * ((float)percentComplete/(float)(grid*grid))) + 1;
}

//shuffles the tiles into random positions
void PlayScreen::shuffle()
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
void PlayScreen::swapTiles(Tile *tile1, Tile *tile2)
{
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
    if(calculatePercent() >= 100)
        playerWin();
}

//update the timer
void PlayScreen::update()
{
    int minutes = (++seconds) / 60;
    timerLabel->setText("Time: " + QString::number(minutes) + ":" + QString::number(seconds-(minutes*60)));
}

//checks if the tile is next to the blank tile and swaps them if it is.
void PlayScreen::handleTileClick(Tile* t)
{
    if(timer->isActive())
    {
        if((t->getX()-1 == hiddenTile->getX() && t->getY() == hiddenTile->getY()) || (t->getX() == hiddenTile->getX() && t->getY()-1 == hiddenTile->getY()) || (t->getX()+1 == hiddenTile->getX() && t->getY() == hiddenTile->getY()) || (t->getX() == hiddenTile->getX() && t->getY()+1 == hiddenTile->getY()))
        {
            //qDebug("BEFORE :: T:(%d, %d) H:(%d,%d)", t->getX(), t->getY(), hiddenTile->getX(), hiddenTile->getY());
            swapTiles(t, hiddenTile);
            //qDebug("AFTER :: T:(%d, %d) H:(%d,%d)", t->getX(), t->getY(), hiddenTile->getX(), hiddenTile->getY());
            movesLabel->setText("Moves: " + QString::number(++numMoves));
            percentLabel->setText("Percent: " + QString::number(calculatePercent()) + "%");
            qDebug() << (int)(10000 - ((log(seconds)-log(1))/(log(1000)-log(1)) + (log(numMoves)-log(1))/(log(1000)-log(1)))*1000);
        }
    }
}

//DEBUG PURPOSES ONLY! displays the win menu so we don't have to solve the puzzle in our presentation.
void PlayScreen::winButtonClicked()
{
    qDebug() << "main menu button clicked.";
    win_menu *wm = new win_menu(mainWindow, mainWindow);
    wm->display(screenWidth, screenHeight);
}

//pauses the timer and prevents the user from moving tiles
void PlayScreen::pauseButtonClicked()
{
    qDebug() << "pause button clicked.";
    if(timer->isActive())
    {
        timer->stop();
    }
    else
    {
        timer->start();
    }
}

//takes the user back to the main menu
void PlayScreen::giveUpButtonClicked()
{
    MainMenu *mm = new MainMenu(mainWindow, mainWindow);
    mm->display(screenWidth, screenHeight);
    mm->raise();

}

//called if the winning conditions are met. creates a win menu
void PlayScreen::playerWin()
{
    qDebug() << "player won.";
    win_menu *wm = new win_menu(mainWindow, mainWindow);
    wm->display(screenWidth, screenHeight);
}
