#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tile.h"

#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsView>
#include <QGridLayout>

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

    QGraphicsView *gView;
    QGridLayout *layout;
    QGridLayout *playGrid;
    QGridLayout *menuGrid;
    Ui::MainWindow *ui;

private slots:
    void handleTileClick(Tile*);
};

#endif // MAINWINDOW_H
