#include <iostream>
#include <chrono>
#include <thread>
#include <csignal>

#include <terminal/tutility.h>
#include <graphic.h>

using namespace std;

class Wink{
private:
    Point winkPosition;
    bool running = true;
public:
    Wink() : winkPosition{0,0} {}

    void tick() {
        gotoxy(winkPosition);
        puts(">v-");
    }

    void start(){
        running = true;

        while(running){
            tick();
        }
    }

    void end(){
        running = false;
    }
};

Wink app;

void __cdecl endSignal(int sig){
    app.end();
}

int main(){
    altBuffer();
    signal(SIGINT, endSignal);

    app.start();

    mainBuffer();
    return 0;
}
 