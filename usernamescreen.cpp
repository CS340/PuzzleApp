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

UsernameScreen::UsernameScreen(MainWindow *mainWindow, QWidget *parent) : QWidget(parent)
{
    this->mainWindow = mainWindow;
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

    //go to main menu
    MainMenu *mm = new MainMenu(mainWindow, mainWindow);
    mm->display(screenWidth, screenHeight);
}
