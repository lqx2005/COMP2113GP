#include <bits/stdc++.h>
#include "map.h"
using namespace std;
// Enum definitions for object types and possible actions
enum Type {EMPTY, BODY, FOOD, BARRIER};
enum Action {MOVE, EAT, CRASH};
// Random number generator using CPU timestamp
mt19937 g(__builtin_ia32_rdtsc());
// Map class implementation
// Map initialization
Map::Map(int h, int w) : height(h), width(w) {
    // set up 2D dynamic array
    mp = new int*[height];
    for(int i = 0; i < height; i++) {
        mp[i] = new int[width];
    }
    // initialize all cells to EMPTY
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            mp[i][j] = EMPTY;
        }
    }
}
// Map destruction
Map::~Map() {
    // Delete the map to manage memory
    for(int i = 0; i < height; i++) {
        delete[] mp[i];
    }
    delete[] mp;
}
// Setting the position of the snake
void Map::setSnake(Snake s) {
    // Mark all snake positions as BODY
    for(auto coord : s.body) {
        auto [x, y] = coord;
        mp[x][y] = BODY;
    }
}
// Setting the position for cell
void Map::setPosition(pair<int, int> coord, int TP) {
    auto [x, y] = coord;
    mp[x][y] = TP;
}
// Getting the position of the cells
int Map::getPosition(pair<int, int> coord) {
    auto [x, y] = coord;
    return mp[x][y];
}
// Food generation logic
pair<int, int> Map::generateFood() {
    vector<pair<int, int>> valid;
    // Searching for empty cells
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(mp[i][j] == EMPTY) {
                valid.emplace_back(i, j);
            }
        }
    }
    //Randomly distributing the food
    uniform_int_distribution<int> rng(0, int(valid.size()) - 1);
    return valid[rng(g)];
}
// Placing the food
void Map::setFood() {
    pair<int, int> coord = generateFood();
    setPosition(coord, FOOD);
}
// Moving the snake
int Map::makeMove(Snake &S) {
    pair<int, int> tail = S.tail();
    pair<int, int> head = S.nextStep();
    if(getPosition(head) == EMPTY) {
        setPosition(tail, EMPTY);
        setPosition(head, BODY);
        S.Move();
        return MOVE;
    } else if(getPosition(head) == FOOD) {
        setPosition(head, BODY);
        S.Eat();
        return EAT;
    } else {
        return CRASH;
    }
}
// File I/O methods
// Loading the map from file
void Map::load(ifstream &fin) {
    fin >> height >> width;
    for(int x = 0; x < height; x++) {
        for(int y = 0; y < width; y++) {
            fin >> mp[x][y];
        }
    }
}
// Saving the map to file
void Map::save(ofstream &fout) {
    fout << height <<" " << width << endl;
    for(int x = 0; x < height; x++) {
        for(int y = 0; y < width; y++) {
            fout << mp[x][y] << " ";
        }
        fout << endl;
    }
}