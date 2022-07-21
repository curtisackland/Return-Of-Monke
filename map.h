
#ifndef MAP_H
#define MAP_H

#include <QGraphicsItemGroup>
#include <QGraphicsItem>
#include <QPoint>
#include <vector>
#include "tile.h"

class Map : public QGraphicsItemGroup{

    private:
        int mapWidth;
        int mapLength;
        Tile ***map;
        QGraphicsRectItem *ground = nullptr;
    public:
        Map(int width, int length, QGraphicsItem *parent = nullptr);
        ~Map();
        std::vector<QPoint*> enemySpawnLocations();
        std::vector<QPoint*> dropSpawnLocations();
        Tile*** getMap();
        int getMapWidth();
        int getMapLength();
};

#endif