#include "tile.h"

Tile::Tile(int tileType, QGraphicsItem *parent) : QGraphicsItemGroup(parent) {
    this->tileType = tileType;
    rect = new QGraphicsRectItem(-25, -25, 50, 50, this);
    rect->setPen(QPen(Qt::NoPen));
    // temporary values
    if (tileType == 0) { // walkable 
        // rect->setBrush(QBrush(QColor(0, 200, 0)));
        // walkable = 1;
    } else if (tileType == 1) { // not walkable
        rect->setBrush(QBrush(QColor(0,0,0)));
        walkable = 0;
    } else { // Invalid type
        rect->setBrush(QBrush(QColor(255,0,255)));
        walkable = 0;
    }
}

Tile::~Tile() {
    delete rect;
}

QPainterPath Tile::shape() {
    return rect->shape();
}

QGraphicsRectItem *Tile::getRect(){
    return rect;
}

bool Tile::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const {
    return rect->collidesWithItem(other, mode);
}

int Tile::getTileType() {
    return tileType;
}

bool Tile::getWalkable() {
    return walkable;
}