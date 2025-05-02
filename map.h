#pragma once
#include <bits/stdc++.h>
#include "snake.h"
using namespace std;

class Map {
    public:
    int height, width;
    int **mp;
    Map(int h, int w);
    ~Map();
    void setSnake(Snake s);
    void setPosition(pair<int, int> coord, int TP);
    int getPosition(pair<int, int> coord);
    int checkValid(pair<int, int> coord);
    pair<int, int> generateFood();
    void setFood();
    int makeMove(Snake &S);
    void load(ifstream &fin);
    void save(ofstream &fout);
};