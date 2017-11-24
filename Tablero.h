#ifndef TABLARO_H
#define TABLARO_H

#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "MyRect.h"
#include "GameController.h"
#include "Circulo.h"

using namespace std;

class Tablero : public QGraphicsView {
protected:
    QGraphicsTextItem *Puntajes, *jug1, *jug2, *turno, *pj1, *pj2, *ganador;

    void mousePressEvent(QMouseEvent *event) {

        QGraphicsView::mousePressEvent(event);
        this->comer(MyRect::lastMovey, MyRect::lastMovex, !GameController::round);
        this->refTablero[MyRect::lastMovey][MyRect::lastMovex].setColorete(0,0,0,255);
        this->Contar();
        if((this->validateMoves(GameController::round) ) ==0){
            qDebug() << "pasa turno";
            if(GameController::round){
                GameController *k;
                k= new GameController(true);
                k->toggleRound();
                this->validateMoves(GameController::round);

            }else{
                GameController *k;
                k= new GameController(false);
                k->toggleRound();
                this->validateMoves(GameController::round);
            }


        }
        else{

            this->refTablero[MyRect::lastMoveyp][MyRect::lastMovexp].setColorete(120,49,30, 255);
            if (this->refTablero[MyRect::lastMoveyp][MyRect::lastMovexp].getCircle()) {
                if (this->refTablero[MyRect::lastMoveyp][MyRect::lastMovexp].getCircle()->getType()) {
                    this->refTablero[MyRect::lastMoveyp][MyRect::lastMovexp].getCircle()->colorete(255, 255, 255, 190);
                }
                else {
                    this->refTablero[MyRect::lastMoveyp][MyRect::lastMovexp].getCircle()->colorete(44, 44, 44, 190);
                }
            }
        }

        if (!this->bandPC) {
                int x = 0;
                int y = 0;
               while (!this->refTablero[x][y].getCanMove()) {
                    x = rand()%8;
                    y = rand()%8;
               }

               this->refTablero[x][y].pcMove();
               this->comer(x, y, !GameController::round);
               this->Contar();
               this->validateMoves(GameController::round);
        }
    }

public:
    QColor *color;
    int dim;
    MyRect **refTablero;
    bool bandPC;

    Tablero () : QGraphicsView () {
        this->setWindowState(Qt::WindowMaximized);
        this->setBackgroundBrush(QBrush(QColor(125, 45, 25, 255)));
        this->dim = 8;
        this->bandPC = true;
        this->refTablero = new MyRect*[this->dim];
        for (int i = 0; i < this->dim+2; i++) {
            this->refTablero[i] = new MyRect[this->dim+2];
        }
        this->setInitialState();
    }

    void setInitialState () {
        for (int i = 0; i < this->dim+1; i++) {
            for (int x = 0; x < this->dim+1; x++) {
                this->refTablero[i][x].setCircle(NULL, x, i);
            }
        }
    }

    void Contar(){

        int fichasB=0, fichasN=0;
        for(int i=0;i<this->dim;i++){
            for(int j=0;j<this->dim;j++){
                if(this->refTablero[i][j].getCircle()){

                    if(this->refTablero[i][j].getCircle()->getType()){
                        fichasB++;

                    }else{

                        fichasN++;
                    }


                }


            }


        }

       pj1->setPlainText(QString::number(fichasB));
       pj2->setPlainText(QString::number(fichasN));

       if(fichasN+fichasB==64){
        ganador= new QGraphicsTextItem();
        QString aux1;
        ganador->setPos(680,300);
        ganador->setScale(2);
        this->scene()->addItem(ganador);
        if(fichasN>fichasB){
            aux1="Ha ganado negras";
            ganador->setPlainText(aux1);

        }else{
            aux1="ha ganado blancas";
            ganador->setPlainText(aux1);
        }
        //this->scene()->removeItem(turno);
        }

       if(fichasN==0){
           ganador= new QGraphicsTextItem();
           QString aux1;
           ganador->setPos(680,300);
           ganador->setScale(2);
            this->scene()->addItem(ganador);
           aux1="ha ganado blancas";
           ganador->setPlainText(aux1);
           this->scene()->removeItem(turno);
        }
       if(fichasB==0){
           ganador= new QGraphicsTextItem();
           QString aux1;
           ganador->setPos(680,300);
           ganador->setScale(2);
           this->scene()->addItem(ganador);
           aux1="ha ganado negras";
           ganador->setPlainText(aux1);
           this->scene()->removeItem(turno);
       }
        qDebug() << "fichas Blancas: "<<fichasB;
        qDebug() << "fichas Negras: "<<fichasN;

    }

