#ifndef VIEW_H
#define VIEW_H

class Focus : public QGraphicsItemGroup
{
private:

public:
    void keyPressEvent (QKeyEvent *event){
        qDebug () << "press a key ";
    }

    void mousePressEvent (QKeyEvent *event) {
        qDebug () << "over on ";
    }
};

#endif // VIEW_H
