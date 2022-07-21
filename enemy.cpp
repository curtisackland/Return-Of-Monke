/**
 * @file enemy.cpp
 * @author David Lin (dlin72@uwo.ca) Evan Goldrick (egoldric@uwo.ca)
 * @brief 
 * @version 0.1
 * @date 2021-11-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "enemy.h"

/**
 * @brief constructor initializes position and direction of enemy
 * @param name name of enemy
 * @param initialX initial x pos
 * @param initialY initial y pos
 * @param initialD initial direction in radians
 * @param hp enemy health
 * @param dmg enemy damage
 * @param speed enemy movement speed
 * @param target Player class
 */
Enemy::Enemy(std::string name, double initialX, double initialY, double initialD, int hp, int damage, double speed, double attackRadius, QGraphicsItem * parent) : QGraphicsItemGroup (parent){
    if (name == "Grunt" || name == "Tank"){
        hitbox_size = 30;
    } else if (name == "Brute"){
        hitbox_size = 50;
    }
    enemy = new QGraphicsRectItem (-(hitbox_size/2), -(hitbox_size/2), hitbox_size, hitbox_size, this);
    this->setPos(initialX, initialY);
    enemy->setRotation(initialD);
    QPen outline;
    outline.setStyle(Qt::NoPen);
    enemy->setPen(outline);

    QTransform transform;
    transform.translate(-(hitbox_size/2), -(hitbox_size/2));

    QBrush brush;
    if (name == "Grunt"){
        brush.setTextureImage(QImage("resources/Grunt.png"));
    } else if (name == "Brute"){
        brush.setTextureImage(QImage("resources/Brute.png")); 
    } else if (name == "Tank"){
        brush.setTextureImage(QImage("resources/Tank.png")); 
    }
    brush.setTransform(transform);
    enemy->setBrush(brush);

    attackRange = new QGraphicsEllipseItem (-attackRadius, -attackRadius, attackRadius * 2, attackRadius * 2, this);

    maxHealth = hp;
    health = hp;
    this->damage = damage;
    movementSpeed = speed;
    this->attackRadius = attackRadius;
    healthBar = new HUDbar(-30, 25, 60, 10, 50, 100, this);
    healthBar->setColor(QBrush(QColor(255,0,0,200)));
    healthBar->setMax(maxHealth);
}
/**
 * @brief destructor
 */
Enemy::~Enemy(){

}

/**
 * @brief changes enemy location to chase the player
 * @param target player class that contains the player's location
 */
