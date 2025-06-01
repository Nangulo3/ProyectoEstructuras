# Makefile

# Variables
CXX = g++
CXXFLAGS = -I headers
SRC = $(wildcard src/*.cpp)
OUT = programa

# Regla principal
all:
	$(CXX) -o $(OUT) $(SRC) $(CXXFLAGS)

# Limpieza opcional
clean:
	rm -f $(OUT)
