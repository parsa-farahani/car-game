#include <iostream>
#include <fstream>
#include <windows.h>
#include "mycar.hpp"
#include "otherCar.hpp"
#include "box.hpp"
#include "game.hpp"
using namespace std;


int main() {

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    Game game;
    game.play();
    return 0;
}