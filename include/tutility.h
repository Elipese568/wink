#pragma once

#include<iostream>
#include<graphic.h>

using std::cout;
using std::flush;

typedef decltype(cout) cout_t;

cout_t& esc(
    cout_t& stream
) {
    stream.put(stream.widen('\x1b'));
    return stream;
}

void altBuffer() {
    cout << esc << "[?1049h" << flush;
}

void mainBuffer() {
    cout << esc << "[?1049l" << flush;
}

void showCursor(){
    cout << esc << "[?25h" << flush;
}

void hideCursor(){
    cout << esc << "[?25l" << flush;
}

void gotoxy(int x, int y) {
    cout << esc << '['
        << y << ';'
        << x << 'H';
}

void fillch(char ch, const Point& point, int length){
    for(int i = point.x; i < point.x + length; i++){
        gotoxy(i,point.y);
        putchar(ch);
    }
}

void gotoxy(const Point& point){
    gotoxy(point.x, point.y);
}
