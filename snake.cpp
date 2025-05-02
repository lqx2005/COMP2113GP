// Include common headers
#include <bits/stdc++.h>
#include "snake.h"
#include "map.h"
using namespace std;

// Macros to simplify pair member access
#define x first
#define y second

// Direction arrays: coordinate changes for UP/RIGHT/DOWN/LEFT
static int dX[] = {-1, 0, 1, 0};
static int dY[] = {0, 1, 0, -1};
// Direction constants
enum Direction { UP, RIGHT, DOWN, LEFT};

// Constructor: Initializes snake with given length and map size
Snake::Snake(int length, int h, int w) : height(h), width(w), d(RIGHT) { // Start facing RIGHT
    body.clear(); // Clear existing body segments

    // Create horizontal snake body starting at (0,0)
    for(int i = 0; i < length; i++) {
        body.emplace_front(0, i); // Add segments to front (head)
    }
}

// Returns current head position
pair<int, int> Snake::head() {
    return body.front();
}

// Returns current tail position
pair<int, int> Snake::tail() {
    return body.back();
}

// Calculates next head position with wrap-around
pair<int, int> Snake::nextStep() {
    pair<int, int> h = head();// Current head

    // Move based on current direction
    h.x += dX[d];
    h.y += dY[d];

    // Handle map boundary
    h.x = (h.x + height) % height;
    h.y = (h.y + width) % width;
    return h;
}

// Change movement direction
void Snake::setDir(int direction) {
    d = direction;
}

// Regular movement (no growth)
void Snake::Move() {
    pair<int, int> h = nextStep();
    body.push_front(h); // Add new head
    body.pop_back(); // Remove old tail
}

// Movement when eating (grows by 1 segment)
void Snake::Eat() {
    pair<int, int> h = nextStep();
    body.push_front(h);// Add new head, keep tail

}

// Load snake state from file
void Snake::load(ifstream &fin) {
    int length;
    fin >> d; // Read direction
    fin >> length; // Read body length
    body.clear(); // Reset current body

    // Rebuild body from saved coordinates
    for(int i = 0; i < length; i++) {
        int x, y;
        fin >> x >> y;
        body.emplace_back(x, y); // Add segments to back
    }
}

// Save snake state to file
void Snake::save(ofstream &fout) {
    fout << d << endl; // Save direction
    fout << body.size() << endl; // Save body length

    // Convert deque to vector for easier iteration
    vector<pair<int, int>> output(body.begin(), body.end());

    // Write all coordinates
    for(auto [x, y] : output) {
        fout << x << " " << y << endl; 
    }
}