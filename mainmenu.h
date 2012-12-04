#ifndef MAINMENU_H
#define MAINMENU_H

//AUTHORS: Alan Leung, Carlos Lopez

#include "mainwindow.h"

#include <QWidget>
#include <QString>
#include <vector>
#include <QLabel>
#include <QGridLayout>

// The main menu keeps track of all default images to choose from and handles switching between them
// it also has buttons to go to all other screens.
class MainMenu : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenu(MainWindow *mainWindow, QWidget *parent = 0); //no custom image
    explicit MainMenu(QString path, MainWindow *mainWindow, QWidget *parent = 0); //custom image
    void display(int sw, int sh);

private:
    int screenHeight;
    int screenWidth;
    int pathsIndex; //holds the index of the currently displayed picture in the vector of images
    QLabel *imageLabel;
    std::vector<QString> paths; //vector of filepaths to all images in the rotation
    QGridLayout *layout;
    int gridSize;
    MainWindow *mainWindow;

signals:
    
public slots:
    void makeGame(); //singleplayer
    void makeMultiplayerGame(); //multiplayer
    void makeHighscore(); //highscores
    void customImage();
    void cancel(); //cancel slot for custom image screen
    void left(); //left arrow
    void right(); //right arrow
    
};

#endif // MAINMENU_H
