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
all: prep $(EXEC)

prep:
	rm -rf $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INC) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(EXEC) $(BUILD_DIR)/*.o
	rm -rf $(BUILD_DIR)

.PHONY: all clean prep
