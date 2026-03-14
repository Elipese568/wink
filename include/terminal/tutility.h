#pragma once

#include<iostream>
#include<graphic.h>

using std::cout;
using std::flush;

typedef decltype(cout) cout_t;

cout_t & __cdecl esc(
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

void gotoxy(int x, int y) {
    cout << esc << '['
        << x << ';'
        << y << 'H';
}

void gotoxy(const Point& point){
    gotoxy(point.x, point.y);
}