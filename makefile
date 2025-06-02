# Nombre del ejecutable
TARGET = programa.exe

# Carpetas
SRC_DIR = src
INC_DIR = headers

# Compilador y flags
CXX = g++
CXXFLAGS = -std=c++17 -I$(INC_DIR) -Wall -Wextra

# Archivos fuente y objetos
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)

# Regla por defecto
all: $(TARGET)

# Regla de construcción del ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Reglas para compilar cada archivo objeto
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)


