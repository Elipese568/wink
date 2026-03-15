#include <iostream>
#include <chrono>
#include <thread>
#include <csignal>
#include <random>

#include <terminal/tutility.h>
#include <graphic.h>
#include <TimeSpan.hpp>

#define invoke(t) t()()

using namespace std;

template<int Fps>
class Wink{
private:
    Point    winkPosition;

    bool     running = true;

    TimeSpan<chrono::steady_clock::time_point> winkTimeSpan;
    mt19937  rg;

    chrono::seconds kNextWinkTimeIntervalRange = 5s;
public:
    Wink() : winkPosition{0,0}, 
             winkTimeSpan{
                 chrono::steady_clock::now() - 1s, 
                 chrono::steady_clock::now() - 1s},
             rg{invoke(random_device)} {}

    void generateNextWinkTime() {
        auto nextWinkTp = 
            chrono::steady_clock::now() + kNextWinkTimeIntervalRange;
        auto endWinkTp = nextWinkTp + 2s;
        
        winkTimeSpan = TimeSpan(nextWinkTp, endWinkTp);
    }

    void tick() {
        gotoxy(winkPosition);
        if(winkTimeSpan.contains(chrono::steady_clock::now()))
            puts(">v-");
        else
            puts("ovo");
    }

    void waitFrame() {
        this_thread::sleep_for(1s / Fps);
    }

    void start(){
        running = true;
        generateNextWinkTime();
        while(running){
            tick();

            waitFrame();
        }
    }

    void end(){
        running = false;
    }
};

Wink<20> app;

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
 
