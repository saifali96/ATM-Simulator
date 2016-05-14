CC=gcc

INC_DIR = include
SRC_DIR = src
BIN_DIR = bin
CFLAGS = -std=c99 -Wall -Werror -I./include -I.

atmsimulator:
	$(CC) $(CFLAGS) $(SRC_DIR)/atm.c -o $(BIN_DIR)/atmsimulator

clean:
	rm -f $(BIN_DIR)/atmsimulator
default:
	atmsimulator