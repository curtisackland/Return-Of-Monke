/**
 * @file gunInfo.h
 * @author Evan Goldrick (egoldric@uwo.ca)
 * @brief Definition of GunInfo
 * @version 0.1
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef GUN_INFO_HEADER
#define GUN_INFO_HEADER
#include <QGraphicsItemGroup>
#include <QFont>
#include <QFontMetrics>
#include <string>
#include "gun.h"

/**
 * @brief Used to show information about the currently selected gun on the hud
 * 
 */
class GunInfo : public QGraphicsItemGroup {
    private:
    QFont *font;
    QFontMetrics *fm;
    QGraphicsTextItem *weaponType;
    QGraphicsTextItem *ammoCount;
    public:
    GunInfo(double, double, QGraphicsItem *parent = nullptr);
    ~GunInfo();
    void updateGunInformation(Gun *);
};
#endif