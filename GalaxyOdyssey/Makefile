SRC_DIR := src
INC_DIR := include
BUILD_DIR := ./build

# Compiler and flags
CXX := g++
INC := -I$(INC_DIR)

CXXFLAGS := -Wall
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

# Source and object files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Executable name
EXEC := GalaxyOdyssey

# Targets
all: prep $(EXEC)

prep:
	rm -rf $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INC) $^ -o $@ $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(EXEC) $(BUILD_DIR)/*.o
	rm -rf $(BUILD_DIR)

run: $(EXEC)
    LD_LIBRARY_PATH=$(LIB_DIR) ./$(EXEC)

.PHONY: all clean run