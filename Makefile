CC = gcc
CFLAGS = -Wall -g -Iinclude $(shell pkg-config --cflags gtk+-3.0 pango)
LIBS = $(shell pkg-config --libs gtk+-3.0 pango) -lpcap -ljson-c
SRCS = src/main.c src/scanner.c src/gui/gui.c
OBJS = $(SRCS:.c=.o)
TARGET = bin/network_scanner

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

clean:
	rm -f $(TARGET) $(OBJS)

