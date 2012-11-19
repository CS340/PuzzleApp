#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>

class MainMenu : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = 0);
    void display(int sw, int sh);

private:
    int screenHeight;
    int screenWidth;

signals:
    
public slots:
    void makeGame();
    void makeHighscore();
    void customImage();
    void cancel();
    void customImageChosen(QString path);
    
};

#endif // MAINMENU_H
