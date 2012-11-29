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


// userNameScreen is shown only the first time the app is run.
// it takes in a QString with a QLineEdit to use as the players
// user name for the online high scores and multiplayer.
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

    //set up layout
    QFont font("Helvetica", 13);
    layout = new QGridLayout();
    this->setLayout(layout);
    this->setFixedSize(screenWidth, screenHeight);

    //create QLineEdit to take user input
    QLineEdit *lineEdit = new QLineEdit();
    lineEdit->setFixedWidth(screenWidth);
    layout->addWidget(lineEdit, 1,0,1,1,Qt::AlignHCenter);

    //instruction label
    QLabel *label = new QLabel("Please input a username.");
    label->setFixedSize(screenWidth, screenHeight/10);
    label->setAlignment(Qt::AlignHCenter);
    label->setFont(font);
    layout->addWidget(label, 0,0,1,1,Qt::AlignHCenter);

    //create ok button and add to the layout
    QPushButton *okButton = new QPushButton("OK");
    okButton->setFixedWidth(screenWidth/2);
    layout->addWidget(okButton, 2,0,1,1,Qt::AlignHCenter);

    //connect everything
    connect(okButton, SIGNAL(clicked()), this, SLOT(okPushed()));
    connect(lineEdit, SIGNAL(textEdited(QString)), this, SLOT(newText(QString)));

    lineEdit->clearFocus();
    this->show();
}


//updates text whenever the user makes changes in the QLineEdit
void UsernameScreen::newText(const QString &t)
{
    qDebug() << "new text.";
    text = t;
}

//saves text to a file on the sd card and passes the user name to mainWindow
//for easy access in other classes. Also creates main menu.
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
    socket->connectToHost("ganymede.sytes.net", 4848);
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
