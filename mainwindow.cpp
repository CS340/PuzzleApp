#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tile.h"

#include <QCoreApplication>
#include <QLabel>
#include <QPixmap>
#include <QImage>
#include <QDesktopWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QImageReader>
#include <QPushButton>
#include <QIcon>
#include <QMessageBox>
#include <QGridLayout>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
    QGridLayout *layout = new QGridLayout(gView);
    QGridLayout *playGrid = new QGridLayout();
    QGridLayout *menuGrid = new QGridLayout();
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

                //QObject::connect(buttons[i][j], SIGNAL(clicked()), gView, SLOT(handlebutton(buttons[i][j])));
            }
        }
    }

    for(int i=0; i<layout->columnCount(); i++)
        layout->setColumnMinimumWidth(i, screenWidth);

    layout->setRowMinimumHeight(1, screenHeight-screenWidth);

    for(int i=0; i<playGrid->rowCount(); i++){
        playGrid->setColumnMinimumWidth(i, screenWidth/grid);
        playGrid->setRowMinimumHeight(i, screenWidth/grid);
    }

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

void MainWindow::handlebutton(QPushButton *button)
{
    QMessageBox* msgBox = new QMessageBox();
    msgBox->setWindowTitle("Hello");
    button->setVisible(false);

    QLabel *label = new QLabel(this->gView);
    label->move(0,500);
    label->setText("buttons");
    label->show();
    this->update();
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
