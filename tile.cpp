//AUTHORS: Matt Dumford, Anthony Phelps

#include "tile.h"

// tiles are a custom QPushButton that can send a signal with a pointer to
// themselves when clicked. they also hold their x and y positions in the grid.
Tile::Tile(int x, int y, const QIcon & icon, QWidget * parent) : QPushButton(icon, "", parent)
{
    this->x = x;
    this->y = y;
    initX = x;
    initY = y;

    //custom signal to send a pointer to itself
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

//get the x position of the tile
int Tile::getX()
{
    return this->x;
}

//get the y position of the tile
int Tile::getY()
{
    return this->y;
}

//get the initial x position of the tile
int Tile::getInitX()
{
    return initX;
}

//get the initial y position of the tile
int Tile::getInitY()
{
    return initY;
}

//set the x position of the tile
void Tile::setX(int a)
{
    this->x = a;
}

//set the y position of the tile
void Tile::setY(int a)
{
    this->y = a;
}

