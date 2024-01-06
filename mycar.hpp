#include <iostream>
#include "car.hpp"
#include "console.hpp"

#ifndef MY_CAR
#define MY_CAR

class MyCar : public Car {
    private:
        std::string shape[4] = 
        {
            "+--+\\",
            "+--+/",
            // " + ",
            // "+-+",
            // " + ",
            // "+-+"
        };
        std::string expParticles1[4] = {"o    o",
                                        "o    o"}
        ;
        std::string expParticles2[4] = {"  oo  ",
                                        "  oo  "}
        ; 
        int life;
        int score;
        bool isMoving;
        bool exploded;
        bool dead;
    public:
        MyCar();

        void exists () const override ;

        void update();
        void draw();

        void move(char);
        void explode();

        void addScore(int);

        void setLife(int);
        void setScore(int);
        void setIsMoving(bool);
        void setExploded(bool);
        void setDead(bool);

        int getLife();
        int getScore();
        bool getIsMoving();
        bool getExploded();
        bool getDead();
};



#endif