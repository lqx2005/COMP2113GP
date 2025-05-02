#pragma once

#include <bits/stdc++.h>
#include <termio.h>

using namespace std;
class Keyboard {


public:
    Keyboard();
    ~Keyboard();
    string scanKeyboard();
    char scanChar();
    void setupTerminal();
    void restoreTerminal();
    char getChar();
};

