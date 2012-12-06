#ifndef HIGHSCORESCREEN_H
#define HIGHSCORESCREEN_H

//AUTHORS: Anthony Phelps

#include "mainwindow.h"

#include <QWidget>
#include <QTcpSocket>
#include <QLabel>

// Makes a connection to the highscore server.
// Uses the user's username to gather a list of their
// top ten scores and the global top ten scores.

class HighscoreScreen : public QWidget
{
    Q_OBJECT
public:
    explicit HighscoreScreen(MainWindow *mainWindow, QWidget *parent = 0);
    void display(int screenWidth, int screenHeight);
    
private:
    void makeCon(); //Makes connection to server
    QString parseResponse(QString s); //Parses server response
    int screenWidth, screenHeight;
    MainWindow *mainWindow;
    QTcpSocket *socket;
    bool all;
    bool checkNext;
    QString myScoreString; //Contains the user's top ten scores
    QString allScoreString; //Contains the gloabl top ten scores
    QLabel *allScoreLabel; // Label to display gloabl scores
    QLabel *myScoreLabel; //Label to display personal scores

signals:
    
private slots:
    void connected(); //Run when connection is established
    void disconnected(); //Run when connection closes.
    void bytesWritten(qint64 bytes); //Run when bytes have been written over the socket.
    void readyRead(); //Run when connection can be read from.
    void mineScores();  //Refreshes personal user scores
    void allScores(); //Refreshes gloabl scores
    void refresh(); //Refreshes both of the above
    void mainMenuButtonClicked();
};

#endif // HIGHSCORESCREEN_H
