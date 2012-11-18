#include "tile.h"

Tile::Tile(int x, int y, const QIcon & icon, QWidget * parent) : QPushButton(icon, "", parent)
{
    //qDebug("NEW_TILE");
    this->x = x;
    this->y = y;
    initX = x;
    initY = y;
    QObject::connect(this, SIGNAL(clicked()), this, SLOT(onClick()));
}

Tile::Tile(const QString &text) : QPushButton(text)
{

}


Tile::Tile()
{

}

Tile::~Tile()
{

}

int Tile::getX()
{
    return this->x;
}

int Tile::getY()
{
    return this->y;
}

int Tile::getInitX()
{
    return initX;
}

int Tile::getInitY()
{
    return initY;
}

void Tile::setX(int a)
{
    this->x = a;
}

void Tile::setY(int a)
{
    this->y = a;
}

