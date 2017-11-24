#include "dialog.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "Tablero.h"
#include "MyRect.h"
#include "Scene.h"
#include "Circulo.h"
#include <QKeyEvent>
#include <QLabel>
//#include "menu.h"

/*
    https://www.youtube.com/watch?v=8ntEQpg7gck
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Scene *scene = new Scene();
    Tablero *tablero = new Tablero();
    tablero->setScene(scene);

    tablero->paintTablero();
    tablero->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    tablero->show();

    return a.exec();
}
