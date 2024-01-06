#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include "box.hpp"
#include "console.hpp"
using namespace std;

Box::Box() {
    auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    srand(seed);
    setRandomScore();  // setting random score for each box

    setRandomPosY();
    posX = 80;
    speedX = -2;
    speedY = 0;

    isObtained = false;
    shape = notObtained;
}

void Box::update() {

    if (isObtained) {
        shape = obtained;
    } else {
        shape = notObtained;
    }

    if (posX <= 0) {
        isObtained = false;
        setRandomPosY();
        posX = 70;
    }

    posX += speedX;
}

void Box::draw(int width, int height) {
    Console::gotoxy( posX, posY );
    if (posX < width) {
        for (int i = 0; i < 2; i++) {
            Console::gotoxy( posX, posY + i ); cout << shape[i];
        }
    }
    if (posX < 0) {
        for (int i = 0; i < 2; i++) {
            Console::gotoxy( posX, posY + i ); cout << "   ";
        }
    }
}

void Box::setPosX(int posX) {
    this->posX = posX;
}

void Box::setPosY(int posY) {
    this->posY = posY;
}

void Box::setRandomPosY() {
    int randN = rand() % 3;

    if (randN == 0) {
        posY = 1;
    }
    else if (randN == 1) {
        posY = 4;
    }
    else if (randN == 2) {
        posY = 7;
    }  
}

void Box::setRandomScore() {
    score = (rand() % 10) + 1;
}

void Box::setIsObtained(bool isObtained) {
    this->isObtained = isObtained;
}


int Box::getPosX() {
    return posX;
}
int Box::getPosY() {
    return posY;
}

int Box::getScore() {
    return score;
}
bool Box::getIsObtained() {
    return isObtained;
}