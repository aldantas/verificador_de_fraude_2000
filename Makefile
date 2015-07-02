CC=g++
CFLAGS=-std=c++11 -I. -c
LDFLAGS=-lpthread
SRC=main.cpp csvreader.cpp csvwriter.cpp
OBJ=$(SRC:.cpp=.o)
TARGET=main

all: $(SRC) $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o $(TARGET)
