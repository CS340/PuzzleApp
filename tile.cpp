#include "tile.h"

Tile::Tile(int x, int y, const QIcon & icon, QWidget * parent) : QPushButton(icon, "", parent)
{
    this->x = x;
    this->y = y;
    connect(this, SIGNAL(clicked()), this, SLOT(onClick()));
}

Tile::Tile()
{

}

Tile::~Tile()
{

}
