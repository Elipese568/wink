#pragma once
#include<iostream>

using std::cout;

typedef decltype(cout) cout_t;

cout_t & __cdecl esc(
    cout_t& stream
) {
    stream.put('\x1b');
    return stream;
}

void altBuffer() {
    cout << esc << "[?1049h";
}

void mainBuffer() {
    cout << esc << "[?1049l";
}

void gotoxy(int x, int y) {
    cout << esc << '['
        << x << ';'
        << y << 'H';
}
