#ifndef SCENE_H
#define SCENE_H
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "GameController.h"

class Scene : public QGraphicsScene {
protected:

public:
   Scene () : QGraphicsScene() {


       QGraphicsTextItem *box = new QGraphicsTextItem("demo");
       this->addItem(box);

   }
};

#endif // SCENE_H
