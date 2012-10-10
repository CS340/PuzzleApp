#include "mainwindow.h"

#include <QApplication>
#include<QLabel>
#include<QPixmap>
#include<QImage>
#include<QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //set up main window
    MainWindow mainWindow;
    mainWindow.setOrientation(MainWindow::ScreenOrientationLockPortrait);
    mainWindow.showExpanded();

    QDesktopWidget *desktop = QApplication::desktop();
    int screenWidth = desktop->width();
    //int screenHeight = desktop->height();

    QLabel *imageLabel = new QLabel(&mainWindow);
    QImage elephant(":/elephant.gif");

    elephant = elephant.scaledToWidth(screenWidth);

    imageLabel->setPixmap(QPixmap::fromImage(elephant));
    imageLabel->resize(elephant.width(), elephant.height());
    imageLabel->show();

    return app.exec();
}
