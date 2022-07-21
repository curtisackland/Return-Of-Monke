#ifndef DEATH_SCREEN_H
#define DEATH_SCREEN_H
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItemGroup>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <view.h>
#include "menuButton.h"
#include "leaderboard.h"
#include <QInputDialog>
#include <QDialog>
/**
 * @brief Creates a death screen
 * 
 */
class DeathScreen{
    public:
        explicit DeathScreen(int finalScore);
        ~DeathScreen();
};

#endif