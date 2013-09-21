CC=gcc

CFLAGS = -I. -Ifonts
LDFLAGS = -lwiringPi

all: dogl

OBJ = dogl.o

dogl: $(OBJ)
	$(CC) $(CFLAGS) -o dogl $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< 

clean:
	rm *.o dogl
