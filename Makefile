
all:
	$(MAKE) -C src
	$(MAKE) -C example

mock:
	$(MAKE) -C src mock
	$(MAKE) -C example mock
	
glmock:
	$(MAKE) -C src glmock
	$(MAKE) -C example glmock

mock-mac:
	$(MAKE) -C src mock
	$(MAKE) -C example mock_mac

install:
	$(MAKE) -C src install

uninstall:
	$(MAKE) -C src uninstall

clean:
	$(MAKE) -C src clean
	$(MAKE) -C example clean

test test-mock-lib: dogl $(MOCK_LIB)
	@./test.sh --with-mock-lib

test-mock-bin: $(MOCK_BIN)
	@./test.sh --with-mock-bin

test-real-pi: $(MOCK_LIB)
	@./test.sh
