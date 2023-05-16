#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    // Escena
    escena = new QGraphicsScene();
    ui->graphicsView->setScene(escena);
    escena->setSceneRect(0,0,970,715);
    escena->setBackgroundBrush(Qt::black);

    //Pacman y Fantasma
    pac = new pacman;
    escena->addItem(pac);

    phantom = new Fantasma;
    escena->addItem(phantom);


    //Movimiento continuo
    timeanima = new QTimer();
    timeghost = new QTimer();

    connect(timeanima,SIGNAL(timeout()),this,SLOT(movimiento()));
    timeanima->start(50);
    connect(timeghost,SIGNAL(timeout()),this,SLOT(movghost()));
    timeghost->start(80);


    //Laberinto y puntos
    CrearLaberinto();
    CrearPuntos();


    int puntuacion = 0;


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CrearLaberinto() // Recibe un txt con posiciones, ancho y alto
{
    ifstream mapa;
    int x, y, ancho, alto;
    mapa.open("mapa.txt");

    while (mapa.good()){

        mapa >> x;
        mapa >> y;
        mapa >> ancho;
        mapa >> alto;

        Paredes.push_back(new pared(x,y,ancho,alto));
        escena->addItem(Paredes.back());
    }
    mapa.close();
}

void MainWindow::CrearPuntos() // Recibe un txt con posiciones
{
    ifstream score;
    int x, y;
    score.open("puntos.txt");

    while (score.good()){

        score >> x;
        score >> y;

        Puntos.push_back(new punto(x,y));
        escena->addItem(Puntos.back());
    }
    score.close();
}

void MainWindow::keyPressEvent(QKeyEvent *evento)
{
    if(evento->key() == Qt::Key_W) tecla = "W";
    else if(evento->key() == Qt::Key_S ) tecla = "S";
    else if(evento->key() == Qt::Key_A ) tecla = "A";
    else if(evento->key() == Qt::Key_D) tecla = "D";
}

void MainWindow::movimiento(){ //Movimiento Pacman

    if (tecla == "W"){
       pac->setRotation(270);
        pac->MoveUp();
    }

    if (tecla == "S"){
        pac->setRotation(90);
        pac->MoveDown();
    }
    if (tecla == "A"){
        pac->setRotation(180);
        pac->MoveLeft();
    }
    if (tecla == "D"){
        pac->setRotation(0);
        pac->MoveRight();
    }

    if(EvaluarColision()){

        if (tecla == "W") pac->MoveDown();

        if (tecla == "S") pac->MoveUp();

        if (tecla == "A") pac->MoveRight();

        if (tecla == "D") pac->MoveLeft();

    }

    if(Comerpunto())
        aumentarPunt();

}

void MainWindow::movghost() //Movimiento fantasma
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

bool MainWindow::EvaluarColision() // Colision Pacman-Pared
{
    QList<pared*>::iterator it;

    for ( it = Paredes.begin(); it != Paredes.end(); it++){

        if((*it)->collidesWithItem(pac))
            return true;
    }
    return false;

}

bool MainWindow::EvaluarColisionghost()// Colision Fantasma-    Pared
{
    QList<pared*>::iterator i;

    for ( i = Paredes.begin(); i != Paredes.end(); i++){

        if((*i)->collidesWithItem(phantom))
            return true;
    }

    return false;
}

bool MainWindow::Comerpunto(){

    for (int i = 0;i < Puntos.size();i++) {

        if(pac->collidesWithItem(Puntos.at(i))){

            escena->removeItem(Puntos.at(i));
            Puntos.removeAt(i);
            return true;

        }
    }
    return false;
}

void MainWindow::aumentarPunt(){
    puntuacion += 5;
    ui->lcdNumber->display(puntuacion);
}








