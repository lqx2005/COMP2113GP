#include "keyboard.h"
#include "snake.h"
#include "map.h"
#include "screen.h"
#include <bits/stdc++.h>
using namespace std;


class Game {
public:
    Map MP;
    Snake snake;
    Screen screen;
    Keyboard keyboard;
    int level;
    Game(int height, int width);
    void setLevel(int l);
    int load();
    void save();
    void setFood(int number);
    int run();
    int select_option(vector<string> options, int l, int r);
    void guideline();
    int start_up();
    int select_diff();
    int select_pause();
    void run_loop();
};
    
