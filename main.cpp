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


    int grid = 5;
    QGraphicsItem *item[grid][grid];

    //cut image into tiles and position them
    for(int i = 0; i < grid; i++)
    {
        for(int j = 0; j < grid; j++)
        {
           item[i][j] = gScene->addPixmap(QPixmap::fromImage(elephant.copy(i*(eWidth/grid), j*(eHeight/grid), eWidth/grid, eHeight/grid)));
           item[i][j]->setPos(eWidth/grid *i, eHeight/grid *j);
           item[i][j]->setScale(0.99);
        }
    }


    gView->show();
    return app.exec();
}
