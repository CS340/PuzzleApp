#include "gridsizescreen.h"
#include "playscreen.h"

#include <QFont>
#include <QDebug>

GridSizeScreen::GridSizeScreen(QWidget *parent) : QWidget(parent)
{

}

GridSizeScreen::GridSizeScreen(QString path, QWidget *parent) : QWidget(parent)
{
    this->path = path;
}

void GridSizeScreen::display(int screenWidth, int screenHeight)
{
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    this->resize(screenWidth, screenHeight);
    QGridLayout *layout = new QGridLayout(this);
    this->setLayout(layout);
    QFont font("Helvetica", 13);
    QLabel *label = new QLabel("Please choose a grid size.");
    label->setFont(font);
    layout->addWidget(label,0,0,1,2);

    QPushButton *b3 = new QPushButton("3X3");
    QPushButton *b4 = new QPushButton("4X4");
    QPushButton *b5 = new QPushButton("5X5");
    QPushButton *b6 = new QPushButton("6X6");
    QPushButton *b7 = new QPushButton("7X7");
    QPushButton *b8 = new QPushButton("8X8");
    QPushButton *b9 = new QPushButton("9X9");
    QPushButton *b10 = new QPushButton("10X10");

    b3->setFont(font);
    b4->setFont(font);
    b5->setFont(font);
    b6->setFont(font);
    b7->setFont(font);
    b8->setFont(font);
    b9->setFont(font);
    b10->setFont(font);

    b3->setFixedHeight(screenHeight/5);
    b4->setFixedHeight(screenHeight/5);
    b5->setFixedHeight(screenHeight/5);
    b6->setFixedHeight(screenHeight/5);
    b7->setFixedHeight(screenHeight/5);
    b8->setFixedHeight(screenHeight/5);
    b9->setFixedHeight(screenHeight/5);
    b10->setFixedHeight(screenHeight/5);

    layout->addWidget(b3, 1,0);
    layout->addWidget(b4, 1,1);
    layout->addWidget(b5, 2,0);
    layout->addWidget(b6, 2,1);
    layout->addWidget(b7, 3,0);
    layout->addWidget(b8, 3,1);
    layout->addWidget(b9, 4,0);
    layout->addWidget(b10, 4,1);

    connect(b3, SIGNAL(clicked()), this, SLOT(b3Pushed()));
    connect(b4, SIGNAL(clicked()), this, SLOT(b4Pushed()));
    connect(b5, SIGNAL(clicked()), this, SLOT(b5Pushed()));
    connect(b6, SIGNAL(clicked()), this, SLOT(b6Pushed()));
    connect(b7, SIGNAL(clicked()), this, SLOT(b7Pushed()));
    connect(b8, SIGNAL(clicked()), this, SLOT(b8Pushed()));
    connect(b9, SIGNAL(clicked()), this, SLOT(b9Pushed()));
    connect(b10, SIGNAL(clicked()), this, SLOT(b10Pushed()));

    this->show();
    this->raise();
    qDebug() << "end of display.";
}

void GridSizeScreen::b3Pushed()
{
    PlayScreen *ps = new PlayScreen(path, this);
    ps->display(screenWidth, screenHeight, 3);
    ps->raise();
}

void GridSizeScreen::b4Pushed()
{
    PlayScreen *ps = new PlayScreen(path, this);
    ps->display(screenWidth, screenHeight, 4);
    ps->raise();
}

void GridSizeScreen::b5Pushed()
{
    PlayScreen *ps = new PlayScreen(path, this);
    ps->display(screenWidth, screenHeight, 5);
    ps->raise();
}

void GridSizeScreen::b6Pushed()
{
    PlayScreen *ps = new PlayScreen(path, this);
    ps->display(screenWidth, screenHeight, 6);
    ps->raise();
}

void GridSizeScreen::b7Pushed()
{
    PlayScreen *ps = new PlayScreen(path, this);
    ps->display(screenWidth, screenHeight, 7);
    ps->raise();
}

void GridSizeScreen::b8Pushed()
{
    PlayScreen *ps = new PlayScreen(path, this);
    ps->display(screenWidth, screenHeight, 8);
    ps->raise();
}

void GridSizeScreen::b9Pushed()
{
    PlayScreen *ps = new PlayScreen(path, this);
    ps->display(screenWidth, screenHeight, 9);
    ps->raise();
}

void GridSizeScreen::b10Pushed()
{
    PlayScreen *ps = new PlayScreen(path, this);
    ps->display(screenWidth, screenHeight, 10);
    ps->raise();
}
