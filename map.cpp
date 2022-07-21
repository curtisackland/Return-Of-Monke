#include "map.h"

Map::Map(int width, int length, QGraphicsItem *parent) : QGraphicsItemGroup(parent){
    mapWidth = width;
    mapLength = length;
    map = new Tile**[width];
    for(int i = 0; i < width; i++){
        map[i] = new Tile*[length];
        for(int j = 0; j < length; j++){
            if(i == 0 || i == width - 1 || j == 0 || j == length - 1){
                map[i][j] = new Tile(1, this);
            } else {
                int r = std::rand() % 15;
                if(r == 0){
                    map[i][j] = new Tile(1, this);
                } else {
                    map[i][j] = new Tile(0, this);
                }   
            }
            map[i][j]->setPos(i * 50 + 25, j * 50 + 25);
        }
    }

    ground = new QGraphicsRectItem(50, 50, 5000, 5000, this);
    ground->setPen(QPen(Qt::NoPen));
    // ground->setBrush(QBrush(QColor(0, 200, 0)));
    ground->setZValue(-100);

    QBrush brush;
    brush.setTextureImage(QImage("resources/Map.png"));
    // brush.setTransform(transform);
    ground->setBrush(brush);

}

Map::~Map(){

}

std::vector<QPoint*> Map::enemySpawnLocations(){

}

std::vector<QPoint*> Map::dropSpawnLocations(){

}

Tile*** Map::getMap(){
    return map;
}

int Map::getMapWidth() {
    return mapWidth;
}

int Map::getMapLength() {
    return mapLength;
}