 # Makefile
CC = g++
CFLAGS = -Wall -Iinclude
TARGET = sys_util
SOURCES = src/main.cpp src/sys_util.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)

