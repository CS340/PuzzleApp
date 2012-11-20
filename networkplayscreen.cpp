#include "networkplayscreen.h"
#include "tile.h"
#include <QLabel>
#include <QImageReader>
#include <QGridLayout>
#include <QGraphicsView>
#include <QTimer>
#include <math.h>
#include <QDebug>

NetworkPlayScreen::NetworkPlayScreen(QWidget *parent) :
    QWidget(parent)
{

}

void NetworkPlayScreen::display(int screenWidth, int screenHeight)
{
    grid = 5;
    numMoves = 0;
    seconds = 0;
    percentComplete = grid*grid;

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
    menuGrid->addWidget(movesLabel,0,0);
    timerLabel = new QLabel("Time: 0:0");
    menuGrid->addWidget(timerLabel,0,1);
    percentLabel = new QLabel("Percent: 0%");
    menuGrid->addWidget(percentLabel,0,2);

    //import image
    QImageReader reader(":/elephant.gif");
    reader.setScaledSize(QSize(screenWidth, screenWidth));
    QImage elephant = reader.read();
    int eHeight = elephant.height();
    int eWidth = elephant.width();

    //cut image into tiles and position them
    for(int i = 0; i < grid; i++){
        for(int j = 0; j < grid; j++){
            if(!(i==grid-1 && j==grid-1)){
                QPixmap pixmap = QPixmap::fromImage(elephant.copy(i*(eWidth/grid), j*(eHeight/grid), eWidth/grid, eHeight/grid));
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
    if(percentComplete == grid*grid)
    {
        playerWin();
    }

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);

    percentLabel->setText("Percent Complete: " + QString::number(calculatePercent()) + "%");

    gView->show();
}

int NetworkPlayScreen::calculatePercent()
{
    /*int total = grid*grid;
    int inplace = 0;
    for(int i = 0; i < grid - 1; i++)
    {
        for(int j = 0; j < grid - 1; j++)
        {
            if(!(i == grid - 1 && j == grid - 1))
            {
                Tile *g = dynamic_cast<Tile*>(playGrid->itemAtPosition(i,j)->widget());
                if(g->getInitX() == i && g->getInitY() == j)
                {
                    inplace++;
                }
            }
        }
    }*/

    return (int)(100.00 * ((float)percentComplete/(float)(grid*grid)));
}

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

void NetworkPlayScreen::swapTiles(Tile *tile1, Tile *tile2){
    playGrid->removeWidget(tile1);
    playGrid->removeWidget(tile2);

    int x1start = tile1->getX();
    int y1start = tile1->getY();
    int x2start = tile2->getX();
    int y2start = tile2->getY();

    playGrid->addWidget(tile1, y2start, x2start);
    playGrid->addWidget(tile2, y1start, x1start);

    tile1->setX(x2start);
    tile1->setY(y2start);
    tile2->setX(x1start);
    tile2->setY(y1start);

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
}

void NetworkPlayScreen::update()
{
    int minutes = (++seconds) / 60;
    timerLabel->setText("Time: " + QString::number(minutes) + ":" + QString::number(seconds-(minutes*60)));
}

void NetworkPlayScreen::handleTileClick(Tile* t)
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

void NetworkPlayScreen::playerWin()
{

}
