# 2D Game Engine

This is a 2D game engine with an example game written in it built using C++ and SDL2. The engine supports various features such as animation, character management, input handling, map parsing, and rendering.

## Features

- **Animation**: Supports sprite animations for characters.
- **Character Management**: Handles different character states and actions.
- **Input Handling**: Processes user inputs for controlling characters.
- **Map Parsing**: Loads and parses game maps.
- **Rendering**: Renders game objects and backgrounds using SDL2.

## Getting Started

### Prerequisites

- C++17 compatible compiler
- SDL2
- SDL2_image
- SDL2_mixer
- SDL2_ttf
- TinyXML

### Building the Project

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/2DGameEngine.git
    cd 2DGameEngine
    ```

2. Install the required libraries. On a Debian-based system, you can use:
    ```sh
    sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev libtinyxml-dev
    ```

3. Build the project using `make`:
    ```sh
    make
    ```

### Running the Game

After building the project, you can run the game using:
```sh
./bin/GameEngine