    void addCircle (int x, int y, bool type) {
        Circulo *item = new Circulo();
        int r = item->getRadio();
        int altoRect = this->refTablero[0][0].getAlto();

        int posx, posy;

        r = (altoRect-r)/2;
        posx = (x * altoRect) + r;
        posy = (y * altoRect) + r;

        item->setCircle(posx, posy);
        item->setType(type);
        this->refTablero[y][x].setCircle(item, x, y);
        this->scene()->addItem(item);
    }

    int validateMoves (bool turno) {
        int probar=0;
        for(int i=0; i<this->dim;i++){
            for(int j=0;j<this->dim;j++){
                bool n=false;
                if(cambiar(i,j,turno,n) && ! this->refTablero[i][j].getCircle()){
                    this->refTablero[i][j].setCanMove(true);
                    probar=1;
                }
                else{
                    this->refTablero[i][j].setCanMove(false);
                }
            }
        }

        if(turno){

          this->turno->setPlainText("Juega Blancas");
        }
        else{

          this->turno->setPlainText("Juega Negras");
        }
        return probar;
    }

    void verificar () {
        for(int i=0; i<this->dim;i++){
            for(int j=0;j<this->dim;j++){
                if (this->refTablero[i][j].getCircle()) {
//                    this->refTablero[i][j].getCircle()->colorete(i*10, j*10, j*10, 255);
                    if (this->refTablero[i][j].getCircle()->getType()) {
                      qDebug() << "blanco: " << i << " " << j << " :";
                    }
                    else {
                      qDebug() << "negro: " << i << " " << j << " :";
                    }
                }
//                qDebug() << endl;
            }
        }
    }

