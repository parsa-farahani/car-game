#include <iostream>
#include <windows.h>
#include <conio.h>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include "game.hpp"
#include "otherCar.hpp"
#include "console.hpp"
using namespace std;

int OtherCar::carsCount = 0;

OtherCar::OtherCar() {
    auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    srand(seed);
    setSpeed(-2, 0);
    setRandomScore();
    setPos();
    isObtained = false;

    OtherCar::carsCount += 1;
}

void OtherCar::exists() const {
    cout << true << '\n';
}

void OtherCar::update() {
    if (getPosX() > 0 ) {
        setPosX( getPosX() + getSpeedX() );  // to move obstacles (x)
    }
}

void OtherCar::draw(int width, int height) {

    int posX = getPosX();
    int posY = getPosY();

    if ( posX < width) {
        for (int i = 0; i < 2; i++) {
            Console::gotoxy( getPosX(), getPosY() + i ); cout << shape[i] ;
        }
    } else {
        for (int i = 0; i < 2; i++) {
            Console::gotoxy( getPosX(), getPosY() + i ); cout << "      ";
        }
    }

    if (posX < 0) {   // crossing the game screen
        for (int i = 0; i < 2; i++) {
            Console::gotoxy( getPosX(), getPosY() + i ); cout << "      ";
        }
    }
}

void OtherCar::setPos() {
    if (OtherCar::carsCount == 0) {
        setPosX(58);
    }
    else if (OtherCar::carsCount == 1) {
        setPosX(88);
    }
    else if (OtherCar::carsCount == 2) {
        setPosX(118);
    }
    else if (OtherCar::carsCount == 3) {
        setPosX(148);
    }

    setRandomPosY();
}

void OtherCar::setRandomPosY() {
    int randNum = rand() % 3;

    if (randNum == 0) {
        setPosY(1);
    }
    else if (randNum == 1) {
        setPosY(4);
    }
    else if (randNum == 2) {
        setPosY(7);
    }
}


void OtherCar::setRandomScore() {
    score = ( rand() % 5 ) + 1;     // a random score for each 'other car' (between 1 to 5)
}

void::OtherCar::setIsObtained(bool isObtained) {
    this->isObtained = isObtained;
}

int OtherCar::getScore() {
    return score;
}
bool OtherCar::getIsObtained() {
    return isObtained;
}
