INC_DIR = -I. -Ifonts -Ilib/wiringPi/wiringPi
LIB_DIR = -L/usr/local/lib

LIBS = -lwiringPi -pthread

SHLIB_EXT = so

MOCK_BIN = dogl_mock
MOCK_OBJ = wiringpimock.o
MOCK_LIB = libwiringPi_mock.$(SHLIB_EXT)

LD_FLAGS = $(LIB_DIR) $(LIBS)
CFLAGS = -Wall -g $(INC_DIR) -fPIC

SRC = dogl.c screen.c fonts.c
OBJ = $(SRC:.c=.o)

dogl: $(OBJ)
	$(CC) -o $@ $(OBJ) $(LD_FLAGS)

mock_lib: $(MOCK_LIB)

$(MOCK_LIB): $(MOCK_OBJ)
	$(CC) -shared -o $@ $(MOCK_OBJ)

dogl_mock: $(OBJ) $(MOCK_LIB)
	$(CC) -o $@ dogl.o $(MOCK_OBJ) -lwiringPi_mock -L.

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