    bool cambiar(int yp, int xp, bool turno, bool n){

        int k=0;
        if(xp-1 >=0){

            for(int i=(xp-1);i>=0;i--){
                if(! this->refTablero[yp][i].getCircle() ){

                    break;

                }
                if(turno){
                    if(this->refTablero[yp][i].getCircle()->getType()){
                        while(i<xp ){

                            //    m[yp][i]=2;
                            i++;
                            k++;
                        }
                        if(k>=2)
                            n=true;

                        break;
                    }
                }else{

                    if(! this->refTablero[yp][i].getCircle()->getType()){
                        while(i<xp){
                            //      m[yp][i]=1;
                            i++;
                            k++;
                        }
                        if(k>=2)
                            n=true;
                        break;
                    }
                }
            }
        }

        k=0;
        if(xp+1 < this->dim){
            for(int i=(xp+1);i<8;i++){
                if(! this->refTablero[yp][i].getCircle()){
                    break;

                }
                if(turno){
                    if(this->refTablero[yp][i].getCircle()->getType()){
                        while(i>xp){
                            //m[yp][i]=2;
                            i--;
                            k++;
                        }
                        if(k>=2)
                            n=true;
                        break;
                    }
                }else{


                    if(! this->refTablero[yp][i].getCircle()->getType()){
                        while(i>xp){
                            //  m[yp][i]=1;
                            i--;
                            k++;
                        }
                        if(k>=2)
                            n=true;
                        break;
                    }
                }
            }
        }
        if(yp-1 >=0){

            k=0;
            for(int i=(yp-1);i>=0;i--){
                if(! this->refTablero[i][xp].getCircle()){
                    break;

                }

                if(turno){
                    if(this->refTablero[i][xp].getCircle()->getType()){
                        while(i<yp){
                            //m[i][xp]=2;
                            i++;
                            k++;
                        }
                        if(k>=2)
                            n=true;
                        break;
                    }
                }else{

                    if(! this->refTablero[i][xp].getCircle()->getType()){
                        while(i<yp){
                            //  m[i][xp]=1;
                            i++;
                            k++;
                        }
                        if(k>=2)
                            n=true;
                        break;
                    }
                }
            }
        }
        if(yp+1 < this->dim){
            k=0;
            for(int i=(yp+1);i<8;i++){
                if(! this->refTablero[i][xp].getCircle()){
                    break;

                }
                if(turno){
                    if(this->refTablero[i][xp].getCircle()->getType()){
                        while(i>yp){
                            // m[i][xp]=2;
                            i--;
                            k++;
                        }
                        if(k>=2)
                            n=true;
                        break;
                    }
                }else{

                    if(! this->refTablero[i][xp].getCircle()->getType()){
                        while(i>yp){
                            //   m[i][xp]=1;
                            i--;
                            k++;
                        }
                        if(k>=2)
                            n=true;
                        break;
                    }
                }

            }
        }

        if(xp+1<this->dim && yp+1<this->dim ){

            int j=xp+1;
            k=0;
            for(int i=(yp+1);i<8;i++){

                if(! this->refTablero[i][j].getCircle()){

                    break;

                }
                if(turno){
                    if(this->refTablero[i][j].getCircle()->getType()){
                        while(i>yp){

                            //m[i][j]=2;
                            i--;
                            j--;
                            k++;
                        }

                        if(k>=2)
                            n=true;

                        break;
                    }
                }else{

                    if(! this->refTablero[i][j].getCircle()->getType()){
                        while(i>yp){
                            //  m[i][j]=1;
                            i--;
                            j--;
                            k++;
                        }
                        if(k>=2)
                            n=true;

                        break;
                    }
                }
                j++;

            }
        }
        if(xp-1 >=0 && yp-1 >=0){
            int    j=xp-1;
            k=0;
            for(int i=(yp-1);i>=0;i--){
                if(! this->refTablero[i][j].getCircle()){
                    break;

                }
                if(turno){
                    if(this->refTablero[i][j].getCircle()->getType()){
                        while(i<yp){
                            // m[i][j]=2;
                            i++;
                            j++;
                            k++;
                        }
                        if(k>=2)
                            n=true;
                        break;
                    }

                }else{

                    if(! this->refTablero[i][j].getCircle()->getType()){
                        while(i<yp){
                            //    m[i][j]=1;
                            i++;
                            j++;
                            k++;
                        }
                        if(k>=2)
                            n=true;
                        break;
                    }
                }
                j--;
            }

        }
        if(yp+1 < this->dim && xp-1 >=0){
            int j=xp-1;
            k=0;
            for(int i=(yp+1);i<8;i++){
                if(! this->refTablero[i][j].getCircle()){
                    break;

                }
                if(turno){
                    if(this->refTablero[i][j].getCircle()->getType()){
                        while(i>yp){
                            //m[i][j]=2;
                            i--;
                            j++;
                            k++;
                        }
                        if(k>=2)
                            n=true;
                        break;
                    }

                }else{

                    if(! this->refTablero[i][j].getCircle()->getType()){
                        while(i>yp){
                            //  m[i][j]=1;
                            i--;
                            j++;
                            k++;
                        }
                        if(k>=2)
                            n=true;
                        break;
                    }
                }
                j--;
            }
        }
        if( xp+1 <this->dim && yp-1>=0){
            int j=xp+1;
            k=0;
            for(int i=(yp-1);i>=0;i--){
                if(! this->refTablero[i][j].getCircle()){
                    break;

                }
                if(turno){
                    if(this->refTablero[i][j].getCircle()->getType()){
                        while(i<yp){
                            //m[i][j]=2;
                            i++;
                            j--;
                            k++;
                        }
                        if(k>=2)
                            n=true;
                        break;
                    }

                }else{

                    if(! this->refTablero[i][j].getCircle()->getType()){
                        while(i<yp){
                            //  m[i][j]=1;
                            i++;
                            j--;
                            k++;
                        }
                        if(k>=2)
                            n=true;
                        break;
                    }
                }
                j++;
            }
        }

        return n;
    }


