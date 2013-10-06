INC_DIR = -I. -Ifonts -I../lib/wiringPi/wiringPi
LIB_DIR = -L/usr/local/lib

LIBS = -lwiringPi -pthread

SHLIB_EXT = so

DOG128_SLIB = libdog128.a
DOG128_OBJ = libdog128.o
DOG128_LIB = libdog128.$(SHLIB_EXT)

MOCK_BIN = dogl_mock
MOCK_OBJ = wiringpimock.o
MOCK_LIB = libwiringPi_mock.$(SHLIB_EXT)

LD_FLAGS = $(LIB_DIR) $(LIBS)
CFLAGS = -Wall -g $(INC_DIR) -fPIC

SRC = dog128.c screen.c fonts.c
OBJ = $(SRC:.c=.o)

$(DOG128_SLIB): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LD_FLAGS)

$(DOG128_LIB): $(DOG128_OBJ) screen.o fonts.o
	$(CC) -shared -o $@ $(DOG128_OBJ) screen.o fonts.o

libdog128Mock.so: $(OBJ) $(MOCK_LIB)
	$(CC) -shared -o $@ $(OBJ) $(MOCK_OBJ) -lwiringPi_mock -L.


mock_lib: $(MOCK_LIB)

$(MOCK_LIB): $(MOCK_OBJ)
	$(CC) -shared -o $@ $(MOCK_OBJ)

dog128_mock: $(OBJ) $(MOCK_LIB)
	$(CC) -o $@ $(OBJ) $(MOCK_OBJ) -lwiringPi_mock -L.

.c.o:
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -c $<

clean:
	rm *.o dogl dogl.testreport $(MOCK_BIN) $(OBJ) $(MOCK_LIB)

test test-mock-lib: dogl $(MOCK_LIB)
	@./test.sh --with-mock-lib

test-mock-bin: $(MOCK_BIN)
	@./test.sh --with-mock-bin

test-real-pi: $(MOCK_LIB)
	@./test.sh
