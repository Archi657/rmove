# Makefile

CXX = gcc
TARGET = rme
SOURCES = $(wildcard src/*.c)
BINDIR = /usr/bin/

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX)  $(SOURCES) -o $(TARGET)

install: $(TARGET)
	mkdir -p $(BINDIR)
	cp $(TARGET) $(BINDIR)

