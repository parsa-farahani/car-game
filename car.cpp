#include <iostream>
#include "car.hpp"

using namespace std;

Car::~Car() {};

void Car::exists() const {
    cout << true << '\n';
};


void Car::setPos(int posX, int posY) {
    this->posX = posX;
    this->posY = posY;
}
void Car::setPosX(int posX) {
    this->posX = posX;
}
void Car::setPosY(int posY) {
    this->posY = posY;
}

void Car::setSpeed(int speedX, int speedY) {
    this->speedX = speedX;
    this->speedY = speedY;
}
void Car::setSpeedX(int speed) {
    this->speedX = speed;
}
void Car::setSpeedY(int speed) {
    this->speedY = speed;
}

int Car::getPosX() {
    return posX;
}
int Car::getPosY() {
    return posY;
}
int Car::getSpeedX() {
    return this->speedX;
}
int Car::getSpeedY() {
    return this->speedY;
}