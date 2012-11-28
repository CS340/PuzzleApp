#ifndef NETWORKPLAYSCREEN_H
#define NETWORKPLAYSCREEN_H

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

class NetworkPlayScreen : public QWidget
{
    Q_OBJECT
public:
    explicit NetworkPlayScreen(QString imgPath, MainWindow *mainWindow, QWidget *parent = 0);
    void display(int screenWidth, int screenHeight, int gridSize = 5);

private:
    int* findHiddenTile(int x, int y, int hiddenX, int hiddenY);
    void swapTiles(Tile *tile1, Tile *tile2);
    void shuffle();
    int calculatePercent();
    QString parseResponse(QString s);
    void makeCon();

    int screenWidth, screenHeight;
    QString imgPath;
    QImage image;
    MainWindow *mainWindow;
    QTcpSocket *socket;

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

signals:
    void win();

private slots:
    void handleTileClick(Tile*);
    void update();
    void mainMenuButtonClicked();
    void pauseButtonClicked();
    void giveUpButtonClicked();
    void playerWin();
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
};

#endif // NETWORKPLAYSCREEN_H
