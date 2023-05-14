#include "punto.h"

punto::punto(int x, int y)
{
    this-> posx = x;
    this-> posy = y;
    setPos(posx,posy);
}

QRectF punto::boundingRect() const
{
    return QRectF(posx,posy,2*radio,2*radio);
}

void punto::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    option = nullptr;
    widget = nullptr;

    painter->setBrush(Qt::white);
    painter->drawEllipse(boundingRect());
}
