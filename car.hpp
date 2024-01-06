#include <iostream>

#ifndef CAR
#define CAR

class Car {
    private:
        int posX;
        int posY;
        int speedX;
        int speedY;
    public:
        virtual ~Car();
        virtual void exists() const = 0;

        virtual void setPos(int, int);
        void setPosX(int);
        void setPosY(int);
        void setSpeed(int, int);
        void setSpeedX(int);
        void setSpeedY(int);

        int getPosX();
        int getPosY();
        int getSpeedX();
        int getSpeedY();
};



#endif