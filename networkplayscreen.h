#ifndef NETWORKPLAYSCREEN_H
#define NETWORKPLAYSCREEN_H

//AUTHORS: Anthony Phelps

#include "tile.h"
#include "mainwindow.h"

#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsView>
#include <QGridLayout>
#include <QLabel>
#include <QString>
#include <QWidget>
#include <QTcpSocket>

// the networkplayScreen is the screen for the multi-player game.
// it takes in the file path to the image the user wants to use
// and cuts it up into tiles and displays them on the screen with various
// menu buttons and statistics. It also handles tile clicks and tile swapping.
// It is nearly identical to the single player screen except it sends and recives
// player actions over the network
class NetworkPlayScreen : public QWidget
{
    Q_OBJECT
public:
    explicit NetworkPlayScreen(QString imgPath, MainWindow *mainWindow, QWidget *parent = 0);
    void display(int screenWidth, int screenHeight, int gridSize = 5);

private:
    int* findHiddenTile(int x, int y, int hiddenX, int hiddenY); //finds the position if the blank tile relative to another tile
    void swapTiles(Tile *tile1, Tile *tile2); //switch the position of two tiles
    void shuffle();  //shuffle the tiles
    int calculatePercent(); //calculate the percent of the puzzle that is complete
    QString parseResponse(QString s);
    void makeCon();

    int screenWidth, screenHeight;
    QString imgPath; //file path to the user's chosen image
    QImage image;
    MainWindow *mainWindow;
    QTcpSocket *socket;
    QString partner,gameName;

    QGraphicsView *gView;
    QGridLayout *layout;
    QGridLayout *playGrid; //grid of tiles
    QGridLayout *menuGrid;

    Tile *hiddenTile;
    int numMoves;
    int seconds;
    int percentComplete;
    int grid;
    QLabel *movesLabel;
    QLabel *timerLabel;
    QLabel *percentLabel;
    QLabel *opMovesLabel;
    QLabel *opPercentLabel;
    QTimer *timer;

signals:
    void win();

private slots:
    void handleTileClick(Tile*);
    void update(); //update the timer
    void mainMenuButtonClicked();
    void giveUpButtonClicked();
    void playerWin();
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
};

#endif // NETWORKPLAYSCREEN_H
