CC=gcc

LIBS=-lwiringPi

all: dogl

dogl: main.c
	$(CC) $(LIBS) main.c -o dogl
