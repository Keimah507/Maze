build:
	gcc -Wall -Werror -Wextra -pedantic -Iheaders -std=c99 ./src/*.c -lSDL2 -lm -o maze
run:
	make && clear && ./maze && make clean;

clean:
	rm maze;
