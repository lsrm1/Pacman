#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    escena = new QGraphicsScene();
    ui->graphicsView->setScene(escena);
    escena->setSceneRect(0,0,895,715);

    escena->setBackgroundBrush(Qt::black);

    Laberinto();

    pac = new pacman;
    escena->addItem(pac);

    phantom = new Fantasma;
    escena->addItem(phantom);

    timeanima = new QTimer();
    timeghost = new QTimer();

    connect(timeanima,SIGNAL(timeout()),this,SLOT(movimiento()));
    timeanima->start(50);

    connect(timeghost,SIGNAL(timeout()),this,SLOT(movghost()));
    timeghost->start(80);

    int puntuacion = 0;


    Puntos.push_back(new punto(20,20));
    escena->addItem(Puntos.back());
    Puntos.push_back(new punto(20,30));
    escena->addItem(Puntos.back());
    Puntos.push_back(new punto(20,40));
    escena->addItem(Puntos.back());
    Puntos.push_back(new punto(20,50));
    escena->addItem(Puntos.back());
    Puntos.push_back(new punto(20,60));
    escena->addItem(Puntos.back());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::keyPressEvent(QKeyEvent *evento)
{
    if(evento->key() == Qt::Key_H ) tecla = "H";
    else if(evento->key() == Qt::Key_N ) tecla = "N";
    else if(evento->key() == Qt::Key_B ) tecla = "B";
    else if(evento->key() == Qt::Key_M ) tecla = "M";
}

void MainWindow::movimiento(){

    if (tecla== "H"){
       pac->setRotation(270);
        pac->MoveUp();
    }

    if (tecla == "N"){
        pac->setRotation(90);
        pac->MoveDown();
    }
    if (tecla == "B"){
        pac->setRotation(180);
        pac->MoveLeft();
    }
    if (tecla == "M"){
        pac->setRotation(0);
        pac->MoveRight();
    }

    if(EvaluarColision()){

        if (tecla == "H")
            pac->MoveDown();

        if (tecla == "N")
            pac->MoveUp();

        if (tecla == "B")
            pac->MoveRight();

        if (tecla == "M")
            pac->MoveLeft();

    }

    if(Comermoneda())
        {
            aumentarPunt();
        }

}

void MainWindow::movghost()
{
    if (phantom->posx < pac->posx){
          phantom->MoveRight();
           if(EvaluarColisionghost())
               phantom->MoveLeft();
    }

    else if (phantom->posx > pac->posx){
          phantom->MoveLeft();
          if(EvaluarColisionghost())
              phantom->MoveRight();

    }

    if (phantom->posy > pac->posy){
          phantom->MoveUp();
          if(EvaluarColisionghost())
              phantom->MoveDown();

    }

    else if (phantom->posy < pac->posy){
          phantom->MoveDown();
          if(EvaluarColisionghost())
              phantom->MoveUp();

    }

    if (phantom->collidesWithItem(pac)){
        pac->Muere();
        timeghost->stop();
        timeanima->stop();
    }

}

bool MainWindow::EvaluarColision()
{
    QList<pared*>::iterator it;

    for ( it = Paredes.begin(); it != Paredes.end(); it++){

        if((*it)->collidesWithItem(pac)){

            return true;

        }
    }

    return false;

}

bool MainWindow::EvaluarColisionghost()
{
    QList<pared*>::iterator i;

    for ( i = Paredes.begin(); i != Paredes.end(); i++){

        if((*i)->collidesWithItem(phantom)){

            return true;

        }
    }

    return false;
}

bool MainWindow::Comermoneda()
{
    for (int i = 0;i < Puntos.size();i++) {

       if(pac->collidesWithItem(Puntos.at(i))){
           escena->removeItem(Puntos.at(i));
           Puntos.removeAt(i);
           return true;

        }
    }

    return false;
}

void MainWindow::aumentarPunt()
{
    puntuacion += 5;
    ui->lcdNumber->display(puntuacion);
}

void MainWindow::Laberinto()
{
    ifstream mapa;
    int x, y, w, h;
    mapa.open("mapa.txt");

    while (mapa.good()){

        mapa >> x;
        mapa >> y;
        mapa >> w;
        mapa >> h;

        Paredes.push_back(new pared(x,y,w,h));
        escena->addItem(Paredes.back());
    }
    mapa.close();
}






