#ifndef CUSTOMIMAGESCREEN_H
#define CUSTOMIMAGESCREEN_H

#include "mainmenu.h"

#include <QWidget>
#include <QGraphicsView>

class CustomImageScreen : public QWidget
{

    Q_OBJECT
public:
    explicit CustomImageScreen(MainMenu *mm, QWidget *parent = 0);
    void display(int screenWidth, int screenHeight);

private:
    QGraphicsView *gView;
    MainMenu *mainMenu;

};

#endif // CUSTOMIMAGESCREEN_H
