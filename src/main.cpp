#include <iostream>
#include <chrono>
#include <thread>
#include <csignal>
#include <random>
#include <sys/ioctl.h>

#include <tutility.h>
#include <graphic.h>
#include <TimeSpan.hpp>
#include <global.h>
#include <unistd.h>

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
        gotoxy(0,0);
        if(isWinkReversing)
            winkPosition.x--;
        else
            winkPosition.x++;

        if(isWinkReversing){
            if(winkPosition.x <= 1) isWinkReversing = false;
        }
        else if(winkPosition.x >= 20) isWinkReversing = true;
    }

    void putWink(){
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

    void clearWink(){
        fillch(' ', winkPosition, 3);
    }

    void tick(int frame) {
        clearWink();
        updatePosisiton();
        putWink();
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

Wink<5> app;

void CBCALL endSignal(int sig){
    app.end();
}

int main(){
    /* Screen */
    altBuffer();
    hideCursor();
    
    winsize tsize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &tsize);
    gotoxy(0, tsize.ws_row - 1);
    cout << tsize.ws_row << "x" << tsize.ws_col << flush;

    /* Main Program */
    app.start();

    /* Exit */
    showCursor();
    mainBuffer();
    return 0;
}
 
