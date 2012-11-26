#ifndef PLAYSCREEN_H
#define PLAYSCREEN_H


#include "tile.h"

#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsView>
#include <QGridLayout>
#include <QLabel>
#include <QString>
#include <QWidget>

class PlayScreen : public QWidget
{
    Q_OBJECT
public:
    explicit PlayScreen(QString imgPath, QWidget *parent = 0);
    void display(int screenWidth, int screenHeight);

private:
    int* findHiddenTile(int x, int y, int hiddenX, int hiddenY);
    void swapTiles(Tile *tile1, Tile *tile2);
    void shuffle();
    int calculatePercent();
    void playerWin();

    int screenWidth, screenHeight;
    QString imgPath;

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

#endif // PLAYSCREEN_H
