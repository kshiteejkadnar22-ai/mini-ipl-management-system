CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2

TARGET = ipl_manager

all: $(TARGET)

$(TARGET): ipl_manager.c
	$(CC) $(CFLAGS) -o $(TARGET) ipl_manager.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean

