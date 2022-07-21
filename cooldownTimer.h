#ifndef COOLDOWN_TIMER_HEADER
#define COOLDOWN_TIMER_HEADER
#include <QGraphicsItemGroup>
#include <QBrush>

/**
 * @brief timer to show the player how much time is left to cool down
 * 
 */
class CooldownTimer : public QGraphicsItemGroup {
    private:
    QGraphicsEllipseItem *pie = new QGraphicsEllipseItem(this);
    double frac = 0;
    bool hideOnZero = true;

    public:
    CooldownTimer(double, double, double, double, QGraphicsItem *parent = nullptr);
    ~CooldownTimer();
    void setFraction(double);
    double getFraction();
    void setHideOnZero(bool h); 
    void setColor(QBrush b);
};

#endif