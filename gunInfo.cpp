/**
 * @file gunInfo.cpp
 * @author Evan Goldrick (egoldric@uwo.ca)
 * @brief Implementation of GunInfo
 * @version 0.1
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "gunInfo.h"
/**
 * @brief Construct a new Gun Info object
 * 
 * @param x x position of the text (right aligned)
 * @param y y position of the text (top aligned)
 * @param parent parent graphics object
 */
GunInfo::GunInfo(double x, double y, QGraphicsItem *parent) : QGraphicsItemGroup(parent) {
    this->setPos(x, y);
    font = new QFont("Helvetica Neue", 20);
    fm = new QFontMetrics(*font);
    weaponType = new QGraphicsTextItem(this);
    //weaponType->setPos(0, 0);
    weaponType->setFont(*font);
    
    ammoCount = new QGraphicsTextItem(this);
    //ammoCount->setPos(0, fm->height() + 10);
    ammoCount->setFont(*font);
}

/**
 * @brief Destroy the Gun Info object
 * 
 */
GunInfo::~GunInfo() {
    delete font;
    delete fm;
    delete weaponType;
    delete ammoCount;
}

/**
 * @brief update the text to reflect the gun stats
 * 
 * @param gun 
 */
void GunInfo::updateGunInformation(Gun *gun) {
    QString type = QString::fromStdString(gun->getGunType());
    weaponType->setPlainText(type);
    weaponType->setPos(-fm->horizontalAdvance(type), 0);

    QString count("");
    count.append(QString::number(gun->getCurrentMagazineCapacity()));
    count.append("/");
    count.append(QString::number(gun->getAmmoCount()));
    ammoCount->setPlainText(count);
    ammoCount->setPos(-fm->horizontalAdvance(count), fm->height() + 10);
}

