#pragma once
#include <bits/stdc++.h>
using namespace std;
class Snake {
    public:
    int height, width;
    deque<pair<int, int>> body;
    int d;
    Snake(int length, int h, int w);
    pair<int, int> head();
    pair<int, int> tail();
    pair<int, int> nextStep();
    void setDir(int direction);
    void Move();
    void Eat();
    void load(ifstream &fin);
    void save(ofstream &fout);
};