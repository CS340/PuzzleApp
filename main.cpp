//AUTHORS: Matt Dumford, Anthony Phelps

#include "mainwindow.h"
#include "mainmenu.h"
#include "win_menu.h"
#include "gridsizescreen.h"
#include "usernamescreen.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //set up width and height
    QDesktopWidget *desktop = QApplication::desktop();
    int screenWidth = desktop->width();
    int screenHeight = desktop->height();

    //create main window
    MainWindow mainWindow;
    mainWindow.setOrientation(MainWindow::ScreenOrientationLockPortrait);
    mainWindow.resize(screenWidth, screenHeight);
    mainWindow.showExpanded();

    //check if there is already a username
    //open directory to pictures folder
    QDir dir  = QDir(QDir::rootPath());
    dir.cd("sdcard");
    if(!dir.entryList().contains("Puzzle Pictures"))
        dir.mkdir("Puzzle Pictures");
    dir.cd("Puzzle Pictures");

    //get list of files in pictures folder
    QStringList files = dir.entryList();

    //if there is already a username, give it to the main window and create a main menu
    if(files.contains("user.name"))
    {
        QFile file(dir.absolutePath() + "/user.name");
        QStringList strings;
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            while (!in.atEnd()) {
                strings += in.readLine().split(";");
            }
        }

        mainWindow.setUserName(strings.at(0));
        qDebug() << mainWindow.getUserName();

        MainMenu *mm = new MainMenu(&mainWindow, &mainWindow);
        mm->display(screenWidth, screenHeight);
    }

    //if there is no username, make a username screen and get one
    else
    {
        UsernameScreen *uns = new UsernameScreen(&mainWindow, &mainWindow);
        uns->display(screenWidth, screenHeight);
    }





    return app.exec();
}
