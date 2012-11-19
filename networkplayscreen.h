#ifndef NETWORKPLAYSCREEN_H
#define NETWORKPLAYSCREEN_H

#include <QWidget>
#include "tile.h"

#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsView>
#include <QGridLayout>
#include <QLabel>

class NetworkPlayScreen : public QWidget
{
    Q_OBJECT
public:
    explicit NetworkPlayScreen(QWidget *parent = 0);
    void display(int screenWidth, int screenHeight);

private:
    int* findHiddenTile(int x, int y, int hiddenX, int hiddenY);
    void swapTiles(Tile *tile1, Tile *tile2);
    void shuffle();
    int calculatePercent();
    void playerWin();

    QGraphicsView *gView;
    QGridLayout *layout;
    QGridLayout *playGrid;
    QGridLayout *menuGrid;
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
    void update();
};

#endif // NETWORKPLAYSCREEN_H
