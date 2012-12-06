//AUTHORS: Alan Leung, Carlos Lopez

#include "mainmenu.h"
#include "playscreen.h"
#include "highscorescreen.h"
#include "customimagescreen.h"
#include "networkplayscreen.h"
#include "gridsizescreen.h"

#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QSize>
#include <QGridLayout>
#include <QFont>
#include <QImageReader>
#include <QDesktopWidget>
#include <QImage>
#include <QDebug>

// The main menu keeps track of all default images to choose from and handles switching between them
// it also has buttons to go to all other screens.

//no custom image
MainMenu::MainMenu(MainWindow *mainWindow, QWidget *parent) : QWidget(parent)
{
    this->mainWindow = mainWindow;
    pathsIndex = 0;

    //add default images to vector of filepaths
    paths.push_back(QString(":/elephant.gif"));
    paths.push_back(QString(":/chameleon.jpg"));
    paths.push_back(QString(":/sandwich.jpg"));
    paths.push_back(QString(":/dog.jpg"));
    paths.push_back(QString(":/smiley.jpg"));
}

//custom image
MainMenu::MainMenu(QString path, MainWindow *mainWindow, QWidget *parent) : QWidget(parent)
{
    this->mainWindow = mainWindow;
    pathsIndex = 0;

    //add custom and default images to vector of filepaths
    paths.push_back(path);
    paths.push_back(QString(":/elephant.gif"));
    paths.push_back(QString(":/chameleon.jpg"));
    paths.push_back(QString(":/sandwich.jpg"));
    paths.push_back(QString(":/dog.jpg"));
    paths.push_back(QString(":/smiley.jpg"));
}

void MainMenu::display(int sw, int sh)
{
    screenWidth = sw;
    screenHeight = sh;

    //setup for picture
    imageLabel = new QLabel(this);
    QImage image(paths[pathsIndex]);
    image = image.scaledToWidth((4.4/6.1)*sw);
    imageLabel->setPixmap(QPixmap::fromImage(image));
    imageLabel->resize(image.width(), image.height());

    //layout for buttons
    QWidget *widget1 = new QWidget;
    layout = new QGridLayout;
    widget1->setLayout(layout);

    //create buttons
    QPushButton *customImageButton = new QPushButton("Custom Image");
    QPushButton *singlePlayerButton = new QPushButton("Single Player");
    QPushButton *multiplayerButton = new QPushButton("Multi-player");
    QPushButton *highscore = new QPushButton("Highscores");

    //setup for arrow buttons
    QImage r_arrow_pic(":/Right.gif");
    QImage l_arrow_pic(":/Left.gif");
    QSize arrowSize((sw-image.width())/2, (sw-image.width())/2-10);

    //create arrow buttons
    QPushButton *left = new QPushButton();
    left->setIcon(QIcon(QPixmap::fromImage(l_arrow_pic)));
    left->setIconSize(arrowSize);
    left->setFixedSize(arrowSize);
    QPushButton *right = new QPushButton();
    right->setIcon(QIcon(QPixmap::fromImage(r_arrow_pic)));
    right->setIconSize(arrowSize);
    right->setFixedSize(arrowSize);

    //button sizing
    //customImageButton->setMinimumWidth(image.width());
    singlePlayerButton->setMinimumWidth(sw);
    multiplayerButton->setMinimumWidth(sw);
    highscore->setMinimumWidth(sw);

    //fonts
    QFont myfont("Helvetica", 16, QFont::Bold);
    myfont.setFamily("Helvetica");
    QFont customImageFont("helvetica", 13, QFont::Bold);
    customImageFont.setFamily("Helvetica");
    customImageButton->setFont(customImageFont);
    singlePlayerButton->setFont(myfont);
    multiplayerButton->setFont(myfont);
    highscore->setFont(myfont);

    //add everything to layout
    layout->addWidget(left, 0, 0, 1, 1);
    layout->addWidget(imageLabel, 0, 1, 1, 1, Qt::AlignHCenter);
    layout->addWidget(right, 0, 2, 1, 1, Qt::AlignRight);
    layout->addWidget(customImageButton, 1, 0, 1, 3, Qt::AlignHCenter);
    layout->addWidget(singlePlayerButton, 2, 0, 1, 3, Qt::AlignHCenter);
    layout->addWidget(multiplayerButton, 3, 0, 1, 3, Qt::AlignHCenter);
    layout->addWidget(highscore, 4, 0, 1, 3, Qt::AlignHCenter);

    //connect buttons
    connect(customImageButton, SIGNAL(clicked()), this, SLOT(customImage()));
    connect(singlePlayerButton, SIGNAL(clicked()), this, SLOT(makeGame()));
    connect(multiplayerButton, SIGNAL(clicked()), this, SLOT(makeMultiplayerGame()));
    connect(highscore, SIGNAL(clicked()), this, SLOT(makeHighscore()));
    connect(left, SIGNAL(clicked()), this, SLOT(left()));
    connect(right, SIGNAL(clicked()), this, SLOT(right()));

    //username label
    QLabel *userName = new QLabel(QString("User name: ") + mainWindow->getUserName());
    userName->setFixedHeight(20);
    layout->addWidget(userName, 5,0,1,3,Qt::AlignHCenter);

    widget1->show();
}

