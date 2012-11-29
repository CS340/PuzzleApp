#ifndef PLAYSCREEN_H
#define PLAYSCREEN_H


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

class PlayScreen : public QWidget
{
    Q_OBJECT
public:
    explicit PlayScreen(QString imgPath, MainWindow *mainWindow, QWidget *parent = 0);
    void display(int screenWidth, int screenHeight, int gridSize = 5);

signals:
    void win();

private:
    int* findHiddenTile(int x, int y, int hiddenX, int hiddenY);
    void swapTiles(Tile *tile1, Tile *tile2);
    void shuffle();
    int calculatePercent();
    void makeCon();
    QString parseResponse(QString s);


    int screenWidth, screenHeight;
    QString imgPath;
    QImage image;
    MainWindow *mainWindow;

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
    QTcpSocket *socket;

private slots:
    void handleTileClick(Tile*);
    void update();
    void winButtonClicked();
    void pauseButtonClicked();
    void giveUpButtonClicked();
    void playerWin();
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
};

#endif // PLAYSCREEN_H
