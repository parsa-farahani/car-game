#include <iostream>

#ifndef CONSOLE
#define CONSOLE

class Console
{
    private:
    
    public:
        static void gotoxy(int, int);  // to print in any place you want

        static void hideCursor();  // to hide cursor

        static void sleep(int);
};

#endif