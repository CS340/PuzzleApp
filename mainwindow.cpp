#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tile.h"

#include <QLabel>
#include <QImageReader>
#include <QGridLayout>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    numMoves = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::display(int screenWidth, int screenHeight)
{
    int grid = 5;

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

    movesLabel = new QLabel(QString::number(numMoves));
    menuGrid->addWidget(movesLabel,0,0,1,1);


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


    shuffle(grid);
    qDebug("Shuffled");
    gView->show();
    qDebug("MAIN_WINDOW");
}

void MainWindow::shuffle(int grid)
{
    for(int i = 0; i < grid - 1; i++)
    {
        for(int j = 0; j < grid - 1; j++)
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

void MainWindow::swapTiles(Tile *tile1, Tile *tile2){
    playGrid->removeWidget(tile1);
    playGrid->removeWidget(tile2);

    playGrid->addWidget(tile1, tile2->getY(), tile2->getX());
    playGrid->addWidget(tile2, tile1->getY(), tile1->getX());

    int tmpx = tile1->getX();
    int tmpy = tile1->getY();

    tile1->setX(tile2->getX());
    tile1->setY(tile2->getY());
    tile2->setX(tmpx);
    tile2->setY(tmpy);
}


void MainWindow::handleTileClick(Tile* t)
{
    qDebug("MAIN_WINDOW_TILE_CLICK");
    if((t->getX()-1 == hiddenTile->getX() && t->getY() == hiddenTile->getY()) || (t->getX() == hiddenTile->getX() && t->getY()-1 == hiddenTile->getY()) || (t->getX()+1 == hiddenTile->getX() && t->getY() == hiddenTile->getY()) || (t->getX() == hiddenTile->getX() && t->getY()+1 == hiddenTile->getY()))
    {
        qDebug("BEFORE :: T:(%d, %d) H:(%d,%d)", t->getX(), t->getY(), hiddenTile->getX(), hiddenTile->getY());
        swapTiles(t, hiddenTile);
        qDebug("AFTER :: T:(%d, %d) H:(%d,%d)", t->getX(), t->getY(), hiddenTile->getX(), hiddenTile->getY());
        movesLabel->setText(QString::number(++numMoves));
    }
}


void MainWindow::setOrientation(ScreenOrientation orientation)
{
    Qt::WidgetAttribute attribute;
    switch (orientation) {
#if QT_VERSION < 0x040702
    // Qt < 4.7.2 does not yet have the Qt::WA_*Orientation attributes
    case ScreenOrientationLockPortrait:
        attribute = static_cast<Qt::WidgetAttribute>(128);
        break;
    case ScreenOrientationLockLandscape:
        attribute = static_cast<Qt::WidgetAttribute>(129);
        break;
    default:
    case ScreenOrientationAuto:
        attribute = static_cast<Qt::WidgetAttribute>(130);
        break;
#else // QT_VERSION < 0x040702
    case ScreenOrientationLockPortrait:
        attribute = Qt::WA_LockPortraitOrientation;
        break;
    case ScreenOrientationLockLandscape:
        attribute = Qt::WA_LockLandscapeOrientation;
        break;
    default:
    case ScreenOrientationAuto:
        attribute = Qt::WA_AutoOrientation;
        break;
#endif // QT_VERSION < 0x040702
    };
    setAttribute(attribute, true);
}

void MainWindow::showExpanded()
{
#if defined(Q_WS_SIMULATOR)
    showFullScreen();
#elif defined(Q_WS_MAEMO_5)
    showMaximized();
#else
    show();
#endif
}
