#ifndef HIGHSCORESCREEN_H
#define HIGHSCORESCREEN_H

#include <QWidget>
#include <QTcpSocket>
#include <QLabel>

class HighscoreScreen : public QWidget
{
    Q_OBJECT
public:
    explicit HighscoreScreen(QWidget *parent = 0);
    void display(int screenWidth, int screenHeight);
    
private:
    void test();
    void makeCon();
    QString parseResponse(QString s);

    QTcpSocket *socket;
    bool all;
    bool checkNext;
    QString myScoreString;
    QString allScoreString;
    QLabel *allScoreLabel;
    QLabel *myScoreLabel;

signals:
    
private slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void mineScores();
    void allScores();
    void refresh();
};

#endif // HIGHSCORESCREEN_H
