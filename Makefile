CC? = clang
CFLAGS? = -std=c99 -pedantic -Wall -Wextra -Werror
SRC = src/func.c
RES= func
OBJ = $(SRC:.c=.o)
BUILD_DIR = lib/
SRC_TEST = check/main.c
RES_TEST = check/test

library: $(OBJ) | $(BUILD_DIR)
	ar csr $(BUILD_DIR)lib$(RES).a $^
	rm -rf $(BUILD_DIR) $(OBJ)

%.o: %.c
	$(COMPILE.c) $^ -o $@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

check: library
	$(CC) $(SRC_TEST) -o $(RES_TEST)
	./$(RES_TEST)

clean:
	rm -rf $(BUILD_DIR) $(OBJ) $(RES_TEST)
