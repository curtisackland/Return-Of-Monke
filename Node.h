#ifndef NODE_H
#define NODE_H

#include <stdio.h>

class Node{
    public:
        Node(double gcost, double hcost, int mapx, int mapy, char direction);
        //Node::get
        bool operator>(const Node&) const;
        double getGCost();
        Node* getPrevNode();
        void setPrevNode(Node *prev);
        int getMapX();
        int getMapY();
        char getDirection();
        bool isChecked();
        void setChecked();
        double getFCost();
    private:
        double fcost = 0;
        double hcost = 0;
        double gcost = 0;
        int mapx;
        int mapy;
        Node *prev;
        char direction;
        bool checked = false;
};

#endif