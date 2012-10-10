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

    //QLabel *imageLabel = new QLabel(&mainWindow);
    QImage elephant(":/elephant.gif");

    elephant = elephant.scaledToWidth(screenWidth);
    int eWidth = elephant.width();
    int eHeight = elephant.height();

    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            QLabel *imageLabel = new QLabel(&mainWindow);
            imageLabel->setPixmap(QPixmap::fromImage(elephant.copy(i*(eWidth/5), j*(eHeight/5), (i+1)*(eWidth/5), (j+1)*(eHeight/5))));
            imageLabel->resize(eWidth, eHeight);
            imageLabel->show();
        }
    }

    //imageLabel->setPixmap(QPixmap::fromImage(elephant));
   // imageLabel->resize(elephant.width(), elephant.height());
   // imageLabel->show();

    return app.exec();
}
