#include <iostream>
#include <chrono>
#include <thread>
#include <csignal>

#include <terminal/tutility.h>
#include <graphic.h>

using namespace std;

bool running = true;

void __cdecl endSignal(int sig){
    running = false;
}

class Wink{
private:
    Point winkPosition;
public:
    Wink() : winkPosition{0,0} {}

    void tick() {
        gotoxy(winkPosition);
        puts(">v-");
    }
};

int main(){
    altBuffer();

    signal(SIGINT, endSignal);

    auto app = Wink();

    while(running){
        app.tick();
    }

    mainBuffer();
    return 0;
}
 