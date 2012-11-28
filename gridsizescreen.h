#ifndef GRIDSIZESCREEN_H
#define GRIDSIZESCREEN_H

#include "playscreen.h"

#include <QWidget>
#include <QString>

class GridSizeScreen : public QWidget
{
    Q_OBJECT
public:
    explicit GridSizeScreen(QString path, QWidget *parent = 0);
    explicit GridSizeScreen(QWidget *parent = 0);
    void display(int screenWidth, int screenHeight);

private:
    QString path;
    int screenWidth, screenHeight;

private slots:
    void b3Pushed();
    void b4Pushed();
    void b5Pushed();
    void b6Pushed();
    void b7Pushed();
    void b8Pushed();
    void b9Pushed();
    void b10Pushed();
};

#endif // GRIDSIZESCREEN_H
