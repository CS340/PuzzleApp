#include "mainmenu.h"
#include "playscreen.h"
#include "highscorescreen.h"
#include "customimagescreen.h"

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

}

void MainMenu::display(int sw, int sh)
{

    screenWidth = sw;
    screenHeight = sh;

    //setup for picture
    QLabel *imageLabel = new QLabel(this);
    QImage elephant(":/elephant.gif");

    elephant = elephant.scaledToWidth(sw - 200);

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

    //setup for arrow buttons
    QImage r_arrow_pic(":/Right.gif");
    QImage l_arrow_pic(":/Left.gif");

    QLabel *l_arrow_button = new QLabel(this);
    QLabel *r_arrow_button = new QLabel(this);

    l_arrow_pic = l_arrow_pic.scaledToWidth(50);
    r_arrow_pic = r_arrow_pic.scaledToWidth(50);

    l_arrow_button->setPixmap(QPixmap::fromImage(l_arrow_pic));
    r_arrow_button->setPixmap(QPixmap::fromImage(r_arrow_pic));

    QPushButton *button4 = new QPushButton("<");
    QPushButton *button5 = new QPushButton(">");
    QSize buttonsize2(50, elephant.height());

    //Putting everything together in the menu
    customImageButton->setFixedSize(elephant.width(), 100);
    singlePlayerButton->setFixedSize(buttonsize1);
    multiplayerButton->setFixedSize(buttonsize1);
    highscore->setFixedSize(buttonsize1);
    singlePlayerButton->setFont(myfont);
    multiplayerButton->setFont(myfont);
    highscore->setFont(myfont);
    button4->setFixedSize(buttonsize2);
    button5->setFixedSize(buttonsize2);
    button4->setFont(myfont);
    button5->setFont(myfont);


    layout->addWidget(l_arrow_button, 1, 1, 1, 1);
    layout->addWidget(imageLabel, 1, 2, 1, 1, Qt::AlignHCenter);
    layout->addWidget(r_arrow_button, 1, 3, 1, 1, Qt::AlignRight);
    layout->addWidget(customImageButton, 2, 1, 1, 3, Qt::AlignHCenter);
    layout->addWidget(singlePlayerButton, 3, 1, 1, 3, Qt::AlignHCenter);
    layout->addWidget(multiplayerButton, 4, 1, 1, 3, Qt::AlignHCenter);
    layout->addWidget(highscore, 5, 1, 1, 3, Qt::AlignHCenter);

    connect(customImageButton, SIGNAL(clicked()), this, SLOT(customImage()));
    connect(singlePlayerButton, SIGNAL(clicked()), this, SLOT(makeGame()));
    connect(highscore, SIGNAL(clicked()), this, SLOT(makeHighscore()));

    widget1->show();
}

void MainMenu::customImage()
{
    qDebug() << "Making custom image";

    CustomImageScreen *cis = new CustomImageScreen(this, this);
    cis->display(screenWidth, screenHeight);
    qDebug() << "custom image made";
    this->raise();
}

void MainMenu::cancel()
{
    this->raise();
}

void MainMenu::customImageChosen(QString path)
{
    qDebug() << "custom image chosen: " << path;
}

void MainMenu::makeGame()
{
    qDebug() << "Making game...";
    PlayScreen *ps = new PlayScreen(this->parentWidget());
    ps->display(screenWidth, screenHeight);
    qDebug() << "Game made.";
}

void MainMenu::makeHighscore()
{
    qDebug() << "Making Highscore...";
    HighscoreScreen *hss = new HighscoreScreen(screenWidth, screenHeight);
    qDebug() << "Highscore made.";
}