    void comer(int yp, int xp, bool turno){


        int k=0;
        if(xp-1 >=0){

            for(int i=(xp-1);i>=0;i--){
                if(! this->refTablero[yp][i].getCircle() ){

                    break;

                }
                if(turno){
                    if(this->refTablero[yp][i].getCircle()->getType()){
                        while(i<xp ){

                            this->refTablero[yp][i].getCircle()->setType(true);
                            i++;
                            //            k++;
                        }
                        //          if(k>=2)
                        //               n=true;

                        break;
                    }
                }else{

                    if(! this->refTablero[yp][i].getCircle()->getType()){
                        while(i<xp){
                            this->refTablero[yp][i].getCircle()->setType(false);
                            i++;
                            //  k++;
                        }
                        //if(k>=2)
                        //n=true;
                        break;
                    }
                }
            }
        }

        k=0;
        if(xp+1 < this->dim){
            for(int i=(xp+1);i<8;i++){
                if(! this->refTablero[yp][i].getCircle()){
                    break;

                }
                if(turno){
                    if(this->refTablero[yp][i].getCircle()->getType()){
                        while(i>xp){
                            this->refTablero[yp][i].getCircle()->setType(true);
                            i--;
                            //k++;
                        }
                        //if(k>=2)
                        //  n=true;
                        break;
                    }
                }else{


                    if(! this->refTablero[yp][i].getCircle()->getType()){
                        while(i>xp){
                            this->refTablero[yp][i].getCircle()->setType(false);
                            i--;
                            // k++;
                        }
                        //if(k>=2)
                        //  n=true;
                        break;
                    }
                }
            }
        }
        if(yp-1 >=0){

            k=0;
            for(int i=(yp-1);i>=0;i--){
                if(! this->refTablero[i][xp].getCircle()){
                    break;

                }

                if(turno){
                    if(this->refTablero[i][xp].getCircle()->getType()){
                        while(i<yp){
                            this->refTablero[i][xp].getCircle()->setType(true);
                            i++;
                            //k++;
                        }
                        //if(k>=2)
                        //  n=true;
                        break;
                    }
                }else{

                    if(! this->refTablero[i][xp].getCircle()->getType()){
                        while(i<yp){
                            this->refTablero[i][xp].getCircle()->setType(false);
                            i++;
                            // k++;
                        }
                        //if(k>=2)
                        // n=true;
                        break;
                    }
                }
            }
        }
        if(yp+1 < this->dim){
            k=0;
            for(int i=(yp+1);i<8;i++){
                if(! this->refTablero[i][xp].getCircle()){
                    break;

                }
                if(turno){
                    if(this->refTablero[i][xp].getCircle()->getType()){
                        while(i>yp){
                            this->refTablero[i][xp].getCircle()->setType(true);
                            i--;
                            //     k++;
                        }
                        // if(k>=2)
                        //   n=true;
                        break;
                    }
                }else{

                    if(! this->refTablero[i][xp].getCircle()->getType()){
                        while(i>yp){
                            this->refTablero[i][xp].getCircle()->setType(false);
                            i--;
                            // k++;
                        }
                        //if(k>=2)
                        // n=true;
                        break;
                    }
                }

            }
        }

        if(xp+1<this->dim && yp+1<this->dim ){

            int j=xp+1;
            k=0;
            for(int i=(yp+1);i<8;i++){

                if(! this->refTablero[i][j].getCircle()){

                    break;

                }
                if(turno){
                    if(this->refTablero[i][j].getCircle()->getType()){
                        while(i>yp){

                            this->refTablero[i][j].getCircle()->setType(true);
                            i--;
                            j--;
                            //k++;
                        }

                        //if(k>=2)
                        // n=true;

                        break;
                    }
                }else{

                    if(! this->refTablero[i][j].getCircle()->getType()){
                        while(i>yp){
                            this->refTablero[i][j].getCircle()->setType(false);
                            i--;
                            j--;
                            // k++;
                        }
                        // if(k>=2)
                        //    n=true;

                        break;
                    }
                }
                j++;

            }
        }
        if(xp-1 >=0 && yp-1 >=0){
            int    j=xp-1;
            k=0;
            for(int i=(yp-1);i>=0;i--){
                if(! this->refTablero[i][j].getCircle()){
                    break;

                }
                if(turno){
                    if(this->refTablero[i][j].getCircle()->getType()){
                        while(i<yp){
                            this->refTablero[i][j].getCircle()->setType(true);
                            i++;
                            j++;
                            //   k++;
                        }
                        //if(k>=2)
                        //  n=true;
                        break;
                    }

                }else{

                    if(! this->refTablero[i][j].getCircle()->getType()){
                        while(i<yp){
                            this->refTablero[i][j].getCircle()->setType(false);
                            i++;
                            j++;
                            //   k++;
                        }
                        //if(k>=2)
                        //   n=true;
                        break;
                    }
                }
                j--;
            }

        }
        if(yp+1 < this->dim && xp-1 >=0){
            int j=xp-1;
            k=0;
            for(int i=(yp+1);i<8;i++){
                if(! this->refTablero[i][j].getCircle()){
                    break;

                }
                if(turno){
                    if(this->refTablero[i][j].getCircle()->getType()){
                        while(i>yp){
                            this->refTablero[i][j].getCircle()->setType(true);
                            i--;
                            j++;
                            //    k++;
                        }
                        // if(k>=2)
                        //   n=true;
                        break;
                    }

                }else{

                    if(! this->refTablero[i][j].getCircle()->getType()){
                        while(i>yp){
                            this->refTablero[i][j].getCircle()->setType(false);
                            i--;
                            j++;
                            //k++;
                        }
                        //if(k>=2)
                        //   n=true;
                        break;
                    }
                }
                j--;
            }
        }
        if( xp+1 <this->dim && yp-1>=0){
            int j=xp+1;
            k=0;
            for(int i=(yp-1);i>=0;i--){
                if(! this->refTablero[i][j].getCircle()){
                    break;

                }
                if(turno){
                    if(this->refTablero[i][j].getCircle()->getType()){
                        while(i<yp){
                            this->refTablero[i][j].getCircle()->setType(true);
                            i++;
                            j--;
                            //k++;
                        }
                        //if(k>=2)
                        // n=true;
                        break;
                    }

                }else{

                    if(! this->refTablero[i][j].getCircle()->getType()){
                        while(i<yp){
                            this->refTablero[i][j].getCircle()->setType(false);
                            i++;
                            j--;
                            // k++;
                        }
                        //if(k>=2)
                        //  n=true;
                        break;
                    }
                }
                j++;
            }
        }

    }






