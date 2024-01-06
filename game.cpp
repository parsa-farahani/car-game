#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>   // to get keyboard input from user
#include "game.hpp"
#include "console.hpp"
using namespace std;

Game::Game() {
    width = 50;
    height = 10;
    highestScore = 0;
    boxIsObtained = false;
    paused = false;
    exitGame = false;
    gameOver = false;
    reposition();
}

Game::~Game() {};

void Game::update() {
    if (paused) {
        showGamePause();
    }

    if ( myCar.getLife() == 0 ) {
        paused = false;
        showGameOver();
    }
    checkHighestScore();
    checkCarCross();
    checkCollision();
    checkObtainBox();
    checkBoxInterference();
    checkObstaclesCross();
    // checkObstaclesInterference();

    myCar.update();
    for (int i = 0; i < obstacleNum; i++) {
        obstacles[i].update();
    }
    box.update();
}

void Game::draw() {
    for (int i = 0; i < obstacleNum; i++) {
        obstacles[i].draw(width, height);
    }
    box.draw(width, height);
    myCar.draw();
}


void Game::play() {
    Console::hideCursor();
    showLoading();
    showGameStart();
    while ( !myCar.getDead() ) {
        printLayout();
        getInput();
        update();
        draw();
        Console::sleep(40);
        system("cls");   // clears the console
    }
}

void Game::continuePlay() {
    Console::hideCursor();
    while ( !myCar.getDead() ) {
        system("cls");
        printLayout();
        getInput();
        update();
        draw();
        Console::sleep(40);
        // system("cls");   // clears the console
    }
}

void Game::checkHighestScore() {
    if ( myCar.getScore() > highestScore ) {
        highestScore = myCar.getScore();
    }
}

void Game::checkCarCross() {
    for (int i = 0; i < obstacleNum; i++) {
        if ( (myCar.getPosX() > (obstacles[i].getPosX() + 5)) && !(obstacles[i].getIsObtained()) ) {
            myCar.addScore( obstacles[i].getScore() );   // the score of the same ' other car' (which is a random number between 1-5, will be added to 'my car' score)
            obstacles[i].setIsObtained(true);
        }
    }
}

void Game::checkCollision() {   // checking collisions between 'myCar' and 'other cars'
    for (int i = 0; i < obstacleNum; i++) {  
        if ( ( (myCar.getPosX() <= obstacles[i].getPosX() + 5) && (myCar.getPosX() >= obstacles[i].getPosX()) || 
            (myCar.getPosX() + 5 <= obstacles[i].getPosX() + 5) && (myCar.getPosX() + 5 >= obstacles[i].getPosX()) ) 
            && myCar.getPosY() == obstacles[i].getPosY() 
        ) {
            crash();
        }
    }
}

void Game::checkObstaclesCross() {
    for (int i = 0; i < obstacleNum; i++) {
        if ( (obstacles[i].getPosX() ) <= 0 ) {  // if the 'other car' crosses the left line, it will get new x,y positions and 'my car' will get score
            obstacles[i].setRandomPosY();
            obstacles[i].setPosX(width + 24);
            // obstacles[i].setPosX(width + 8);
            // checkObstaclesInterference();
            obstacles[i].setRandomScore();
            obstacles[i].setIsObtained(false);
        }
    }
}

void Game::checkObstaclesInterference() {
    for (int i = 0; i < obstacleNum; i++) {
        if ( ( (obstacles[i+1].getPosX() - (obstacles[i].getPosX() < 24)) && (obstacles[i+1].getPosX() - (obstacles[i].getPosX()) >= 0) ) && (obstacles[i+1].getPosY() == (obstacles[i].getPosY()))) {
            obstacles[i+1].setPosX(obstacles[i].getPosX() + 24); 
        }
    }
}

void Game::checkObtainBox() {
    if ( ( (myCar.getPosX() <= box.getPosX() + 2) && (myCar.getPosX() >= box.getPosX()) || 
            (myCar.getPosX() + 5 <= box.getPosX() + 2) && (myCar.getPosX() + 5 >= box.getPosX()) ) 
            && myCar.getPosY() == box.getPosY() 
            && !box.getIsObtained()
    ) {
        box.setIsObtained(true);
        myCar.addScore( box.getScore() );
        box.setRandomScore();
        // box.setIsObtained(false);
    }    
}


void Game::checkBoxInterference() {
    for (int i = 0; i < obstacleNum; i++) {  
        if ( ( (box.getPosX() <= obstacles[i].getPosX() + 5) && (box.getPosX() >= obstacles[i].getPosX()) || 
            (box.getPosX() + 2 <= obstacles[i].getPosX() + 5) && (box.getPosX() + 2 >= obstacles[i].getPosX()) ) 
            && box.getPosY() == obstacles[i].getPosY() 
        ) {
            box.setPosX( box.getPosX() + 7 );
        }
    }
}

