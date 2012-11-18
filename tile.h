#ifndef TILE_H
#define TILE_H

#include <QPushButton>

class Tile : public QPushButton
{

Q_OBJECT

public:
    explicit Tile(int x, int y, const QIcon & icon, QWidget *parent = 0);
    explicit Tile(const QString &text);
    explicit Tile();
    virtual ~Tile();
    int getX();
    int getY();
    int getInitX();
    int getInitY();
    void setX(int a);
    void setY(int a);

private:
    int x;
    int y;
    int width;
    int height;
    int initX;
    int initY;

signals:
    void tileClicked(Tile*);

private slots:
    void onClick(){
        //qDebug("TILE_CLICK");
        emit tileClicked(this);
    }
};

#endif // TILE_H
