#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tile.h"

#include <QLabel>
#include <QImageReader>
#include <QGridLayout>
#include <QGraphicsView>

QLabel *label;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    label = new QLabel();
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
                connect(button, SIGNAL(Tile::tileClicked(Tile*)), this, SLOT(handleTileClick(Tile*)));
            }
        }
    }

    //make hidden tile
    reader.setFileName(":/black.png");
    QIcon black(QPixmap::fromImage(reader.read()));
    Tile *hiddenTile = new Tile(grid-1, grid-1, black);
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

    swapTiles(0,0,4,4);

    qDebug("MAIN_WINDOW");

    gView->show();
}

/*int *MainWindow::findHiddenTile(int x, int y, int hiddenX, int hiddenY)
{
    int *ans = new int[2];
    if(buttons[x+1][y] == 0){
        ans[0] = x+1;
        ans[1] = y;
    }
    else{
        ans[0] = -1;
        ans[1] = -1;
    }


    return ans;
}*/


void MainWindow::swapTiles(int x1, int y1, int x2, int y2){
    QWidget *tile1 = playGrid->itemAtPosition(y1, x1)->widget();
    QWidget *tile2 = playGrid->itemAtPosition(y2, x2)->widget();

    playGrid->removeWidget(tile1);
    playGrid->removeWidget(tile2);

    playGrid->addWidget(tile1, y2, x2);
    playGrid->addWidget(tile2, y1, x1);
}


void MainWindow::handleTileClick(Tile* t)
{
    qDebug("MAIN_WINDOW_TILE_CLICK");
    label->setText("(LABEL)");
    menuGrid->addWidget(label, 0,0);
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
