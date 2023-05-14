#ifndef PUNTO_H
#define PUNTO_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>

class punto: public QGraphicsItem
{
    int posx;
    int posy;
    int radio = 5;

public:
    punto(int x, int y);
    QRectF boundingRect() const ;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};
#endif // PUNTO_H
