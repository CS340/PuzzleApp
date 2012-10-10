#include "mainwindow.h"

#include <QApplication>
#include<QLabel>
#include<QPixmap>
#include<QImage>
#include<QDesktopWidget>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QGraphicsPixmapItem>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //set up main window
    QDesktopWidget *desktop = QApplication::desktop();
    int screenWidth = desktop->width();
    int screenHeight = desktop->height();
    MainWindow mainWindow;
    mainWindow.setOrientation(MainWindow::ScreenOrientationLockPortrait);
    mainWindow.resize(screenWidth, screenHeight);
    mainWindow.showExpanded();

    //set up scene and view
    QGraphicsScene *gScene = new QGraphicsScene(&mainWindow);
    QGraphicsView *gView = new QGraphicsView(gScene);
    gScene->setBackgroundBrush(Qt::black);

    //import and resize image
    QImage elephant(":/elephant.gif");
    elephant = elephant.scaledToWidth(screenWidth);
    int eWidth = elephant.width();
    int eHeight = elephant.height();

    //gScene->addPixmap(QPixmap::fromImage(elephant));

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
    return app.exec();
}
