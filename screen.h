#pragma once

#include "snake.h"
#include "map.h"
#include <bits/stdc++.h>
using namespace std;

class Screen{
public:
    int height, width;
    vector<string> buffer;
    Screen(int h, int w);
    ~Screen();
    void clear();
    void refresh();
    void setupTerminal();
    void restoreTerminal();
    void moveCursor(int x, int y);
    void draw(int x, int y, vector<string> buffer);
    void print(int x, int y, string buffer);
    void print_inside(int x, int y, string buffer);
    void PrintColor(int x, int y, string buffer, int color);
    void printMap(Snake &S, Map &M);
    void printFileError();
    void printOption(int option, vector<string> options);
    void displayGameOver();
};
