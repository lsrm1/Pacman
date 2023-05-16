#ifndef PACMAN_H
#define PACMAN_H

#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QObject>

class pacman: public QObject, public QGraphicsItem
{
public:
    int posx,posy;
    int velocidad;
    float ancho,alto;
    float filas,columnas;

    QTimer *timer;
    QPixmap *pixmap;

public:
    pacman(QObject *parent = nullptr);

    QRectF boundingRect() const ;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
    void Muere();   //Cambia Sprite

public slots:
    void Actualizacion();
    void Morir();

};

#endif // PACMAN_H

