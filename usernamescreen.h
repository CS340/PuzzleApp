#ifndef USERNAMESCREEN_H
#define USERNAMESCREEN_H

#include "mainwindow.h"

#include <QWidget>
#include <QLineEdit>
#include <QGridLayout>

class UsernameScreen : public QWidget
{
    Q_OBJECT
public:
    explicit UsernameScreen(MainWindow *mainWindow, QWidget *parent = 0);
    void display(int screenWidth, int screenHeight);

private:
    MainWindow *mainWindow;
    int screenWidth, screenHeight;
    QLineEdit *lineEdit;
    QGridLayout *layout;
    QString text;
    
signals:
    
public slots:
    void okPushed();
    void newText(const QString&);
    
};

#endif // USERNAMESCREEN_H
