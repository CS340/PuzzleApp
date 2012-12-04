#ifndef CUSTOMIMAGESCREEN_H
#define CUSTOMIMAGESCREEN_H

//AUTHORS: Matt Dumford

#include "mainmenu.h"
#include "mainwindow.h"

#include <QWidget>
#include <QGraphicsView>

// the custom image screen allows the user to choose an image to play with from their sd card.
// it uses a QDir object to navigate to a predetermined folder and grab all of the filepaths
// for the images it finds. it uses custom image buttons to send the filepath for the chosen image
// back to the main menu. A QScrollArea is used for the scrolling, but due to qt limitations,
// two fingers must be used.
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
    void customImageChosen(QString); //recieves signal from custom image buttons and sends the filepath up to the main menu

};

#endif // CUSTOMIMAGESCREEN_H
