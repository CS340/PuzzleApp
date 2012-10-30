#ifndef TILE_H
#define TILE_H

#include <QPushButton>

class Tile : public QPushButton
{

Q_OBJECT

public:
    explicit Tile(int x, int y, const QIcon & icon, QWidget *parent = 0);
    explicit Tile();
    virtual ~Tile();
    int getX();
    int getY();
    void setX(int a);
    void setY(int a);

private:
    int x;
    int y;
    int width;
    int height;

signals:
    void tileClicked(Tile*);

private slots:
    void onClick(){
        qDebug("TILE_CLICK");
        emit tileClicked(this);
    }
};

#endif // TILE_H
