#ifndef MENU_H
#define MENU_H

#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsView>
#include <QMainWindow>
#include <QDebug>

class menu : public QMainWindow
{
    Q_OBJECT

    QPushButton *dosJugadores;
    QPushButton *jugarIA;
    QPushButton *creditos;
    QPushButton *retornarMenuB;

    QGraphicsView* vistaJuego;
    QGraphicsView* vistaMenu;
    QGraphicsScene *scene;

    QGraphicsView* vistaCreditos;
    QGraphicsScene *sceneCreditos;

public:
    menu(QWidget *parent=0) :
        QMainWindow(parent){



    }

    void show();

private slots:
   void jugar(){
        vistaMenu->close();

       Scene *scene = new Scene();
       Tablero *tablero = new Tablero();
       tablero->setScene(scene);

       tablero->paintTablero();
       tablero->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
       tablero->show();
   }

   void jugarVsIA(){
qDebug() << "ksi profe";

   }

   void creditosMuestra(){
qDebug() << "Mariito";

   }

   void retornarMenu(){


   }
};

#endif // MENU_H
