#include "usernamescreen.h"
#include "mainmenu.h"

#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QFont>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QTcpSocket>

UsernameScreen::UsernameScreen(MainWindow *mainWindow, QWidget *parent) : QWidget(parent)
{
    this->mainWindow = mainWindow;
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
}

void UsernameScreen::display(int screenWidth, int screenHeight)
{
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    QFont font("Helvetica", 13);
    layout = new QGridLayout();
    this->setLayout(layout);
    this->setFixedSize(screenWidth, screenHeight);

    lineEdit = new QLineEdit();
    lineEdit->setFixedWidth(screenWidth);
    layout->addWidget(lineEdit, 1,0,1,1,Qt::AlignHCenter);

    QLabel *label = new QLabel("Please input a username.");
    label->setFixedSize(screenWidth, screenHeight/10);
    label->setAlignment(Qt::AlignHCenter);
    label->setFont(font);
    layout->addWidget(label, 0,0,1,1,Qt::AlignHCenter);

    QPushButton *okButton = new QPushButton("OK");
    okButton->setFixedWidth(screenWidth/2);
    layout->addWidget(okButton, 2,0,1,1,Qt::AlignHCenter);

    connect(okButton, SIGNAL(clicked()), this, SLOT(okPushed()));
    connect(lineEdit, SIGNAL(textEdited(QString)), this, SLOT(newText(QString)));

    lineEdit->clearFocus();
    this->show();
}

void UsernameScreen::newText(const QString &t)
{
    qDebug() << "new text.";
    text = t;
}

void UsernameScreen::okPushed()
{
    qDebug() << "OK pushed.";
    qDebug() << text;

    //save text to sdcard/Puzzle Pictures/user.name
    QFile file(QDir::rootPath().append("/sdcard/Puzzle Pictures/user.name"));
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << text;
    file.close();
    mainWindow->setUserName(text);
    qDebug() << "user.name written.";

    makeCon();

    //go to main menu
    MainMenu *mm = new MainMenu(mainWindow, mainWindow);
    mm->display(screenWidth, screenHeight);
}

QString UsernameScreen::parseResponse(QString s)
{
    QStringList parts = s.split(":");
    QString result;

    return result;
}

void UsernameScreen::makeCon()
{
    qDebug() << "Connecting...";
    socket->connectToHost("10.107.206.194", 4848);
    if(!socket->waitForConnected(2000))
    {
        qDebug() << "ERROR: " << socket->errorString();
    }
}

void UsernameScreen::connected()
{
    qDebug() << "Connected";
    socket->write(QString("user:new:"+ mainWindow->getUserName() + ":_:_" +  "\n").toUtf8());
}

void UsernameScreen::disconnected()
{
    qDebug() << "Disconnected";
}

void UsernameScreen::bytesWritten(qint64 bytes)
{
    qDebug() << "Wrote Something: " << bytes << "bytes";
}

void UsernameScreen::readyRead()
{
    qDebug() << "Reading...";
    parseResponse(socket->readLine(1024));
}
