#include "keyboard.h"
#include "snake.h"
#include "map.h"
#include "screen.h"
#include "game.h"
#include <bits/stdc++.h>
using namespace std;
char direction[] = {'w', 'd', 's', 'a'};
int dX[] = {-1, 0, 1, 0};
int dY[] = {0, 1, 0, -1};

enum Action {MOVE, EAT, CRASH};
enum Option {NEW, OLD, QUIT};
enum Pause {CONTINUE, SAVE, EXIT};
int difficulty[3] = {400, 200, 100};

//initialize map, snake, screen and set levels to 0 as defualt
Game::Game(int height, int width) : MP(height, width), snake(2, height, width), screen(height, width), level(0) {}

//set the game difficulty level
void Game::setLevel(int l) {
    level = l;
}

//load game from file "data.txt" which contains previously reserved gaming data
int Game::load() {
    ifstream fin("data.txt");
    if(fin.fail()) {
        screen.printFileError();
        keyboard.scanKeyboard();
        return 0;
    }
    fin >> level;
    snake.load(fin);
    MP.load(fin);
    return 1;
}

//save current game state to file "data.txt"
void Game::save() {
    ofstream fout("data.txt");
    fout << level << endl;
    snake.save(fout);
    MP.save(fout);
}

//place specified number of food items on the map
void Game::setFood(int number) {
    for(int i = 1; i <= number; i++) {
        MP.setFood();
    }
}

//display game control instructions to the player
void Game::guideline() {
    screen.print(screen.height + 2, 0, "Use w/d/s/a to control the direction.");
    screen.print(screen.height + 3, 0, "Use Esc to suspend the game.");
}

//main game loop. The loop runs until the player presses ESC or the snake crashes. 
int Game::run() {
    int time_interval = difficulty[level];
    screen.clear();
    guideline();
    screen.printMap(snake, MP);
    int ESC = 0;
    while(1) {
        this_thread::sleep_for(chrono::milliseconds(time_interval));
        char w = keyboard.scanChar();
        int dir = -1;
        if(w == 27) {
            ESC = 1;
            break;
        } else {
            for(int k = 0; k < 4; k++) {
                if(w == direction[k]) {
                    dir = k;
                }
            }
            int original_dir = snake.d;
            if(dir != -1 && (original_dir + 2) % 4 == dir) {
                dir = -1;
            }
        }
        if(dir != -1) {
            snake.setDir(dir);
        }
        int signal = MP.makeMove(snake);
        if(signal == CRASH) {
            screen.displayGameOver(); 
            keyboard.scanKeyboard();
            break;
        } else if(signal == EAT) {
            MP.setFood();
        } else {

        }
        screen.printMap(snake, MP);
    }
    screen.clear();
    return ESC;
};

//handle user input for options (help to deal with menu selection)
int Game::select_option(vector<string> options, int l, int r) {
    int option = l;
    screen.printOption(option, options);
    while(1) {
        char ch = keyboard.getChar();
        if(ch == 'w') {
            if(option > l) option--;
        } else if(ch == 's') {
            if(option < r) option++;
        } else if(ch == '\n') {
            break;
        }
        screen.printOption(option, options);
        this_thread::sleep_for(chrono::milliseconds(4));
    }
    return option - l;
}

//display main menu options to player and handle the player's input
int Game::start_up() {
    static vector<string> options = {
        "Use w/s to select button and press Enter",
        "Start a new game",
        "Continue the old game",
        "Exit"
    };
    return select_option(options, 1, 3);
}

//display difficulty level options to player and handle the player's input
int Game::select_diff() {
    static vector<string> options = {
        "Use w/s to select difficulty level and press Enter",
        "A larger number implies a higher difficulty level", 
        "Level 1",
        "Level 2",
        "Level 3"
    };
    return select_option(options, 2, 4);
}

//display pause menu options to the player and handle the player's input
int Game::select_pause() {
    static vector<string> options = {
        "Use w/s to select option and press Enter",
        "Continue the game",
        "Save the game",
        "Quit"
    };
    return select_option(options, 1, 3);
}

//game execution loop, manage game sessions and pause menu
void Game::run_loop() {
    while(1) {
        if(run()) {
            int option = select_pause();
            if(option == SAVE) {
                save();
                break;
            } else if(option == EXIT) {
                break;
            } else {

            }
        } else break;
    }
}


