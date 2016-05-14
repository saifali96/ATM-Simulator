CC=g++

INC_DIR = include
SRC_DIR = src
BIN_DIR = bin
CFLAGS = -std=c++11 -Wall -Werror -I./include -I.

atmsimulator:
	$(CC) $(CFLAGS) $(SRC_DIR)/atm.cpp -o $(BIN_DIR)/atmsimulator
clean:
	rm -f $(BIN_DIR)/atmsimulator
default:
	atmsimulator