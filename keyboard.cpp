#include "keyboard.h"
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <bits/stdc++.h>

using namespace std;

//initailiae terminal for keyboar input
Keyboard::Keyboard() {
    setupTerminal();
}

//restore original terminal settintgs
Keyboard::~Keyboard() {
    restoreTerminal();
}

//original terminal settings
static struct termios original_settings;
//original file status flag
static int flags;
//input buffer
static char buf[1 << 12];

void Keyboard::setupTerminal() {
    //get current terminal settings
    tcgetattr(STDIN_FILENO, &original_settings);
    // create modified settings
    struct termios new_settings = original_settings;
    //disable line buffering and echo
    new_settings.c_lflag &= ~(ICANON | ECHO);
    //apply new settings immediately
    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
    //set non-blocking mode
    flags = fcntl(STDIN_FILENO, F_GETFL);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

//restore original file status settings
void Keyboard::restoreTerminal() {
    fcntl(STDIN_FILENO, F_SETFL, flags);
    tcsetattr(STDIN_FILENO, TCSANOW, &original_settings);
}

//read input into buffer and return as string
string Keyboard::scanKeyboard() {    
    int numRead = read(STDIN_FILENO, buf, sizeof(buf));
    string sequence = "";
    if(numRead > 0) {
        for(int i = 0; i < numRead; i++) sequence += buf[i];
    }
    return sequence;
}

//get first available character from input and return it
char Keyboard::getChar() {
    string sequence = scanKeyboard();
    if(sequence.length() > 0) return sequence[0];
    return 0;
}

//scan for specific control characters and return the key
char Keyboard::scanChar() {
    string sequence = scanKeyboard();
    //check for ESC
    for(auto c : sequence) if(c == 27) return c;
    //check for WDSA
    int length = sequence.size();
    vector<int> keys = {119, 100, 115, 97};
    for(int i = length - 1; i >= 0; i--) {
        for(auto key : keys) if(sequence[i] == key) {
            return sequence[i];
        }
    }
    return 0;
}