void Enemy::move(QPoint player, Map *map) {
    /*
    for (int x = 0; x < 102; ++x) {
        for (int y = 0; y < 102; ++y) {
            map->getMap()[x][y]->getRect()->setBrush(QBrush(QColor(0, 0, 0, 0)));
        }
    }*/
    std::list<Node*> fringe;
    bool foundPlayer = false;
    Node *startNode = new Node(0, sqrt((player.x() - this->x())*(player.x() - this->x()) + (player.y() - this->y())*(player.y() - this->y()))/50, (int) floor(this->x()/50), (int) floor(this->y()/50), '0');
    int mapPlayerXpos = (int) floor(player.x()/50);
    int mapPlayerYpos = (int) floor(player.y()/50);
    fringe.push_back(startNode);
    std::set<int> visited;
    Node *playerNode;
    while(!foundPlayer){
        if (fringe.empty()) {
            printf("No nodes left: pathfinding error\n");
            break;
        }
        Node *currentNode = nullptr;
        double lowestFCost = INFINITY;
        for (Node *n : fringe) {
            if (n->getFCost() < lowestFCost) {
                currentNode = n;
                lowestFCost = n->getFCost();
            }
        }
        visited.insert(currentNode->getMapY()*map->getMapWidth() + currentNode->getMapX());
        fringe.remove(currentNode);
        //printf("%d\n", currentNode->getMapX());
        //printf("%d\n", currentNode->getMapY());
        if(map->getMap()[currentNode->getMapX()][currentNode->getMapY()] == map->getMap()[mapPlayerXpos][mapPlayerYpos]){
            foundPlayer = true;
            playerNode = currentNode;
        } else {
            //printf("X: %d | Y: %d\n", currentNode->getMapX(), currentNode->getMapY());
            if(map->getMap()[currentNode->getMapX() + 1][currentNode->getMapY()]->getWalkable() && !visited.count(currentNode->getMapY()*map->getMapWidth() + (currentNode->getMapX() + 1))){
                //map->getMap()[currentNode->getMapX() + 1][currentNode->getMapY()]->getRect()->setBrush(QBrush(QColor(255, 0, 0)));
                //printf("1\n");
                
                double x = currentNode->getMapX() + 1;
                double y = currentNode->getMapY();
                //printf("%lf\n", (player.x()-x)*(player.x()-x) + (player.y()-y)*(player.y()-y));
                Node *tempNode = new Node(currentNode->getGCost() + 1, abs((int) floor(player.x()/50) - x) + abs((int) floor(player.y()/50) - y), currentNode->getMapX() + 1, currentNode->getMapY(), 'E');
                tempNode->setPrevNode(currentNode);
                fringe.push_back(tempNode);
            }
            if(map->getMap()[currentNode->getMapX() - 1][currentNode->getMapY()]->getWalkable() && !visited.count(currentNode->getMapY()*map->getMapWidth() + (currentNode->getMapX() - 1))){
                //map->getMap()[currentNode->getMapX() - 1][currentNode->getMapY()]->getRect()->setBrush(QBrush(QColor(255, 0, 0)));
                //printf("2\n");
                double x = currentNode->getMapX() - 1;
                double y = currentNode->getMapY();
                Node *tempNode = new Node(currentNode->getGCost() + 1, abs((int) floor(player.x()/50) - x) + abs((int) floor(player.y()/50) - y), currentNode->getMapX() - 1, currentNode->getMapY(), 'W');
                tempNode->setPrevNode(currentNode);
                fringe.push_back(tempNode);
            }
            if(map->getMap()[currentNode->getMapX()][currentNode->getMapY() + 1]->getWalkable() && !visited.count((currentNode->getMapY() + 1)*map->getMapWidth() + (currentNode->getMapX()))){
                //map->getMap()[currentNode->getMapX()][currentNode->getMapY() + 1]->getRect()->setBrush(QBrush(QColor(255, 0, 0)));
                //printf("3\n");
                
                double x = currentNode->getMapX();
                double y = currentNode->getMapY() + 1;
                Node *tempNode = new Node(currentNode->getGCost() + 1, abs((int) floor(player.x()/50) - x) + abs((int) floor(player.y()/50) - y), currentNode->getMapX(), currentNode->getMapY() + 1, 'S');
                tempNode->setPrevNode(currentNode);
                fringe.push_back(tempNode);
            }
            if(map->getMap()[currentNode->getMapX()][currentNode->getMapY() - 1]->getWalkable() && !visited.count((currentNode->getMapY() - 1)*map->getMapWidth() + (currentNode->getMapX()))){
                //printf("4\n");
                //map->getMap()[currentNode->getMapX()][currentNode->getMapY() - 1]->getRect()->setBrush(QBrush(QColor(255, 0, 0)));

                double x = currentNode->getMapX();
                double y = currentNode->getMapY() - 1;
                Node *tempNode = new Node(currentNode->getGCost() + 1, abs((int) floor(player.x()/50) - x) + abs((int) floor(player.y()/50) - y), currentNode->getMapX(), currentNode->getMapY() - 1, 'N');
                tempNode->setPrevNode(currentNode);
                fringe.push_back(tempNode);
            }
        } 
    }
    
    if(playerNode->getPrevNode() == nullptr){
        printf("gottem\n");
    } else {
        Node *nextNode = playerNode;
        char direction = nextNode->getDirection();
        while(nextNode->getPrevNode() != startNode){
            //map->getMap()[nextNode->getMapX()][nextNode->getMapY()]->getRect()->setBrush(QBrush(QColor(0, 0, 255)));
            nextNode = nextNode->getPrevNode();
            direction = nextNode->getDirection();
        }
        if(direction == 'N'){
            setPos(pos().x(), pos().y() - movementSpeed);
        } else if(direction == 'E'){
            setPos(pos().x() + movementSpeed, pos().y());
        } else if(direction == 'S'){
            setPos(pos().x(), pos().y() + movementSpeed);
        } else if(direction == 'W'){
            setPos(pos().x() - movementSpeed, pos().y());
        }
    }

}

/**
 * @brief determines collision with player
 * @param target player
 */
bool Enemy::inRange(Player* target){
    return target->collidesWithItem(attackRange);
}

/**
 * @brief function for the enemy to attack player 
 * @param target player
 */
void Enemy::attack(Player *target){
    if (attackCdTimeleft == 0){
        if (inRange(target)){
            if (name == "Tank"){
                // Code to shoot at player
            } 
            else {
                target->hit(damage);
                attackCdTimeleft = attackCdFullTime;
            }
        }
    }
}

/**
 * @brief checks if the enemy is colliding with the passed object
 * @param other object that is checking collision with
 * @param mode specifies the type of collision
 * @return true if there is a collision
 * @return false if there is no collision
 */
bool Enemy::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const {
    return enemy->collidesWithItem(other, mode);
}

/**
 * @brief takes away from enemy's health when called, dies when health reaches 0
 * @param dmg the amount that is taken away
 */
void Enemy::hit(int dmg){
    health = health - dmg;
}

/**
 * @brief gets the enemy's health
 * @return the enemy's health
 */
int Enemy::getHealth(){
    return health;
}

/**
 * @brief Function to check if the enemy is dead based on its current health
 * 
 * @return true the enemy's health is less than or equal to 0
 * @return false the enemy's health is greater than 0
 */
bool Enemy::isDead() {
    return health <= 0;
}

/**
 * @brief change the time it takes to cool down an attack
 * 
 * @param cd new cooldown value
 */
void Enemy::setCooldownLength(int cd) {
    attackCdFullTime = cd;
}

/**
 * @brief cools down abilities
 * 
 */
void Enemy::cooldown() {
    // Cooldown timers
    if (attackCdTimeleft > 0) {
        --attackCdTimeleft;
    } else {
        attackCdTimeleft = 0;
    }

    // 
    healthBar->setCurrent(health);
}

QPainterPath Enemy::shape() const {
    return enemy->shape();
}