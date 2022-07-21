#include "Node.h"

Node::Node(double gcost, double hcost, int mapx, int mapy, char direction){
    fcost = gcost + hcost;
    this->gcost = gcost;
    this->hcost = hcost;
    this->mapx = mapx;
    this->mapy = mapy;
    prev = nullptr;
    this->direction = direction;
}

double Node::getGCost(){
    return gcost;
}

Node* Node::getPrevNode(){
    return prev;
}

int Node::getMapX(){
    return mapx;
}

int Node::getMapY(){
    return mapy;
}

void Node::setPrevNode(Node *prev){
    this->prev = prev;
}

bool Node::operator>(const Node &other) const{
    printf("1: %lf\n", fcost);
    printf("2: %lf\n", other.fcost);
    return fcost > other.fcost;
}

char Node::getDirection(){
    return direction;
}

bool Node::isChecked(){
    return checked;
}

void Node::setChecked(){
    checked = true;
}

double Node::getFCost(){
    return fcost;
}
