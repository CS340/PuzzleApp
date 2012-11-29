#ifndef USERNAMESCREEN_H
#define USERNAMESCREEN_H

//AUTHORS: Matt Dumford, Anthony Phelps

#include "mainwindow.h"

#include <QWidget>
#include <QLineEdit>
#include <QGridLayout>

// userNameScreen is shown only the first time the app is run.
// it takes in a QString with a QLineEdit to use as the players
// user name for the online high scores and multiplayer.
class UsernameScreen : public QWidget
{
    Q_OBJECT
public:
    explicit UsernameScreen(MainWindow *mainWindow, QWidget *parent = 0);
    void display(int screenWidth, int screenHeight); //create all sub-widgets

private:
    MainWindow *mainWindow;
    int screenWidth, screenHeight;
    QGridLayout *layout; //holds all sub-widgets
    QString text; //holds the user input
    
signals:
    
public slots:
    void okPushed(); //ok button, saves user name to file and goes to main menu
    void newText(const QString&); //updates text to whatever is in the QLineEdit
    
};

#endif // USERNAMESCREEN_H
