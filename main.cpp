#include "mainwindow.h"

#include <QApplication>
//#include<QLabel>
//#include<QPixmap>
//#include<QImage>
#include<QDesktopWidget>
//#include<QGraphicsScene>
//#include<QGraphicsView>
//#include<QGraphicsPixmapItem>
//#include<QImageReader>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //set up width and height
    QDesktopWidget *desktop = QApplication::desktop();
    int screenWidth = desktop->width();
    int screenHeight = desktop->height();

    MainWindow mainWindow;
    mainWindow.setOrientation(MainWindow::ScreenOrientationLockPortrait);
    mainWindow.resize(screenWidth, screenHeight);
    mainWindow.showExpanded();

    mainWindow.display(screenWidth, screenHeight);

    return app.exec();
}
