#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tile.h"

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
    QLabel *movesLabel;

private slots:
    void handleTileClick(Tile*);
};

#endif // MAINWINDOW_H
