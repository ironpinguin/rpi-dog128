CC=gcc

CFLAGS = -I. -Ifonts
LDFLAGS = -lwiringPi -pthread

all: dogl

OBJ = dogl.o screen.o fonts.o

dogl: $(OBJ)
	$(CC) $(CFLAGS) -o dogl $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< 

clean:
	rm *.o dogl
