#include <QGraphicsItemGroup>
#include <QGraphicsItem>
#include <QPainterPath>
#include <QBrush>
#include <QPen>
#include <QColor>

class Tile : public QGraphicsItemGroup {
private:
    QGraphicsRectItem *rect = nullptr;
    int tileType = -1;
    bool walkable = 1;
public:
    Tile(int, QGraphicsItem * = nullptr);
    ~Tile();
    virtual QPainterPath shape();
    virtual bool collidesWithItem(const QGraphicsItem *, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const;
    int getTileType();
    bool getWalkable();
    QGraphicsRectItem *getRect();
};