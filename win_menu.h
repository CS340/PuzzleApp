#ifndef WIN_MENU_H
#define WIN_MENU_H

//AUTHORS: Alan Leung, Matt Dumford

#include"mainwindow.h"

#include <QObject>
#include <QGridLayout>
#include <QMovie>
#include <QLabel>

// the win menu is displayed when you win the game. It shows an animated .gif
// and has buttons to go back to the main menu and to quit the app.
class win_menu : public QWidget
{
    Q_OBJECT
public:
    explicit win_menu(MainWindow *mainWindow, QWidget *parent = 0);
    void display(int sw, int sh); //create all sub-widgets
    QGridLayout win_layout; //holds all sub-widgets

private:
    int screen_height, screen_width;
    MainWindow *mainWindow;

signals:
    
public slots:
    void mainMenuClicked(); //goes to main menu
    void quitClicked(); //exits the app
    
};

#endif // WIN_MENU_H
