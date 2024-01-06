#include <iostream>
#include "console.hpp"
#include "mycar.hpp"

using namespace std;

MyCar::MyCar() {
    setSpeedX(2);
    setSpeedY(3);
    setPos(7, 4);
    life = 3;
    score = 0;
    isMoving = false;
    exploded = false;
    dead = false;
}

void MyCar::exists() const {
    cout << true << '\n';
}

void MyCar::update() {
    // Further update options
}

void MyCar::draw() {

    Console::gotoxy( getPosX(), getPosY() );

    if (!dead) {
        for (int i = 0; i < 2; i++) {
            Console::gotoxy( getPosX(), getPosY() + i ); cout << shape[i];
        }
    } else {
        for (int i = 0; i < 2; i++) {
            Console::gotoxy( getPosX(), getPosY() + i ); cout << "      ";
        }
    }
}


void MyCar::move(char dir) {
    if (dead) return;
    switch (dir)
    {
        case 'u':
            if ( getPosY() > 2 ) setPosY(getPosY() - getSpeedY());
            break;
        case 'd':
            if ( getPosY() < 7 ) setPosY(getPosY() + getSpeedY());
            break;
        case 'l':
            if ( getPosX() > 7 ) setPosX( getPosX() - getSpeedX() );
            break;
        case 'r':
            if ( getPosX() < 44 ) setPosX( getPosX() + getSpeedX() );
            break;
    }
}

void MyCar::explode() {
        if (exploded) {
        for (int i = 0; i < 2; i++) {
            Console::gotoxy( getPosX() - 1, getPosY() + i );
            cout << expParticles1[i] << endl;
        }
        exploded = false;
    } else {
        for (int i = 0; i < 2; i++) {
            Console::gotoxy( getPosX() - 1, getPosY() + i );
            cout << expParticles2[i] << endl;
        }
        exploded = true;
    }
    Console::sleep(100);
}

void MyCar::addScore(int plusScore) {
    score += plusScore;
}


void MyCar::setLife(int life) {
    this->life = life;
}
void MyCar::setScore(int score) {
    this->score = score;
}
void MyCar::setIsMoving(bool isMoving) {
    this->isMoving = isMoving;
}
void MyCar::setExploded(bool exploded) {
    this->exploded = exploded;
}
void MyCar::setDead(bool dead) {
    this->dead = dead;
}

int MyCar::getLife() {
    return life;
}
int MyCar::getScore() {
    return score;
}
bool MyCar::getIsMoving() {
    return isMoving;
}
bool MyCar::getExploded() {
    return exploded;
}
bool MyCar::getDead() {
    return dead;
}