#include<iostream>
#include<chrono>
#include<thread>
#include<csignal>
#include"tutility.h"
using namespace std;



void endSignal(int signum){}
int main(){
    altBuffer();
    signal(SIGINT, endSignal);
    while(true){
        gotoxy(0,0);
        cout << ">v-";
    }

    mainBuffer();
    return 0;
}
