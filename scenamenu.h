#ifndef SCENAMENU_H
#define SCENAMENU_H
#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsView>
#include <QMainWindow>

class Scenamenu: public QGraphicsScene
{
public:
    Scenamenu(): QGraphicsScene(){

        QGraphicsTextItem *box = new QGraphicsTextItem("ola");
        this->addItem(box);

        scene= new QGraphicsScene();
        vistaMenu= new QGraphicsView();
        sceneCreditos= new QGraphicsScene();
        vistaCreditos= new QGraphicsView();

        dosJugadores= new QPushButton("2 Jugadores");
        jugarIA= new QPushButton("Jugar contra la PC");
        creditos= new QPushButton("Creditos");
        retornarMenuB= new QPushButton("Ir al Menu");

        vistaMenu->setFixedSize(450,300);
        scene->addWidget(dosJugadores);
        dosJugadores->move(130,100);

        scene->addWidget(creditos);
        creditos->move(142,200);

        scene->addWidget(jugarIA);
        jugarIA->move(112,150);

        connect(dosJugadores, SIGNAL (clicked()), this, SLOT (jugar()));
        connect(jugarIA, SIGNAL (clicked()), this, SLOT (jugarVsIA()));
        connect(creditos, SIGNAL (clicked()), this, SLOT (creditosMuestra()));
        connect(retornarMenuB, SIGNAL (clicked()), this, SLOT (retornarMenu()));
    }
};

#endif // SCENAMENU_H
