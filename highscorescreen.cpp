#include "highscorescreen.h"
#include <QPushButton>
#include <QGridLayout>
#include <QTcpSocket>

HighscoreScreen::HighscoreScreen(QWidget *parent) :
    QWidget(parent)
{
    all = false;
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
}

void HighscoreScreen::display(int screenWidth, int screenHeight)
{
    QGridLayout *layout = new QGridLayout;
    this->setLayout(layout);

    QPushButton *mine = new QPushButton("My Highscores");
    QPushButton *all = new QPushButton("Global Highscores");

    layout->addWidget(mine,0,0);
    layout->addWidget(all,0,1);

    connect(mine, SIGNAL(clicked()), this, SLOT(mineScores()));
    connect(all, SIGNAL(clicked()), this, SLOT(allScores()));

    this->show();

}
void HighscoreScreen::allScores()
{
    all = true;
    makeCon();
}

void HighscoreScreen::makeCon()
{
    qDebug() << "Connecting...";
    socket->connectToHost("10.107.205.243", 4848);

    if(!socket->waitForConnected(1000))
    {
        qDebug() << "ERROR: " << socket->errorString();
    }
}

void HighscoreScreen::connected()
{
    qDebug() << "Connected";
    if(all)
    {
        socket->write("score:get:all\n");
    }
    else
    {
        socket->write("score:get:aphelps\n");
    }
}

void HighscoreScreen::disconnected()
{
    qDebug() << "Disconnected";
}

void HighscoreScreen::bytesWritten(qint64 bytes)
{
    qDebug() << "Wrote Something: " << bytes << "bytes";
}

void HighscoreScreen::readyRead()
{
    qDebug() << "Reading...";
    qDebug() << socket->readLine(1024);
}

void HighscoreScreen::mineScores()
{
    all=false;
    makeCon();
}
