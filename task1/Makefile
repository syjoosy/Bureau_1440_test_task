CC = gcc
CFLAGS = -Wall -Wextra -O2

TARGET = task1

$(TARGET): task1.o
	$(CC) $(CFLAGS) task1.o -o $(TARGET)

task1.o: task1.c
	$(CC) $(CFLAGS) -c task1.c -o task1.o

clean:
	rm -f *.o $(TARGET)
