
all:
	$(MAKE) -C src
	$(MAKE) -C example
	$(MAKE) -C emu

mock:
	$(MAKE) -C src mock
	$(MAKE) -C example
	$(MAKE) -C emu

mock-mac:
	$(MAKE) -C src mock
	$(MAKE) -C example mock_mac
	$(MAKE) -f Makefile-Mac -C emu
clean:
	$(MAKE) -C src clean
	$(MAKE) -C example clean
	$(MAKE) -C emu clean

test test-mock-lib: dogl $(MOCK_LIB)
	@./test.sh --with-mock-lib

test-mock-bin: $(MOCK_BIN)
	@./test.sh --with-mock-bin

test-real-pi: $(MOCK_LIB)
	@./test.sh
