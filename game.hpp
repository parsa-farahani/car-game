#include <iostream>
#include "console.hpp"
#include "mycar.hpp"
#include "otherCar.hpp"
#include "box.hpp"


#ifndef GAME
#define GAME

class Game
{
    private:
        int width;
        int height;
        int highestScore;
        bool boxIsObtained;
        bool paused;
        bool exitGame;
        bool gameOver;

        static const int obstacleNum = 4;

        OtherCar obstacles[obstacleNum];

        MyCar myCar;
        Box box;
    public:
        Game();
        ~Game();

        void update();
        void draw();
        void play();  // calls 'update' & 'draw' methods continuously

        void continuePlay();   // after each pause/continue 

        void checkHighestScore();
        void checkCarCross();
        void checkCollision();
        void checkObstaclesCross();
        void checkObstaclesInterference();
        void checkObtainBox();
        void checkBoxInterference();   // checks interference of box with 'other cars', and fixes that.
        void crash();

        void printLayout();    // to print runnig-game layout
        void showLoading();    // shows starting loading
        void showGamePause();  // shows pause screen
        void showGameStart();  // shows start screen
        void showGameOver();   // shows game-over screen (when life becomes == 0)

        void getInput();   // getting keyboard input from user
        void reposition();  // repositions 'mycar' & 'othercars' after each collision
        void resetposition();  // resets all positions and randomizes again

        void saveGame();
        void loadGame();
};


#endif