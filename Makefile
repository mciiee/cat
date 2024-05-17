FILE = cat
SRC_DIR = src
BUILD_DIR = build
CFLAGS = -std=c11 -Wall
COMPILER = gcc

all: build

build: clean
	gcc $(SRC_DIR)/$(FILE).c -o $(BUILD_DIR)/$(FILE) $(CFLAGS)

clean: 
	rm -rf $(BUILD_DIR)/*


