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
    bool     isWinkReversing = false;

    bool     running = true;

    TimeSpan<chrono::steady_clock::time_point> winkTimeSpan;
    mt19937  rg;

    chrono::seconds kNextWinkTimeIntervalRange = 1s;
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
    void updatePosisiton(){
        
    }

    void tick(int frame) {
        gotoxy(0,0);
        if(isWinkReversing)
            winkPosition.x--;
        else
            winkPosition.x++;

        if(isWinkReversing){
            if(winkPosition.x <= 1) isWinkReversing = false;
        }
        else if(winkPosition.x >= 20) isWinkReversing = true;
        
        cout << "                      " << flush;
        
        gotoxy(winkPosition);
        if(winkTimeSpan.contains(chrono::steady_clock::now())){
            puts(">v-");
        }
        else{
            if(chrono::steady_clock::now() >= winkTimeSpan.end())
                generateNextWinkTime();
            puts("ovo");
        }
    }

    void waitFrame() {
        this_thread::sleep_for(1000ms / Fps);
    }

    void start(){
        running = true;
        generateNextWinkTime();

        int frame = 0;
        while(running){
            tick(frame);

            waitFrame();
        }
    }

    void end(){
        running = false;
    }
};

Wink<120> app;

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
 
