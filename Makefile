OUTPUT=grapher
OUT_DIR=build
SRC_DIR=src
OBJECTS=$(shell ls src/*.cpp | sed -E 's|src/(.*)\.cpp|$(OUT_DIR)/\1.o|g')

CXX=g++
CXX_VERSION=c++14

FLAGS=-Wall -g
LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

.PHONY: directories

all: directories program

directories: $(OUT_DIR)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

$(OUT_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) -std=$(CXX_VERSION) $(FLAGS) -c $< -o $@

program: $(OBJECTS)
	$(CXX) build/* -o $(OUTPUT) $(LIBS) $(FLAGS)

clean:
	rm -rf $(OUT_DIR)
	rm -f $(OUTPUT)

