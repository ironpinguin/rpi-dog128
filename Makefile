CC=gcc

LIBS=-lwiringPi

all: dogl

dogl: dogl.c
	$(CC) $(LIBS) dogl.c -I. -o dogl
