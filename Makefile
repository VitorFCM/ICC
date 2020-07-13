main.o : main.c
	gcc -o main.o -c main.c

principais.o : principais.c
	gcc -o principais.o -c principais.c

auxiliares.o : auxiliares.c
	gcc -o auxiliares.o -c auxiliares.c

main : main.o principais.o auxiliares.o
	gcc -o main main.o principais.o auxiliares.o

all : main

run : main
	./main

clean :
	rm main main.o principais.o auxiliares.o 
