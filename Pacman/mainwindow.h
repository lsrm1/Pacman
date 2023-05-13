#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <pared.h>
#include <QList>
#include <fstream>
#include <string>
#include <iostream>
#include <pacman.h>
#include <QKeyEvent>
#include "punto.h"
#include "fantasma.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//signals:
    //void aviso();

public slots:

    void movimiento();
    void movghost();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *escena;

    pacman *pac;
    Fantasma *phantom;

    QTimer *timeanima;
    QTimer *timeghost;

    QString tecla;

    QList<pared*>Paredes;
    QList<punto*>Puntos;


    bool EvaluarColision();
    bool EvaluarColisionghost();

    void keyPressEvent(QKeyEvent *evento);
    bool Comermoneda();
    int puntuacion;
    void Laberinto();
    void aumentarPunt();

};
#endif // MAINWINDOW_H
