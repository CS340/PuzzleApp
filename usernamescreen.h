#ifndef USERNAMESCREEN_H
#define USERNAMESCREEN_H

#include "mainwindow.h"

#include <QWidget>
#include <QLineEdit>
#include <QGridLayout>
#include <QTcpSocket>

class UsernameScreen : public QWidget
{
    Q_OBJECT
public:
    explicit UsernameScreen(MainWindow *mainWindow, QWidget *parent = 0);
    void display(int screenWidth, int screenHeight);

private:
    void makeCon();
    QString parseResponse(QString s);

    MainWindow *mainWindow;
    int screenWidth, screenHeight;
    QLineEdit *lineEdit;
    QGridLayout *layout;
    QString text;
    QTcpSocket *socket;
    
public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void okPushed();
    void newText(const QString&);
    
};

#endif // USERNAMESCREEN_H
