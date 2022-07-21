/**
 * @file drop.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef DROP_H
#define DROP_H

#include <QGraphicsItemGroup>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <string.h>
#include <iostream>

class Drop : public QGraphicsItemGroup{
    public:
        enum DropTypes {Health, Shield, Pistol, AR, Laser, RocketLauncher, PistolAmmo, ARAmmo, LaserAmmo, RocketAmmo, ENUM_END};
    private:
        QGraphicsRectItem * drop;
        const double dropSize = 30;
        DropTypes dropType;
    public:
        Drop(double, double, DropTypes, QGraphicsItem * = nullptr);
        ~Drop();
        virtual bool collidesWithItem(const QGraphicsItem*, Qt::ItemSelectionMode mode=Qt::IntersectsItemShape);
        DropTypes getDropType();
        QPainterPath shape() const;
};


#endif