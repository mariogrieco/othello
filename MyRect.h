#ifndef MYRECT_H
#define MYRECT_H

#include <QGraphicsRectItem>
#include <QDebug>
#include "Scene.h"
#include "Tablero.h"
#include "Circulo.h"
#include "GameController.h"

class MyRect : public QGraphicsRectItem {

protected:
    int alto;
    QColor* color;
    Circulo *circle;
    Scene *sceneRef;
    bool canMove;
    GameController *controller;
    int mx;
    int my;

    void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
       if (this->canMove) {
           Circulo *item = new Circulo();
           int r = item->getRadio();
           int altoRect = this->getAlto();

           int posx, posy;
           r = (altoRect-r)/2;
           posx = (this->getMx() * altoRect) + r;
           posy = (this->getMy() * altoRect) + r;

           this->circle = item;
           item->setCircle(posx, posy);
           item->setType(GameController::round);
           this->canMove = false;
           this->scene()->addItem(item);
           controller->toggleRound();
           this->lastMovex = this->getMx();
           this->lastMovey = this->getMy();
       }
       this->lastMovexp = this->getMx();
       this->lastMoveyp = this->getMy();
    }

public:
    static int lastMovex;
    static int lastMovexp;
    static int lastMoveyp;
    static int lastMovey;

    MyRect () : QGraphicsRectItem () {
        controller = new GameController();
        this->alto = 80;
        this->color = new QColor(10, 150, 20, 255);
        this->setBrush(*this->color);
        this->mx = 0;
        this->my = 0;
        this->canMove = false;
        this->circle = NULL;
    }

    void pcMove () {
//        if (this->canMove) {
            Circulo *item = new Circulo();
            int r = item->getRadio();
            int altoRect = this->getAlto();

            int posx, posy;
            r = (altoRect-r)/2;
            posx = (this->getMx() * altoRect) + r;
            posy = (this->getMy() * altoRect) + r;

            this->circle = item;
            item->setCircle(posx, posy);
            item->setType(GameController::round);
            this->canMove = false;
            this->scene()->addItem(item);
            controller->toggleRound();
            this->lastMovex = this->getMx();
            this->lastMovey = this->getMy();
//        }
        this->lastMovexp = this->getMx();
        this->lastMoveyp = this->getMy();
    }

   void setMx (int mx) {
        this->mx = mx;
    }

    void setMy (int my) {
       this->my = my;
    }

    int getMx() {
        return this->mx;
    }

    int getMy() {
       return this->my;
    }

    void setCanMove (bool seto){
        this->canMove = seto;
               if (!seto) {
                   this->setOriginalColor();
               }
               else
               {
                   this->setHoverColor();
               }
    }

    void setMcoords (int x, int y) {
        this->mx = x;
        this->my = y;
    }

    void setCircle (Circulo* circle, int x, int y) {
        this->circle = circle;
        this->mx = x;
        this->my = y;
    }

    void setHoverColor () {
        this->color = new QColor(10, 150, 20, 180);
        this->setBrush(*this->color);
    }

    void setOriginalColor () {
       this->color = new QColor(10,150,20,255);
       this->setBrush(*this->color);
    }

    void setAlto (int alto) {
       this->alto = alto;
    }

    int getAlto() {
       return this->alto;
    }

    void setMyRect (int x, int y) {
       this->setRect(x, y, this->alto, this->alto);
    }

    Circulo* getCircle () {
       return this->circle;
    }

    void setColorete (int r, int g, int b, int a) {
       this->color = new QColor(r, g, b, a);
       this->setBrush(*this->color);
    }

    bool getCanMove () {
       return this->canMove;
    }
};

int MyRect::lastMovex = 0;
int MyRect::lastMovexp = 0;
int MyRect::lastMoveyp = 0;
int MyRect::lastMovey = 0;

#endif // MYRECT_H
