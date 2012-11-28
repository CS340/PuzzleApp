#include "usernamescreen.h"

#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QFont>
#include <QDebug>

UsernameScreen::UsernameScreen(QWidget *parent) : QWidget(parent)
{
}

void UsernameScreen::display(int screenWidth, int screenHeight)
{
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

    this->show();
}

//void UsernameScreen::newText(const QString &t)
//{
//    text = t;
//}

void UsernameScreen::okPushed()
{
//    qDebug() << "OK pushed.";
//    qDebug() << text;

}
