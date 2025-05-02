#include "screen.h"
#include "snake.h"
#include "map.h"
#include <bits/stdc++.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <string>

using namespace std;

// Cell type enumeration for game objects
enum Type {EMPTY, BODY, FOOD, BARRIER};

// Screen constructor - initializes display dimensions and terminal
// @param h: playable area height
// @param w: playable area width
Screen::Screen(int h, int w) : height(h), width(w) {
    // Initialize buffer with double-width cells for better visualization
    buffer.resize(height + 2, string(width * 2 + 2, ' '));
    
    // Create vertical borders using '#' characters
    for(int i = 0; i < height + 2; i++) {
        buffer[i][0] = buffer[i][width * 2 + 1] = '#';
    }
    
    // Create horizontal borders using '#' characters
    for(int i = 0; i < width * 2 + 2; i++) {
        buffer[0][i] = buffer[height + 1][i] = '#';
    }
    setupTerminal();
}

// Screen destructor - cleans up terminal settings
Screen::~Screen() {
    restoreTerminal();
}

// Configure terminal for game display
void Screen::setupTerminal() {
    cout << "\033[?25l";  // ANSI escape code to hide cursor
    clear();
}

// Restore default terminal configuration
void Screen::restoreTerminal() {
    cout << "\033[?25h";  // ANSI escape code to show cursor
    clear();
}

// Position terminal cursor at specified coordinates
// @param x: vertical position (0-based row)
// @param y: horizontal position (0-based column)
void Screen::moveCursor(int x, int y){
    cout << "\033[" << x+1 << ";" << y+1 << "H";
}

// Display text at specified screen location
// @param x: target row position
// @param y: target column position
// @param buffer: text content to display
void Screen::print(int x, int y, string buffer) {
    moveCursor(x, y);
    cout << buffer;
    cout.flush();
}

// Print content inside game area boundaries
// @param x: internal row position (0-based)
// @param y: internal column position (0-based)
// @param buffer: text to display
void Screen::print_inside(int x, int y, string buffer) {
    // Adjust coordinates to account for border walls
    print(x + 1, y * 2 + 1, buffer);
}

// Display colored text in game area
// @param x: internal row position
// @param y: internal column position
// @param buffer: text content
// @param color: ANSI color code (31=red, 32=green, etc.)
void Screen::PrintColor(int x, int y, string buffer, int color) {
    cout << "\033[" << color << "m";  // Start color sequence
    moveCursor(x + 1, y * 2 + 1);
    cout << buffer;
    cout << "\033[0m";  // Reset color to default
    cout.flush();
}

// Clear terminal display
void Screen::clear() {
    cout << "\033[2J";  // ANSI clear screen command
}

// Render game state with snake and food
// @param S: Snake object reference
// @param M: Map object reference
void Screen::printMap(Snake &S, Map &M) {
    draw(0, 0, buffer);  // Draw base game frame
    
    // Draw food elements using apple emoji
    for(int x = 0; x < height; x++) {
        for(int y = 0; y < width; y++) {
            if(M.mp[x][y] == FOOD) {
                print_inside(x, y, "\U0001F34E");  // Unicode apple character
            }
        }
    }
    
    // Draw snake body parts with soccer ball emoji
    vector<pair<int, int>> body(S.body.begin(), S.body.end());
    for(auto coord : body) {
        auto [x, y] = coord;
        // Draw smiling face emoji for snake head
        if(coord == S.head()) {
            print_inside(x, y, "\U0001F600");
        } else {
            print_inside(x, y, "\u26BD");  // Soccer ball body segment
        }
    }
}

//Design the shape to be displayed when crash
void Screen::displayGameOver() {
    clear();
    
    const string gameOverArt = R"(
        ╔════════════════════╗
        ║     GAME OVER!     ║
        ╚════════════════════╝
    )";
    
    int centerX = height / 2 - 2;  // -2 to account for 3-line art
    int centerY = width - 10;      // -10 to roughly center the art
    
    // Split the multi-line string into individual lines
    vector<string> lines;
    size_t start = 0;
    size_t end = gameOverArt.find('\n');
    
    while (end != string::npos) {
        lines.push_back(gameOverArt.substr(start, end - start));
        start = end + 1;
        end = gameOverArt.find('\n', start);
    }
    
    // Print each line centered
    for (size_t i = 0; i < lines.size(); i++) {
        if (!lines[i].empty()) { 
            moveCursor(centerX + i, centerY);
            cout << lines[i];
        }
    }
    
    cout.flush();
    this_thread::sleep_for(chrono::seconds(3));  // Display for 2 seconds
}

// Display file error message temporarily
void Screen::printFileError() {
    clear();
    draw(0, 0, buffer);
    print_inside(15, 15, "File does not exist.");
    this_thread::sleep_for(chrono::seconds(2));  // Show message for 2 seconds
}

// Render interactive menu with selection highlight
// @param option: currently selected menu index
// @param options: list of menu text entries
void Screen::printOption(int option, vector<string> options) {
    clear();
    draw(0, 0, buffer);
    int x = 5;  // Initial vertical position for first menu item
    
    for(int i = 0; i < int(options.size()); i++) {
        // Calculate horizontal centering offset
        int shift = options[i].length();
        shift /= 2;  // Account for character width
        shift /= 2;  // Adjust for double-width cells
        
        // Highlight selected option in red
        if(i == option) {
            PrintColor(x, 20 - shift, options[i], 31);
        } else {
            print_inside(x, 20 - shift, options[i]);
        }
        x += 4;  // Vertical spacing between menu items
    }
}

// Render complete buffer to terminal
// @param x: starting row position
// @param y: starting column position
// @param buffer: content to display
void Screen::draw(int x, int y, vector<string> buffer) {
    for(const auto &row : buffer) {
        moveCursor(x, y);
        cout << row;
        x++;  // Move to next line
    }
    cout.flush();
}
