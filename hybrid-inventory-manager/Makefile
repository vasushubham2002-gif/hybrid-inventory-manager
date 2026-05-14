CC = gcc
CXX = g++
CFLAGS = -Iinclude -Wall -Wextra -std=c11
CXXFLAGS = -Iinclude -Wall -Wextra -std=c++11
OBJ_C = src/inventory.o
OBJ_CPP = src/InventoryManager.o src/main.o
TARGET = inventory_manager

all: $(TARGET)

$(TARGET): $(OBJ_C) $(OBJ_CPP)
	$(CXX) -o $@ $^

src/inventory.o: src/inventory.c include/inventory.h
	$(CC) $(CFLAGS) -c $< -o $@

src/InventoryManager.o: src/InventoryManager.cpp include/inventory.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/main.o: src/main.cpp include/inventory.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_C) $(OBJ_CPP) $(TARGET)

.PHONY: all clean