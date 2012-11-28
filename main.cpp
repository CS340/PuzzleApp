#include "mainwindow.h"
#include "mainmenu.h"
#include "win_menu.h"
#include "gridsizescreen.h"
#include "usernamescreen.h"

#include <QApplication>
#include<QDesktopWidget>

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

//    MainMenu *mm = new MainMenu(&mainWindow, &mainWindow);
//    mm->display(screenWidth, screenHeight);

    UsernameScreen *uns = new UsernameScreen(&mainWindow);
    uns->display(screenWidth, screenHeight);

    return app.exec();
}
