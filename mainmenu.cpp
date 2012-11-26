#include "mainmenu.h"
#include "playscreen.h"
#include "highscorescreen.h"
#include "customimagescreen.h"
#include "networkplayscreen.h"

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


MainMenu::MainMenu(QWidget *parent) : QWidget(parent)
{
    imgPath = new QString(":/elephant.gif");
}

MainMenu::MainMenu(QString *path, QWidget *parent) : QWidget(parent)
{
    imgPath = path;
}

void MainMenu::display(int sw, int sh)
{

    screenWidth = sw;
    screenHeight = sh;

    //setup for picture
    QLabel *imageLabel = new QLabel(this);
    QImage elephant(":/elephant.gif");

    elephant = elephant.scaledToWidth((4.4/6.1)*sw);

    imageLabel->setPixmap(QPixmap::fromImage(elephant));
    imageLabel->resize(elephant.width(), elephant.height());
    imageLabel->show();

    //setup for buttons
    QWidget *widget1 = new QWidget;
    QGridLayout *layout = new QGridLayout;
    widget1->setLayout(layout);

    QPushButton *customImageButton = new QPushButton("Custom Image");
    QPushButton *singlePlayerButton = new QPushButton("Single Player");
    QPushButton *multiplayerButton = new QPushButton("Multi-player");
    QPushButton *highscore = new QPushButton("Highscores");
    QSize buttonsize1(sw,100);
    QFont myfont("Helvetica", 16, QFont::Bold);
    myfont.setFamily("Helvetica");
    QFont customImageFont("helvetica", 13, QFont::Bold);
    customImageFont.setFamily("Helvetica");

    //setup for arrow buttons
    QImage r_arrow_pic(":/Right.gif");
    QImage l_arrow_pic(":/Left.gif");
    QSize arrowSize((sw-elephant.width())/2, (sw-elephant.width())/2-10);

    //create arrow buttons
    QPushButton *left = new QPushButton();
    left->setIcon(QIcon(QPixmap::fromImage(l_arrow_pic)));
    left->setIconSize(arrowSize);
    QPushButton *right = new QPushButton();
    right->setIcon(QIcon(QPixmap::fromImage(r_arrow_pic)));
    right->setIconSize(arrowSize);
    left->setFixedSize(arrowSize);
    right->setFixedSize(arrowSize);

    //button sizing
    customImageButton->setMinimumWidth(elephant.width());
    singlePlayerButton->setMinimumWidth(sw);
    multiplayerButton->setMinimumWidth(sw);
    highscore->setMinimumWidth(sw);

    //fonts
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

    widget1->show();
}

void MainMenu::customImage()
{
    qDebug() << "Making custom image";
    CustomImageScreen *cis = new CustomImageScreen(this, this);
    cis->display(screenWidth, screenHeight);
    qDebug() << "custom image made";
}

void MainMenu::left()
{
    qDebug() << "left pressed, switching picture";
}

void MainMenu::right()
{
    qDebug() << "right pressed, switching picture";
}

void MainMenu::cancel()
{
    this->display(screenWidth, screenHeight);
}

void MainMenu::makeGame()
{
    qDebug() << "Making game...";
    PlayScreen *ps = new PlayScreen(this);
    ps->display(screenWidth, screenHeight);
    qDebug() << "Game made.";
}

void MainMenu::makeMultiplayerGame()
{
    qDebug() << "Making multiplayer game.";
    NetworkPlayScreen *nps = new NetworkPlayScreen(this);
    nps->display(screenWidth, screenHeight);
    qDebug() << "multiplayer game made.";
}

void MainMenu::makeHighscore()
{
    qDebug() << "Making Highscore...";
    HighscoreScreen *hss = new HighscoreScreen(this);
    hss->display(screenWidth, screenHeight);
    qDebug() << "Highscore made.";
}
