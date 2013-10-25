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
MOCK_LIB_STATIC = libwiringPi_mock.a

LD_FLAGS = $(LIB_DIR) $(LIBS)
CFLAGS = -Wall -g $(INC_DIR) -fPIC

SRC = dog128.c screen.c fonts.c
OBJ = $(SRC:.c=.o)

mock: dog128_mock_static dog128_mock mock_lib

dog128: libdog128.a libdog128.so

$(DOG128_SLIB): $(OBJ)
	ar rs $@ $(OBJ)

$(DOG128_LIB): $(OBJ)
	$(CC) -shared -o $@ $(OBJ) -lwiringPi

dog128_mock: $(OBJ) $(MOCK_LIB_STATIC)
	$(CC) -shared -o $(DOG128_LIB) $(OBJ) $(MOCK_LIB_STATIC) -lwiringPi_mock -L.

dog128_mock_static: $(OBJ) $(MOCK_LIB_STATIC)
	ar rs $(DOG128_SLIB) $(OBJ) $(MOCK_LIB_STATIC)

$(MOCK_LIB_STATIC): $(MOCK_OBJ)
	ar rs $@ $(MOCK_OBJ)

mock_lib: $(MOCK_LIB)

$(MOCK_LIB): $(MOCK_OBJ)
	$(CC) -shared -o $@ $(MOCK_OBJ)

.c.o:
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -c $<

clean:
	rm *.a *.so tests.o tests wiringpimock.o $(OBJ)

tests: tests.o
	$(CC) -o $@ *.o $(LIB_DIR) $(INC_DIR)

test test-mock-lib: dogl $(MOCK_LIB)
	@./test.sh --with-mock-lib

test-mock-bin: $(MOCK_BIN)
	@./test.sh --with-mock-bin

test-real-pi: $(MOCK_LIB)
	@./test.sh
