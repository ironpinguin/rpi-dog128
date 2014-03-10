INC_DIR=-I. -Ifonts -I../lib/wiringPi/wiringPi
LIB_DIR=-L/usr/local/lib
VERSION=1.0
DESTDIR=/usr
PREFIX=/local

LIBS = -lwiringPi -pthread

SHLIB_EXT = so
SHLIB_EXT_MAC = dylib

DOG128_SLIB = libdog128.a
DOG128_OBJ = libdog128.o
DOG128_LIB = libdog128.$(SHLIB_EXT)
DOG128_LIB_MAC = libdog128.$(SHLIB_EXT_MAC)

MOCK_BIN = dogl_mock
MOCK_OBJ = wiringpimock.o
MOCK_LIB = libwiringPi_mock.$(SHLIB_EXT)
MOCK_LIB_MAC = libwiringPi_mock.$(SHLIB_EXT_MAC)
MOCK_LIB_STATIC = libwiringPi_mock.a

GLMOCK_BIN = dogl_glmock
GLMOCK_OBJ = wiringpiglmock.o
GLMOCK_LIB = libwiringPi_glmock.$(SHLIB_EXT)
GLMOCK_LIB_MAC = libwiringPi_glmock.$(SHLIB_EXT_MAC)
GLMOCK_LIB_STATIC = libwiringPi_glmock.a
GLFLAGS = -lglut -lGL

LD_FLAGS = $(LIB_DIR) $(LIBS)
CFLAGS = -Wall -g $(INC_DIR) -fPIC -std=c99

SRC = dog128.c screen.c fonts.c
OBJ = $(SRC:.c=.o)

all: $(DOG128_SLIB) $(DOG128_LIB).$(VERSION)

install: install-header install-lib

install-header:
	@echo "[Install Headers]"
	@install -m 0755 -d $(DESTDIR)$(PREFIX)/include
	@install -m 0644 dog128.h $(DESTDIR)$(PREFIX)/include
	
install-lib: $(DOG128_LIB).$(VERSION)
	@echo "[Install Dynamic Lib]"
	@install -m 0755 -d $(DESTDIR)$(PREFIX)/lib
	@install -m 0755 $(DOG128_LIB).$(VERSION) $(DESTDIR)$(PREFIX)/lib
	@ln -sf $(DESTDIR)$(PREFIX)/lib/$(DOG128_LIB).$(VERSION) $(DESTDIR)$(PREFIX)/lib/$(DOG128_LIB)
	@ldconfig

install-static: $(DOG128_SLIB)
	@echo "[Install Static Lib]"
	@install -m 0755 -d $(DESTDIR)$(PREFIX)/lib
	@install -m 0755 $(DOG128_SLIB) $(DESTDIR)$(PREFIX)/lib

uninstall:
	@echo "[UnInstall]"
	@rm -f $(DESTDIR)$(PREFIX)/include/dog128.h
	@rm -f $(DESTDIR)$(PREFIX)/lib/libdog128.*
	@rm -f $(DESTDIR)/lib/libdog128.*
	@ldconfig

mock: dog128_mock_static dog128_mock mock_lib

mock-mac: dog128_mock_static dog128_mock_mac mock_lib

glmock: dog128_glmock_static dog128_glmock glmock_lib

glmock-mac: dog128_glmock_static dog128_glmock_mac glmock_lib

$(DOG128_SLIB): $(OBJ)
	ar rs $@ $(OBJ)

$(DOG128_LIB).$(VERSION): $(OBJ)
	$(CC) -shared -o $@ $(OBJ) -lwiringPi

dog128_mock: $(OBJ) $(MOCK_LIB_STATIC)
	$(CC) -shared -o $(DOG128_LIB) $(OBJ) $(MOCK_LIB_STATIC) -lwiringPi_mock -L.

dog128_mock_mac: $(OBJ) $(MOCK_LIB_STATIC)
	$(CC) -shared -o $(DOG128_LIB_MAC) $(OBJ) $(MOCK_LIB_STATIC) -lwiringPi_mock -L.

dog128_mock_static: $(OBJ) $(MOCK_LIB_STATIC)
	ar rs $(DOG128_SLIB) $(MOCK_LIB_STATIC) $(OBJ) $(MOCK_OBJ)

$(MOCK_LIB_STATIC): $(MOCK_OBJ)
	ar rs $@ $(MOCK_OBJ)

mock_lib: $(MOCK_LIB)

$(MOCK_LIB): $(MOCK_OBJ)
	$(CC) -shared -o $@ $(MOCK_OBJ)
	
dog128_glmock: $(OBJ) $(GLMOCK_LIB_STATIC)
	$(CC) -shared -o $(DOG128_LIB) $(OBJ) $(GLMOCK_LIB_STATIC) -lwiringPi_glmock $(GLFLAGS) -L.

dog128_glmock_mac: $(OBJ) $(GLMOCK_LIB_STATIC)
	$(CC) -shared -o $(DOG128_LIB_MAC) $(OBJ) $(GLMOCK_LIB_STATIC) -lwiringPi_glmock $(GLFLAGS) -L.

dog128_glmock_static: $(OBJ) $(GLMOCK_LIB_STATIC)
	ar rs $(DOG128_SLIB) $(GLMOCK_LIB_STATIC) $(OBJ) $(GLMOCK_OBJ)

$(GLMOCK_LIB_STATIC): $(GLMOCK_OBJ)
	ar rs $@ $(GLMOCK_OBJ)

glmock_lib: $(GLMOCK_LIB)

$(GLMOCK_LIB): $(GLMOCK_OBJ)
	$(CC) -shared -o $@ $(GLMOCK_OBJ)

.c.o:
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -c $<

clean:
	rm -rf $(DOG128_SLIB) $(MOCK_LIB) $(GLMOCK_LIB) tests.o tests $(OBJ) $(MOCK_LIB_STATIC) $(GLMOCK_LIB_STATIC)

tests: tests.o
	$(CC) -o $@ *.o $(LIB_DIR) $(INC_DIR) -lwiringPi

test test-mock-lib: dogl $(MOCK_LIB)
	@./test.sh --with-mock-lib

test-mock-bin: $(MOCK_BIN)
	@./test.sh --with-mock-bin

test-real-pi: $(MOCK_LIB)
	@./test.sh
