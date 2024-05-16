# Directories
SRC_DIR := src
INC_DIR := include
BUILD_DIR := ./build

# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
INC := -I$(INC_DIR)

# Source and object files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Executable name
EXEC := MyGame

# Targets
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INC) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -f $(EXEC) $(BUILD_DIR)/*.o

.PHONY: all clean
