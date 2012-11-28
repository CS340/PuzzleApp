#ifndef WIN_MENU_H
#define WIN_MENU_H

#include"mainwindow.h"

#include <QObject>
#include <QGridLayout>
#include <QMovie>
#include <QLabel>

class win_menu : public QWidget
{
    Q_OBJECT
public:
    explicit win_menu(MainWindow *mainWindow, QWidget *parent = 0);
    void display(int sw, int sh);
    void restart();
    QGridLayout win_layout;


private:
    int screen_height;
    int screen_width;
    MainWindow *mainWindow;

signals:
    
public slots:
    void mainMenuClicked();
    void quitClicked();
    
};

#endif // WIN_MENU_H
