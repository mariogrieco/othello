#ifndef CIRCULO_H
#define CIRCULO_H

#include <QGraphicsEllipseItem>

class Circulo : public QGraphicsEllipseItem {

protected:

    int radio;
    QColor *color;
    bool type;

    // true white
    // false black

//    void mousePressEvent(QGraphicsSceneMouseEvent *event)
//    {
//        qDebug() << "Custom item clicked." ;
//    }

public:
    Circulo () : QGraphicsEllipseItem () {
        this->radio = 70;
        this->type = false;
    }

    void setRadio (int r) {
        this->radio = r;
    }

    int getRadio () {
        return this->radio;
    }

    void setType (bool type) {
        this->type = type;
        if (this->type) {
            this->color = new QColor(255, 255, 255, 255);
            this->setBrush(*this->color);
        }else {
            this->color = new QColor(44, 44, 44, 255);
            this->setBrush(*this->color);
        }
    }

    bool getType () {
        return this->type;
    }

    void setCircle (int x, int y) {
        this->setRect(x, y, this->radio, this->radio);
    }

    void colorete (int r, int g, int b, int a) {
        this->color = new QColor(r, g, b, a);
        this->setBrush(*this->color);
    }
};


#endif // CIRCULO_H
