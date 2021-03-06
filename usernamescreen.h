#ifndef USERNAMESCREEN_H
#define USERNAMESCREEN_H

//AUTHORS: Matt Dumford, Anthony Phelps

#include "mainwindow.h"

#include <QWidget>
#include <QLineEdit>
#include <QGridLayout>
#include <QTcpSocket>

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
    void makeCon();
    QString parseResponse(QString s);

    MainWindow *mainWindow;
    int screenWidth, screenHeight;
    QGridLayout *layout; //holds all sub-widgets
    QString text; //holds the user input
    QTcpSocket *socket;
    
signals:
    
public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void okPushed(); //ok button, saves user name to file and goes to main menu
    void newText(const QString&);//updates text to whatever is in the QLineEdit
    
};

#endif // USERNAMESCREEN_H