//go to custom image screen
void MainMenu::customImage()
{
    qDebug() << "Making custom image";
    CustomImageScreen *cis = new CustomImageScreen(this ,mainWindow, mainWindow);
    cis->display(screenWidth, screenHeight);
    qDebug() << "custom image made";
}

//left arrow pressed
void MainMenu::left()
{
    qDebug() << "left pressed, switching picture";

    //loop around to the end if index is at 0
    if(pathsIndex == 0) pathsIndex = paths.size()-1;
    else pathsIndex--;

    delete imageLabel;

    //create a new image label and put it where the old one was
    imageLabel = new QLabel(this);
    QImage image(paths[pathsIndex]);
    image = image.scaledToWidth((4.4/6.1)*screenWidth);
    imageLabel->setPixmap(QPixmap::fromImage(image));
    imageLabel->resize(image.width(), image.height());

    layout->addWidget(imageLabel, 0, 1, 1, 1, Qt::AlignHCenter);
}

//right arrow pressed
void MainMenu::right()
{
    qDebug() << "right pressed, switching picture";

    //loop arouund to the beginning if index is at the end of the vector
    if(pathsIndex == paths.size()-1) pathsIndex = 0;
    else pathsIndex++;

    delete imageLabel;

    //create a new image label and put it where the old one was
    imageLabel = new QLabel(this);
    QImage image(paths[pathsIndex]);
    image = image.scaledToWidth((4.4/6.1)*screenWidth);
    imageLabel->setPixmap(QPixmap::fromImage(image));
    imageLabel->resize(image.width(), image.height());

    layout->addWidget(imageLabel, 0, 1, 1, 1, Qt::AlignHCenter);
}

//called from custom image screen
void MainMenu::cancel()
{
    this->display(screenWidth, screenHeight);
}

//single player game, goes to grid size screen
void MainMenu::makeGame()
{
//    qDebug() << "Making game...";
    GridSizeScreen *gss = new GridSizeScreen(paths[pathsIndex], mainWindow);
    gss->display(screenWidth, screenHeight);
    this->lower();
    gss->raise();
}

//goes to multiplayer game screen
void MainMenu::makeMultiplayerGame()
{
    qDebug() << "Making multiplayer game.";
    NetworkPlayScreen *nps = new NetworkPlayScreen(paths[pathsIndex], mainWindow, mainWindow);
    nps->display(screenWidth, screenHeight);
    qDebug() << "multiplayer game made.";
}

//goes to high score screen
void MainMenu::makeHighscore()
{
    qDebug() << "Making Highscore...";
    HighscoreScreen *hss = new HighscoreScreen(mainWindow, mainWindow);
    hss->display(screenWidth, screenHeight);
    qDebug() << "Highscore made.";
}
