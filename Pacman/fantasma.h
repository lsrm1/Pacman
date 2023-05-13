#ifndef FANTASMA_H
#define FANTASMA_H


#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QObject>

class Fantasma: public QObject, public QGraphicsItem
{
public:
    int posx,posy;
    int velocidad;
    float ancho,alto;
    float filas,columnas;

    QTimer *timer;
    QPixmap *pixmap;

public:
    Fantasma(QObject *parent = nullptr);

    QRectF boundingRect() const ;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();

public slots:
    void Actualizacion();

};

#endif // FANTASMA_H
