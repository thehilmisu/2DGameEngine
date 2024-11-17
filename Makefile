# Directories
SDPLOG_DIR = thirdparty/spdlog/include
TINYXML_DIR = thirdparty/tinyxml
IMGUI_DIR = thirdparty/imgui
IMGUI_BACKENDS_DIR = thirdparty/imgui/backends

# Compiler and flags
CXX = g++
CXXFLAGS = -g -std=c++17 -Wall \
    -Iinclude -I$(SDPLOG_DIR) -I$(TINYXML_DIR) \
    -I$(IMGUI_DIR) -I$(IMGUI_BACKENDS_DIR) \
    -DIMGUI_IMPL_OPENGL_LOADER_GLEW `sdl2-config --cflags`

LDFLAGS = `sdl2-config --libs` -lSDL2_image -lSDL2_mixer -lSDL2_ttf \
    -ltinyxml -lGL -lGLEW

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Output binary
TARGET = $(BIN_DIR)/GameEngine

# ImGui source files
IMGUI_SRCS = \
    $(IMGUI_DIR)/imgui.cpp \
    $(IMGUI_DIR)/imgui_draw.cpp \
    $(IMGUI_DIR)/imgui_widgets.cpp \
    $(IMGUI_DIR)/imgui_tables.cpp \
    $(IMGUI_DIR)/imgui_demo.cpp \
    $(IMGUI_BACKENDS_DIR)/imgui_impl_sdl2.cpp \
    $(IMGUI_BACKENDS_DIR)/imgui_impl_sdlrenderer2.cpp

# Source files (recursive search)
SRCS = $(shell find $(SRC_DIR) -type f -name "*.cpp") $(IMGUI_SRCS)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(filter $(SRC_DIR)/%.cpp,$(SRCS))) \
       $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(filter %.cpp,$(IMGUI_SRCS)))

# Default target
all: $(TARGET)

# Link the object files to create the binary
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Compile source files into object files, handling subdirectories
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile ImGui source files
$(OBJ_DIR)/%.o: %.cpp
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
