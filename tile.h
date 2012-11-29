#ifndef TILE_H
#define TILE_H

//AUTHORS: Matt Dumford, Anthony Phelps

#include <QPushButton>


// tiles are a custom QPushButton that can send a signal with a pointer to
// themselves when clicked. they also hold their x and y positions in the grid.
class Tile : public QPushButton
{

Q_OBJECT

public:
    explicit Tile(int x, int y, const QIcon & icon, QWidget *parent = 0);
    explicit Tile(const QString &text);
    explicit Tile();
    virtual ~Tile();
    int getX(); //get the x position of the tile
    int getY(); //get the y position of the tile
    int getInitX(); //get the initial x position of the tile
    int getInitY(); // get the initial y position of the tile
    void setX(int a); //set the x position of the tile
    void setY(int a); //set the y position of the tile

private:
    int x;
    int y;
    int width;
    int height;
    int initX;
    int initY;

signals:
    void tileClicked(Tile*); //custom signal emitted whenever the tile
                             //detects its own clicked()

private slots:
    void onClick(){
        emit tileClicked(this);
    }
};

#endif // TILE_H
