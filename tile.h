#ifndef TILE_H
#define TILE_H

#include <QPushButton>

class Tile : public QPushButton
{

public:
    explicit Tile(int x, int y, const QIcon & icon, QWidget *parent = 0);
    explicit Tile();
    virtual ~Tile();

private:
    int x;
    int y;
    int width;
    int height;

signals:
    void tileClicked(Tile*);

private slots:
    void onClick(){
        emit tileClicked(this);
    }
};

#endif // TILE_H
