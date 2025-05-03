## Please remember to set the terminal into full screen.
## SNAKE
Group Member: <br/>
              Li Qixuan 3036289523 lqx2005 <br/>
              Wei Yukun 3036289262 Nuno-ux <br/>
              Lu Zhiyuan 3036127517 David-Lu-Zhiyuan <br/>
              Xu Ruicong 3036291100 xuruicong713 <br/>
              Cao Jiyue 3036290089 J-yyyyyyy <br/>

## Table of Contents
1. Game Description
2. Coding Features
3. Libraries
4. Compilation & Execution Instructions

## Game Description
Video Link: https://youtu.be/YiVb3dsB2vQ?feature=shared <br/>
Welcome to our text-based version of classic the game Snake. We are glad to present the arcade classic on your PC.<br/>
Start as a small serpent with just 2 segments, move around the gameboard and toggle the direction of the snake with w/a/s/d.<br/>
Eat fruits to get longer! Fruits are distributed randomly across the map. <br/>
Watch out! The snake dies upon collides into its own body and the game terminates. <br/>
There are three different difficulties for you to explore.<br/>
Try your best to make your snake as long as possible. We wish you a happy time playing SNAKE!


## Coding Features
#### - Generation of random events  <br/>
Fruits are distributed randomly in valid areas across the map.  <br/>
#### - Data structures for storing data  <br/>
Classes are implemented to store variables and functions to execute the game. All the functions and variables are handled with classes. Deque is used to manage the snakes body, i.e. the dynamic insertion and removal at both ends. This handles the movement and the extension of the snake. <br/>
#### - Dynamic memory management <br/>
The map is stored using pointers. A new map is generated each time upon playing the game and gets deleted after the game ends.
#### - File input/output  <br/>
The information of the gameplay is saved in a txt file, and can be loaded when the player wants to resume the gameplay.  <br/>
#### - Program codes in multiple files  <br/>
The program consists of functions of different features in multiple files, integrated using makefile.  <br/>
#### - Multiple Difficulty Levels  <br/>
The snake moves faster in more difficult levels.  A range of speeds are created for the three levels of the game.<br/>

## Non-Standard C++ libraries <br/>
List of non-standard library : termios.h; unistd.h; fcntl.h <br/>
Features supported: <br/>
### termios.h: <br/>
-	Non-blocking input: It disables ICANON (canonical mode), allowing instant keypress detection without waiting for Enter. (Do not require the user to press Enter for the cin.) <br/>
-	Disabling Echo: Prevents keypresses from being displayed on the screen. (e.g. W/A/S/D won’t clutter the terminal.) <br/>
-	Raw input handling: Enables direct detection of special keys (e.g. Esc) <br/>
### unistd.h <br/>
-	Non-blocking read() : Used in Keyboard::scanKeyboard() to check for pending keypresses without freezing the game loop. <br/>
-	Terminal control: Work with fcntl.h to modify file descriptor flags (e.g., STDIN_FILENO.) <br/>
### fcntl.h <br/>
-	0_NONBLOCK Flag: Applied to STDIN_FILENO (standard input) to prevent read() from blocking execution. Without this, the game would stall until a key is pressed. <br/>

## Compilation and execution instructions <br/>
First of all, please remember to set the terminal into full screen. <br/>
### Compilation: <br/>
Bash instruction: make main <br/>
### Run <br/>
Bash instruction: ./main <br/>
### Controls: <br/> 
-	Use W/A/S/D keys to control the snake. W is for moving up, A is for moving left, S is for moving down, D is for moving right. <br/>
-	Enter the Esc key to pause the game. While paused, use W/S to navigate menu options. Use Enter key to confirm selection. <br/>
- After eating one food, the length of the snake will grow by one. <br/>
-	The snake cannot reverse direction. <br/>
-	The game wraps around the screen (if the snake goes out of one edge, it will reappears on the opposite side). <br/>
