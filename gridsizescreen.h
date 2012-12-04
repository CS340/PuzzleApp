#ifndef GRIDSIZESCREEN_H
#define GRIDSIZESCREEN_H

//AUTHORS: Matt Dumford

#include "playscreen.h"
#include "mainwindow.h"

#include <QWidget>
#include <QString>

// The grid size screen is used to get a size for the singleplayer play grid
// it uses 8 qpushbuttons with the respective grid size
class GridSizeScreen : public QWidget
{
    Q_OBJECT
public:
    explicit GridSizeScreen(QString path, MainWindow *mainWindow, QWidget *parent = 0);
    explicit GridSizeScreen(MainWindow *mainWindow, QWidget *parent = 0);
    void display(int screenWidth, int screenHeight);

private:
    QString path; //file path for the image chosen to be passed
    int screenWidth, screenHeight;
    MainWindow *mainWindow;


    //each slot corresponds with the button for the grid size displayed on it
private slots:
    void b3Pushed();
    void b4Pushed();
    void b5Pushed();
    void b6Pushed();
    void b7Pushed();
    void b8Pushed();
    void b9Pushed();
    void b10Pushed();
};

#endif // GRIDSIZESCREEN_H
