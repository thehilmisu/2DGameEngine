SDPLOG_INCLUDE = thirdparty/spdlog/include
TINYXML_INCLUDE = thirdparty/tinyxml
IMGUI_INCLUDE = thirdparty/imgui
IMGUI_BACKENDS = thirdparty/imgui/backends

# Compiler and flags
CXX = g++
CXXFLAGS = -g -std=c++17 -Wall -Iinclude -I$(SDPLOG_INCLUDE) -I$(TINYXML_INCLUDE) -I$(IMGUI_INCLUDE) -I$(IMGUI_BACKENDS) `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_image -lSDL2_mixer -lSDL2_ttf -ltinyxml

IMGUI_SOURCES = \
				thirdparty/imgui/imgui.cpp \
				thirdparty/imgui/imgui_draw.cpp \
				thirdparty/imgui/imgui_widgets.cpp \
				thirdparty/imgui/imgui_tables.cpp \
				thirdparty/imgui/backends/imgui_impl_sdl2.cpp \
				thirdparty/imgui/backends/imgui_impl_sdlrenderer2.cpp \


# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Output binary
TARGET = $(BIN_DIR)/GameEngine

# Source files (recursive search)
SRCS = $(shell find $(SRC_DIR) -type f -name "*.cpp")
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

SRCS += $(IMGUI_SOURCES)

# Default target
all: $(TARGET)

# Link the object files to create the binary
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compile source files into object files, handling subdirectories
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create output directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean up object files and the binary
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Phony targets
.PHONY: all clean
