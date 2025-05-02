snake.o: snake.cpp snake.h
	g++ -c snake.cpp
map.o: map.cpp map.h snake.h
	g++ -c map.cpp
keyboard.o: keyboard.cpp keyboard.h
	g++ -c keyboard.cpp
screen.o: screen.cpp screen.h map.h snake.h
	g++ -c screen.cpp
game.o: game.cpp map.h snake.h keyboard.h screen.h game.h
	g++ -c game.cpp
main.o: main.cpp map.h snake.h keyboard.h screen.h game.h
	g++ -c main.cpp

main: keyboard.o snake.o map.o screen.o game.o main.o
	g++ $^ -o $@
clean:
	rm -f *.o main data.txt
.PHONY: clean

