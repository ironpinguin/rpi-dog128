CC      = gcc
LDFLAGS = -lglut -lGL
CFLAGS  = -std=c99

all: emu

emu: emu.c screen fonts
	$(CC) -o emu emu.c screen.o fonts.o $(LDFLAGS)

screen: ../src/screen.c ../src/screen.h
	$(CC) $(CFLAGS) -c -o screen.o ../src/screen.c

fonts: ../src/fonts.h ../src/fonts.c
	$(CC) $(CFLAGS) -c -o fonts.o ../src/fonts.c

clean:
	rm *~ emu
