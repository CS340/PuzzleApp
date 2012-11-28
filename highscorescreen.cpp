#include "highscorescreen.h"
#include <QPushButton>
#include <QGridLayout>
#include <QTcpSocket>
#include <Qt>
#include <QLabel>

HighscoreScreen::HighscoreScreen(QWidget *parent) : QWidget(parent)
{
    all = false;
    myScoreString = "<table cellpadding=\"3\" border=\"1\"><tr><th>Please reload this list</th></tr></table>";
    allScoreString = "<table  cellpadding=\"3\" border=\"1\"><tr><th>Please reload this list</th></tr></table>";
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

    allScoreLabel = new QLabel(allScoreString);
    myScoreLabel = new QLabel(myScoreString);

    layout->addWidget(myScoreLabel,1,0);
    layout->addWidget(allScoreLabel,1,1);

    this->show();

    //mineScores();
    //allScores();

}

QString HighscoreScreen::parseResponse(QString s)
{
    QStringList parts = s.split(":");
    QString result;

    if(parts.length() != 3)
    {
        return "ERROR: Could not get scores.";
    }
    parts[2].truncate(parts[2].length()-2);

    QStringList pieces = parts[2].split(";");
    QStringList pppp;
    for(int i = 0; i < pieces.length(); i++)
    { 
        pppp = pieces[i].split(",");
        result += "<tr><td>" + pppp[0] +  "</td><td>" + pppp[1] + "</td></tr>";
    }

    if(parts[1] == "all")
    {
        allScoreString = "<table cellpadding=\"3\" border=\"1\"><tr><th>User</th><th>Score</th></tr>" + result + "</table>";
        allScoreLabel->setText(allScoreString);
    }
    else
    {
        myScoreString = "<table cellpadding=\"3\" border=\"1\"><tr><th>User</th><th>Score</th></tr>" + result + "</table>";
        myScoreLabel->setText(myScoreString);
    }

    return result;
}

void HighscoreScreen::allScores()
{
    all = true;
    makeCon();
}

void HighscoreScreen::makeCon()
{
    qDebug() << "Connecting...";
    socket->connectToHost("10.8.200.211", 4848);

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
    parseResponse(socket->readLine(1024));
}

void HighscoreScreen::mineScores()
{
    all=false;
    makeCon();
}
