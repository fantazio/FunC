CC? = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -Werror
SRC = $(wildcard src/*.c)
RES = func
BUILD_DIR = func/
SRC_TEST = check/main.c
RES_TEST = check/test

library: $(BUILD_DIR)
	cp -r src/* $^

%.o: %.c
	$(COMPILE.c) $^ -o $@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

check: library
	$(CC) $(CFLAGS) $(SRC_TEST) -o $(RES_TEST)
	./$(RES_TEST)

clean:
	rm -rf $(wildcard src/*.o) $(wildcard check/*.o) $(BUILD_DIR) $(RES_TEST)*
