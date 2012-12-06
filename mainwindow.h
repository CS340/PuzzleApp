//AUTHORS: Anthony Phelps, Matt Dumford
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

    //getter and setter for user name so all sub-menus/screens have access
    QString getUserName();
    void setUserName(QString name);

    void showExpanded();

private:
    Ui::MainWindow *ui;
    QString userName;


private slots:

};

#endif // MAINWINDOW_H