void Game::crash() {
    paused = true;
    myCar.setDead(true);
    myCar.setLife( myCar.getLife() - 1 );
    int count = 0;
    while (count != 10) {
        getInput();
        myCar.explode();
        Console::gotoxy(2, 22); cout << "You got " << myCar.getScore() << " Score!";
        count ++;
    }
    Console::gotoxy(2, 22); cout << "                    ";

    myCar.setDead(false); 
    box.setIsObtained(false);
    for (int i = 0; i < obstacleNum; i++) {
        if (obstacles[i].getPosX() > myCar.getPosX()) {
            obstacles[i].setIsObtained(false);
        }
    }
    reposition();
}


void Game::getInput() {
    if (_kbhit()) {
        switch (_getch()) {
            case 72:
                myCar.move('u');
                break;
            case 75:
                myCar.move('l');
                break;
            case 77:
                myCar.move('r');
                break;
            case 80:
                myCar.move('d');
                break;
        }
    }
}

void Game::reposition() {
    myCar.setSpeedX(2);
    for (int i = 0; i < Game::obstacleNum; i++) {  // setting new positions for 'other cars(obstacles)'
        // obstacles[i].setPos();
        obstacles[i].setPosX( obstacles[i].getPosX() + 10 );
    }
}

void Game::resetposition() {
    myCar.setPos(7, 4);
    box.setPosX(80);
    myCar.setSpeedX(2);
    for (int i = 0; i < Game::obstacleNum; i++) {  // setting new positions for 'other cars(obstacles)'
        obstacles[i].setPos();
        obstacles[i].setPosX( obstacles[i].getPosX() + width );
    }
}


void Game::saveGame() {
    ofstream file;
    file.open("loads.txt", ios::out);
    if (file.is_open()) {
        file << myCar.getPosX() << " " << myCar.getPosY() << " " << myCar.getLife() << " " << myCar.getScore() << " " << highestScore << " ";
        for (int i = 0; i < 4; i++) {
            file << obstacles[i].getPosX() << " " << obstacles[i].getPosY() << " ";
        }
        file << box.getPosX() << " " << box.getPosY();
        file << '\n';
        file.close();
        cout << "Game saved successfully.\n";
    }
    else {
        cout << "Unable to save the game.\n";
    }
}

void Game::loadGame() {
    ifstream file;
    file.open("loads.txt");

    int myCarPosX;
    int myCarPosY;
    int life;
    int myCarScore;
    int gameHighestScore;
    int boxPosX;
    int boxPosY;

    if (file.is_open()) {
        int posX1, posY1, posX2, posY2, posX3, posY3, posX4, posY4;
        file >> myCarPosX >> myCarPosY >> life >> myCarScore >> gameHighestScore >> posX1 >> posY1 >> posX2 >> posY2 >> posX3 >> posY3 >> posX4 >> posY4 >> boxPosX >> boxPosY ;
        box.setPosX(boxPosX);
        box.setPosY(boxPosY);
        obstacles[0].setPosX(posX1);
        obstacles[0].setPosY(posY1);
        obstacles[1].setPosX(posX2);
        obstacles[1].setPosY(posY2);
        obstacles[2].setPosX(posX3);
        obstacles[2].setPosY(posY3);
        obstacles[3].setPosX(posX4);
        obstacles[3].setPosY(posY4);
        // for (int i = 0; i < 4; i++) {
        //     // int posX;
        //     // int posY;
        //     file >> posX >> posY;
        //     obstacles[i].setPosX(posX);
        //     obstacles[i].setPosY(posY);
        // }
        myCar.setPosX(myCarPosX);
        myCar.setPosY(myCarPosY);
        myCar.setLife(life);
        myCar.setScore(myCarScore);
        highestScore = gameHighestScore;
        file.close();
    }
    else {
        cout << "Unable to open the file.\n";
    }
}


/*  Layout Prints  */

void Game::printLayout() {
    if (paused) return;
    for (int i = 0; i < width; i++) {
        Console::gotoxy(i, 0);
        cout << "#";
        if ( i % 2 == 0 && myCar.getIsMoving() ) {
            Console::gotoxy(i, 3);
            cout << "-";
            Console::gotoxy(i, 6);
            cout << "-";
        }
        else if (i % 2 != 0 && !myCar.getIsMoving() ) {
            Console::gotoxy(i, 3); 
            cout << "-";
            Console::gotoxy(i, 6); 
            cout << "-";
        }
        Console::gotoxy(i, height - 1);
        cout << "#";
    }
    Console::gotoxy(5, height + 1); cout << "Life : " << myCar.getLife();
    Console::gotoxy(5, height + 2); cout << "Score: " << myCar.getScore();
}

