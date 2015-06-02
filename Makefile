CC? = gcc
CFLAGS? = -std=c99 -pedantic -Wall -Wextra -Werror
SRC =
RES= func
OBJ = $(SRC:.c=.o)
BUILD_DIR = lib/
SRC_TEST =
RES_TEST = check/test

library: $(OBJ) | $(BUILD_DIR)
	ar csr $(BUILD_DIR)lib$(RES).a $^

%.o: %.c
	$(COMPILE.c) $^ -o $@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

check: library
	$(CC) -static $(SRC_TEST) -L$(BUILD_DIR) -l$(RES) -o $(RES_TEST)
	./$(RES_TEST)

clean:
	rm -rf $(BUILD_DIR) $(OBJ) $(RES_TEST)
