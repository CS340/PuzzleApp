#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tile.h"
#include "timerthread.h"

#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsView>
#include <QGridLayout>
#include <QLabel>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum ScreenOrientation {
        ScreenOrientationLockPortrait,
        ScreenOrientationLockLandscape,
        ScreenOrientationAuto
    };

    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    void display(int screenWidth, int screenHeight);

    // Note that this will only have an effect on Fremantle.
    void setOrientation(ScreenOrientation orientation);

    void showExpanded();

    Tile *test;

private:
    int* findHiddenTile(int x, int y, int hiddenX, int hiddenY);
    void swapTiles(Tile *tile1, Tile *tile2);
    void shuffle(int grid);

    QGraphicsView *gView;
    QGridLayout *layout;
    QGridLayout *playGrid;
    QGridLayout *menuGrid;
    Ui::MainWindow *ui;
    Tile *hiddenTile;
    int numMoves;
    int seconds;
    QLabel *movesLabel;
    QLabel *timerLabel;
    QTimer *timer;

private slots:
    void handleTileClick(Tile*);
    void update();
};

#endif // MAINWINDOW_H
