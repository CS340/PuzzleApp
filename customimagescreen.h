#ifndef CUSTOMIMAGESCREEN_H
#define CUSTOMIMAGESCREEN_H

#include "mainmenu.h"
#include "mainwindow.h"

#include <QWidget>
#include <QGraphicsView>

class CustomImageScreen : public QWidget
{

    Q_OBJECT
public:
    explicit CustomImageScreen(MainMenu *mm, MainWindow *mainWindow, QWidget *parent = 0);
    void display(int screenWidth, int screenHeight);

private:
    QGraphicsView *gView;
    MainMenu *mainMenu;
    int screenWidth, screenHeight;
    MainWindow *mainWindow;

public slots:
    void customImageChosen(QString);

};

#endif // CUSTOMIMAGESCREEN_H
