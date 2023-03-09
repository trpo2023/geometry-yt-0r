run: main.c main
	gcc -Wall -Werror -o run main.c && ./main && rm -f ./run
