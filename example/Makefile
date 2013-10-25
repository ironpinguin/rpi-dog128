INC_DIR = -I. -I../src -I../lib/wiringPi/wiringPi 
LIB_DIR = -L/usr/local/lib -L../src

LIBS = -ldog128 -pthread

SHLIB_EXT = so

DOG128_SLIB = ../src/libdog128.a
DOG128_LIB = libdog128.$(SHLIB_EXT)

LD_FLAGS = $(LIB_DIR) $(LIBS)
CFLAGS = -Wall -g $(INC_DIR) -fPIC

SRC = dogl.c
OBJ = $(SRC:.c=.o)

all: lib dogl

lib:
	$(MAKE) -C ../src dog128

mock: mock_lib dogl

mock_mac: mock_lib dogl_mac

dogl_mac: $(OBJ)
	$(CC) -o dogl $(OBJ) ../src/*.o $(LIB_DIR)

mock_lib:
	$(MAKE) -C ../src mock

dogl: $(OBJ)
	$(CC) -o $@ $(OBJ) $(DOG128_SLIB) $(LD_FLAGS)

.c.o:
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -c $<

clean:
	rm dogl

test test-mock-lib: dogl $(MOCK_LIB)
	@./test.sh --with-mock-lib

test-mock-bin: $(MOCK_BIN)
	@./test.sh --with-mock-bin

test-real-pi: $(MOCK_LIB)
	@./test.sh
