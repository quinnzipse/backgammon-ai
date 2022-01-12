PROGRAM_NAME = "backgammon-ai"

# Compiler Options
CC=g++
CFLAGS=-Wall -Wextra -Werror -g -std=c++20

# Folders
SRC=src
BIN=bin

# Put list of source files in variable
SOURCE_FILES=$(shell find $(SRC) -name "*.cpp") 
OBJS=$(patsubst $(SRC)/%.cpp,$(BIN)/%.o,$(SOURCE_FILES))

.PHONY: all
$(PROGRAM_NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(BIN)/%.o: $(SRC)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BIN)/
	rm $(PROGRAM_NAME)