    void paintTablero () {
        int acumCoords[2] = { 0, 0 };
     Puntajes= new QGraphicsTextItem();
     jug1= new QGraphicsTextItem();
     turno= new QGraphicsTextItem();
     pj1=new QGraphicsTextItem();
     pj2=new QGraphicsTextItem();
        for ( int i = 0; i < this->dim; i ++ ) {
            for ( int x = 0; x < this->dim; x++ ) {
                this->refTablero[i][x].setMyRect(acumCoords[0], acumCoords[1]);
                this->scene()->addItem(&this->refTablero[i][x]);
                acumCoords[0]+= this->refTablero[i][x].getAlto();
            }
            acumCoords[0]=0;
            acumCoords[1]+= this->refTablero[0][0].getAlto();
        }
        QString puntaje="Puntajes";
        Puntajes->setPos(630,100);
        Puntajes->setPlainText(puntaje);
        Puntajes->setScale(2.5);
        Puntajes->setDefaultTextColor(QColor(0,0,0));
         this->scene()->addItem(Puntajes);
        QString p="Blancas:\nNegras: ";
        jug1->setPos(635,140);
        jug1->setPlainText(p);
        jug1->setScale(2);
        jug1->setDefaultTextColor(QColor(0,0,0));
       // QString Turno="Juega ";
        turno->setPos(630,220);
        //  turno->setPlainText(Turno);
        turno->setScale(2.5);
        jug1->setDefaultTextColor(QColor(0,0,0));
        this->scene()->addItem(jug1);
        this->scene()->addItem(turno);
        pj1->setPos(725,140);
        pj1->setScale(2);

        pj2->setPos(725,165);
        pj2->setScale(2);
        this->scene()->addItem(pj1);
        this->scene()->addItem(pj2);
      this->addCircle(3,3,true);
        this->addCircle(4,4,true);
        this->addCircle(3,4,false);
        this->addCircle(4,3,false);

        validateMoves(GameController::round);
        Contar();
    }
};

#endif // TABLARO_H
