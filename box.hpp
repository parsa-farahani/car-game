#include <iostream>

#ifndef BOX
#define BOX

class Box {
    private:
        std::string notObtained[2] = {
            "***",
            "***",  // had a '\n' at the end
        };
        std::string obtained[2] = {
            "",
            "",
        };
        std::string* shape;
        int posX;
        int posY;
        int speedX;
        int speedY;
        int score;
        bool isObtained;
    public:
        Box();

        void update();
        void draw(int, int);

        void setPosX(int);
        void setPosY(int);
        void setRandomPosY();
        void setRandomScore();
        void setIsObtained(bool);

        int getPosX();
        int getPosY();
        int getScore();
        bool getIsObtained();
};

#endif