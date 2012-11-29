#ifndef PLAYSCREEN_H
#define PLAYSCREEN_H

//AUTHORS: Matt Dumford, Anthony Phelps

#include "tile.h"
#include "mainwindow.h"

#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsView>
#include <QGridLayout>
#include <QLabel>
#include <QString>
#include <QWidget>

// the playScreen is the screen for the single player game.
// it takes in the file path to the image the user wants to use
// and cuts it up into tiles and displays them on the screen with various
// menu buttons and statistics. It also handles tile clicks and tile swapping.
class PlayScreen : public QWidget
{
    Q_OBJECT
public:
    explicit PlayScreen(QString imgPath, MainWindow *mainWindow, QWidget *parent = 0);
    void display(int screenWidth, int screenHeight, int gridSize = 5);

private:
    int* findHiddenTile(int x, int y, int hiddenX, int hiddenY); //finds the position if the blank tile relative to another tile
    void swapTiles(Tile *tile1, Tile *tile2); //switch the position of two tiles
    void shuffle(); //shuffle the tiles
    int calculatePercent(); //calculate the percent of the puzzle that is complete


    int screenWidth, screenHeight;
    QString imgPath; //file path to the user's chosen image
    MainWindow *mainWindow;

    QGridLayout *playGrid; //grid of tiles
    Tile *hiddenTile;
    int numMoves;
    int seconds;
    int percentComplete;
    int grid;
    QLabel *movesLabel;
    QLabel *timerLabel;
    QLabel *percentLabel;
    QTimer *timer;

private slots:
    void handleTileClick(Tile*);
    void update(); //update the timer
    void winButtonClicked();
    void pauseButtonClicked();
    void giveUpButtonClicked();
    void playerWin();
};

#endif // PLAYSCREEN_H