void Game::showLoading() {
    for (int i = height; i >= 0; i--) {
        Console::gotoxy(0, i); cout << "#################################################";
        Console::sleep(15);
    }
    for (int i = 0; i < height; i++) {
        Console::gotoxy(1, i); cout << "                                                 ";
        Console::sleep(15);
    }
}

void Game::showGameStart() {
    bool show = true;
    while(show) {
        Console::gotoxy(0, 0);   cout << "##################################################";
        Console::gotoxy(0, 1);   cout << "#                   CAR  GAME                    #";
        Console::gotoxy(0, 2);   cout << "#                                                #";
        Console::gotoxy(0, 3);   cout << "#              ------------------                #";
        Console::gotoxy(0, 4);   cout << "#                   +--+\\                        #";
        Console::gotoxy(0, 5);   cout << "#                   +--+/                        #";
        Console::gotoxy(0, 6);   cout << "#              ------------------                #";
        Console::gotoxy(0, 7);   cout << "#                                                #";
        Console::gotoxy(0, 8);   cout << "#        C: COUNTINUE      N: NEW GAME           #";
        Console::gotoxy(0, 9);   cout << "#                                                #";
        Console::gotoxy(0, 10);  cout << "##################################################";

        if (_kbhit()) {
            switch (_getch()) {
                case 67:
                case 99:   // c key for cntinue
                    loadGame();
                    show = false;
                    break;
                case 78:
                case 110:  // n key for new game
                    show = false;
                    break;
            }
        }
    } 
}

void Game::showGamePause() {
    if (myCar.getLife() == 0) return;
    while (1) {
        Console::gotoxy(0, 0);   cout << "##################################################";
        Console::gotoxy(0, 1);   cout << "#                   CRASHED!                     #";
        Console::gotoxy(0, 2);   cout << "#                                                #";
        Console::gotoxy(0, 3);   cout << "#            HIGHSCORE: " << highestScore ; for (int i = 0; i < 25 - to_string(highestScore).length(); i++) cout << " "; cout << "#";
        Console::gotoxy(0, 4);   cout << "#            SCORE    : " << myCar.getScore() ; for (int i = 0; i < 25 - to_string(highestScore).length(); i++) cout << " "; cout << "#";
        Console::gotoxy(0, 5);   cout << "#                                                #";
        Console::gotoxy(0, 6);   cout << "#                                                #";
        Console::gotoxy(0, 7);   cout << "#                                                #";
        Console::gotoxy(0, 8);   cout << "#   C: COUNTINUE   S: SAVE & EXIT    X: EXIT     #";
        Console::gotoxy(0, 9);   cout << "#                                                #";
        Console::gotoxy(0, 10);  cout << "##################################################";

        if (_kbhit()) {
            switch (_getch()) {
                case 67:
                case 99:   // c key for cntinue
                    paused = false;
                    system("cls");
                    reposition();
                    continuePlay();
                    break;
                case 83:
                case 115:
                    paused = false;
                    saveGame();
                    exit(1);
                    break;
                case 88:
                case 120:   // x key for exit
                    paused = false;
                    exit(1);
                    break;
            }
        }
    }
}

void Game::showGameOver() {
    gameOver = true;

    while (1) {

        Console::gotoxy(0, 0);   cout << "##################################################";
        Console::gotoxy(0, 1);   cout << "#                  GAME OVER!                    #";
        Console::gotoxy(0, 2);   cout << "#                                                #";
        Console::gotoxy(0, 3);   cout << "#            HIGHSCORE: " << highestScore ; for (int i = 0; i < 25 - to_string(highestScore).length(); i++) cout << " "; cout << "#";
        Console::gotoxy(0, 4);   cout << "#            SCORE    : " << myCar.getScore() ; for (int i = 0; i < 25 - to_string(highestScore).length(); i++) cout << " "; cout << "#";
        Console::gotoxy(0, 5);   cout << "#                                                #";
        Console::gotoxy(0, 6);   cout << "#                                                #";
        Console::gotoxy(0, 7);   cout << "#                                                #";
        Console::gotoxy(0, 8);   cout << "#              R: RETRY    X: EXIT               #";
        Console::gotoxy(0, 9);   cout << "#                                                #";
        Console::gotoxy(0, 10);  cout << "##################################################";

        if (_kbhit()) {
            switch (_getch()) {
                case 82:
                case 114:   // r key for retry
                    myCar.setLife(3);
                    myCar.setScore(0);
                    box.setIsObtained(false);
                    resetposition();     // resets all positions and randomizes again
                    paused = false;
                    play();
                    break;
                case 88:
                case 120:   // x key for exit
                    exit(1);
                    break;
            }
        }
    }
    
}

/*------------------------------------*/