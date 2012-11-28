#ifndef GRIDSIZESCREEN_H
#define GRIDSIZESCREEN_H

#include "playscreen.h"
#include "mainwindow.h"

#include <QWidget>
#include <QString>

class GridSizeScreen : public QWidget
{
    Q_OBJECT
public:
    explicit GridSizeScreen(QString path, MainWindow *mainWindow, QWidget *parent = 0);
    explicit GridSizeScreen(MainWindow *mainWindow, QWidget *parent = 0);
    void display(int screenWidth, int screenHeight);

private:
    QString path;
    int screenWidth, screenHeight;
    MainWindow *mainWindow;

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
