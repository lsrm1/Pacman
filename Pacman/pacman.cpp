#include "pacman.h"

pacman::pacman(QObject *parent) : QObject(parent)
{

    timer = new QTimer();
    filas = 0;
    columnas = 0;
    pixmap = new QPixmap(":/Imagenes/pacman.png");

    posy = 546;
    posx = 442;
    velocidad = 5;
    setPos(posx,posy);

    //dimensiones de la imagen
    ancho = 27.5;
    alto = 25;
    timer->start(220);

    connect(timer,&QTimer::timeout,this,&pacman::Actualizacion);

}


QRectF pacman::boundingRect() const
{
    return QRectF(-ancho/2,-alto/2,ancho,alto);
}

void pacman::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    option = nullptr;
    widget = nullptr;
    painter->drawPixmap(-ancho/2,-alto/2,*pixmap,columnas,0,ancho,alto);
}

void pacman::Actualizacion()
{
    columnas += 27.5;
    if(columnas >= 110){
        columnas = 0;
    }
    this->update(-ancho/2,-alto/2,ancho,alto);
}

void pacman::MoveUp()
{
    posy=posy-velocidad;
    setPos(posx, posy);
}

void pacman::MoveDown()
{
    posy = posy + velocidad;
    setPos(posx, posy);
}

void pacman::MoveLeft()
{
    posx = posx - velocidad;
    setPos(posx, posy);
}

void pacman::MoveRight()
{
    posx = posx + velocidad;
    setPos(posx, posy);
}

void pacman::Muere()
{
    delete pixmap;
    pixmap = new QPixmap(":/Imagenes/muere.png");
}


