#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCoreApplication>
#include<QLabel>
#include<QPixmap>
#include<QImage>
#include<QDesktopWidget>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QGraphicsPixmapItem>
#include<QImageReader>

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
    //set up scene and view
    QGraphicsScene *gScene = new QGraphicsScene(this);
    QGraphicsView *gView = new QGraphicsView(gScene);
    gScene->setBackgroundBrush(Qt::black);

    //import image
    QImageReader reader(":/elephant.gif");
    reader.setScaledSize(QSize(screenWidth, screenWidth));
    QImage elephant = reader.read();
    int eWidth = elephant.height();
    int eHeight = elephant.width();



    //cut image into tiles and position them
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
           QGraphicsPixmapItem *item = gScene->addPixmap(QPixmap::fromImage(elephant.copy(i*(eWidth/5), j*(eHeight/5), eWidth/5, eHeight/5)));
           item->setPos(eWidth/5 *i, eHeight/5 *j);
           item->setScale(0.99);
        }
    }

    gView->show();
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
