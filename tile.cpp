#include "tile.h"

Tile::Tile(int x, int y, const QIcon & icon, QWidget * parent) : QPushButton(icon, "", parent)
{
    qDebug("NEW_TILE");
    this->x = x;
    this->y = y;
    QObject::connect(this, SIGNAL(clicked()), this, SLOT(onClick()));
}

Tile::Tile()
{

}

Tile::~Tile()
{

}

/*void Tile::onClick(){
    emit tileClicked(this);
}*/
