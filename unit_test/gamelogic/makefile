all:	input
	cp input $(HOME)/cmpt433/public/myApps/

input:	
	arm-linux-gnueabihf-gcc -pthread -Wall -g -D _POSIX_C_SOURCE=200809L -Werror -o main.o -c main.c
	arm-linux-gnueabihf-gcc -pthread -Wall -g -D _POSIX_C_SOURCE=200809L -Werror -o game.o -c game.c
	arm-linux-gnueabihf-gcc -pthread -Wall -g -D _POSIX_C_SOURCE=200809L -Werror -o led.o -c led.c
	arm-linux-gnueabihf-gcc -pthread -Wall -g -D _POSIX_C_SOURCE=200809L -Werror -o display.o -c display.c
	arm-linux-gnueabihf-gcc -pthread -Wall -g -D _POSIX_C_SOURCE=200809L -Werror -o input.o -c input.c
	arm-linux-gnueabihf-gcc -pthread -Wall -g -D _POSIX_C_SOURCE=200809L -Werror -o score_display.o -c score_display.c
	arm-linux-gnueabihf-g++ -std=c++11 -o util.o -c util.cpp
	arm-linux-gnueabihf-g++ -pthread util.o input.o main.o led.o display.o game.o score_display.o -o input

clean:
	rm -f *.o input

