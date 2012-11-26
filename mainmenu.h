#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QString>
#include <vector>
#include <QLabel>
#include <QGridLayout>

class MainMenu : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = 0);
    explicit MainMenu(QString path, QWidget *parent = 0);
    void display(int sw, int sh);

private:
    int screenHeight;
    int screenWidth;
    int pathsIndex;
    QLabel *imageLabel;
    std::vector<QString> paths;
    QGridLayout *layout;

signals:
    
public slots:
    void makeGame();
    void makeMultiplayerGame();
    void makeHighscore();
    void customImage();
    void cancel();
    void left();
    void right();
    
};

#endif // MAINMENU_H
