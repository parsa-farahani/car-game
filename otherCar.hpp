#include <iostream>
#include "car.hpp"
#include "console.hpp"

#ifndef OTHER_CARS
#define OTHER_CARS

class OtherCar : public Car {
    private:
        std::string shape[3] = 
        {
            "<+--+>",
            "<+--+>",
        };
        int score;  // random score for each car
        bool isObtained;
    public:
        static int carsCount;
        OtherCar();
        void exists () const override ;

        void update();
        void draw(int, int);

        void setRandomScore();
        void setPos();
        void setRandomPosY();
        void setIsObtained(bool);

        int getScore();  // to access the score of the car
        bool getIsObtained();
};

#endif