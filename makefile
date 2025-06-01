# Compilador
CXX = g++

# Flags
CXXFLAGS = -I headers

# Archivos fuente y ejecutable
SRC = $(wildcard src/*.cpp)
OUT = programa

# Regla principal
all: $(OUT)

$(OUT): $(SRC)
	$(CXX) -o $@ $^ $(CXXFLAGS)

# Limpiar archivos generados
clean:
	del /Q $(OUT).exe 2>nul || rm -f $(OUT)

