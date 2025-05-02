// Entry point for the Snake game
// The main file for the game
// Include the headers for other files
#include "keyboard.h"
#include "snake.h"
#include "map.h"
#include "screen.h"
#include "game.h"
// Include all standard headers for cpp
#include <bits/stdc++.h>
// Enum for main menu options
enum Option {NEW, OLD, QUIT};
// Main game loop
void run() {
    while(1) {
        // Initialize gameboard size
        Game game(30, 40);
        // Set up startup menu
        int option = game.start_up();
        // New game setup
        if(option == NEW) {
            int level = game.select_diff();
            game.setLevel(level);
            game.setFood(5);
            game.run_loop();
        // Loading new game
        } else if(option == OLD) {
            if(game.load()) {
                game.run_loop();
            }
        // Quitting the game
        } else if(option == QUIT) {
            break;
        }
    }
}
// Run the main loop
int main() {
    run();
}
