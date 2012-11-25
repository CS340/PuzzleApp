#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QString>

class MainMenu : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = 0);
    explicit MainMenu(QString *path, QWidget *parent = 0);
    void display(int sw, int sh);

private:
    int screenHeight;
    int screenWidth;
    QString *imgPath;

signals:
    
public slots:
    void makeGame();
    void makeHighscore();
    void customImage();
    void cancel();
    
};

#endif // MAINMENU_H
