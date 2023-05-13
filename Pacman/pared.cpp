#include "pared.h"

pared::pared()
{

}

pared::pared(int x, int y, int w, int h)
{
    this->posx = x ;
    this->posy = y;
    this->w = w;
    this->h = h;
}

QRectF pared::boundingRect() const
{
    return QRectF(posx,posy,w,h);
}

void pared::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    option = nullptr;
    widget = nullptr;
    painter->setBrush(Qt::blue);
    painter->setPen(Qt::blue);
    painter->drawRoundedRect(boundingRect(),6,6);
}
