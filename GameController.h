#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QDebug>

using namespace std;

class GameController {

protected:
    bool machine;

    char player1[256];
    char player2[256];
    // players goes here..

public:
    static bool round;

    GameController () {
        this->round = false;
        this->machine = false;
    }
    GameController (bool k){
        this->round = k;
        this->machine = false;

    }

    void addTablero () {
    }

    void toggleRound () {
        this->round  = this->round ? false : true;
    }

    bool getRound () {
        return this->round;
    }
    void setRound(bool k){

           this->round=k;
    }

    void showMessage () {

    }

};

bool GameController::round = false;

#endif // GAMECONTROLLER_H
