#include "fantasma.h"

Fantasma::Fantasma(QObject *parent) : QObject(parent)
{
    timer = new QTimer();
    filas = 0;
    columnas = 0;
    pixmap = new QPixmap(":/Imagenes/fantasma.png");

    posy = 336;
    posx = 442;
    velocidad = 5;
    setPos(posx,posy);

    ancho = 27.5;
    alto = 24;
    timer->start(220);

    connect(timer,&QTimer::timeout,this,&Fantasma::Actualizacion);

}

QRectF Fantasma::boundingRect() const
{
    return QRectF(-ancho/2,-alto/2,ancho,alto);
}

void Fantasma::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    option = nullptr;
    widget = nullptr;
    painter->drawPixmap(-ancho/2,-alto/2,*pixmap,columnas,0,ancho,alto);
}

void Fantasma::Actualizacion()
{
    columnas += 27.5;
    if(columnas >= 110){
        columnas = 0;
    }
    this->update(-ancho/2,-alto/2,ancho,alto);
}

void Fantasma::MoveUp()
{
    posy=posy-velocidad;
    setPos(posx, posy);
}

void Fantasma::MoveDown()
{
    posy = posy + velocidad;
    setPos(posx, posy);
}

void Fantasma::MoveLeft()
{
    posx = posx - velocidad;
    setPos(posx, posy);
}

void Fantasma::MoveRight()
{
    posx = posx + velocidad;
    setPos(posx, posy);
}
