# Cub3D

A 3D game engine built with C and raycasting techniques, inspired by the classic Wolfenstein 3D.  This project creates a first-person perspective in a maze using raycasting algorithms.

## 📋 Table of Contents

- [About](#about)
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Controls](#controls)
- [Map Configuration](#map-configuration)

## 🎮 About

Cub3D is a graphics project that introduces raycasting techniques to render a 3D graphical representation of a maze from a first-person perspective. The project uses the MiniLibX graphics library and implements fundamental concepts of computer graphics.

## ✨ Features

- **Raycasting Engine**: Real-time 3D rendering using raycasting algorithm
- **Texture Mapping**: Wall textures for different orientations (North, South, East, West)
- **Player Movement**: Smooth navigation through the maze
- **Collision Detection**: Prevents walking through walls
- **Map Parsing**: Custom map configuration from `.cub` files
- **First-Person View**: Immersive 3D perspective

## 🔧 Prerequisites

- GCC compiler
- Make
- MiniLibX library
- X11 (for Linux) or compatible graphics library

## 📦 Installation

1. Clone the repository:
```bash
git clone https://github.com/Moraouid/Cub3d.git
cd Cub3d
```

2. Compile the project:
```bash
make
```

This will generate the `cub3D` executable.

## 🚀 Usage

Run the program with a map file as an argument: 

```bash
./cub3D assets/maps/[map_name].cub
```

Example:
```bash
./cub3D assets/maps/map. cub
```

## 📁 Project Structure

```
Cub3d/
├── includes/           # Header files
│   ├── cub3d.h        # Main header file
│   └── get_next_line/ # GNL utility for file reading
├── src/               # Source files
│   ├── cub3d.c        # Main program entry
│   ├── start_game.c   # Game initialization
│   ├── parsing/       # Map and configuration parsing
│   ├── render/        # Rendering and raycasting logic
│   └── helper/        # Utility functions
├── assets/            # Game assets
│   ├── maps/          # Map configuration files
│   └── textures/      # Wall texture images
├── Makefile           # Build configuration
└── README.md          # Project documentation
```

## 🎯 Controls

- **W / ↑**:  Move forward
- **S / ↓**: Move backward
- **A**:  Strafe left
- **D**:  Strafe right
- **← / →**:  Rotate camera left/right
- **ESC**: Exit the game

## 🗺️ Map Configuration

Map files (`.cub`) define the game environment with the following elements:

### Texture Paths
```
NO ./assets/textures/north_texture.xpm
SO ./assets/textures/south_texture.xpm
WE ./assets/textures/west_texture.xpm
EA ./assets/textures/east_texture.xpm
```

### Colors (RGB format)
```
F 220,100,0    # Floor color
C 225,30,0     # Ceiling color
```

### Map Layout
- `1`: Wall
- `0`: Empty space
- `N/S/E/W`: Player starting position and orientation

Example map:
```
111111
100001
10N001
100001
111111
```

## 🛠️ Development

### Cleaning build files: 
```bash
make clean    # Remove object files
make fclean   # Remove object files and executable
make re       # Rebuild the project
```

## 📝 License

This project is part of the 42 School curriculum. 

## 👥 Contributors

- [Moraouid](https://github.com/Moraouid)

## 🙏 Acknowledgments

- 42 School for the project guidelines
- MiniLibX graphics library
- Lode Vandevenne's raycasting tutorial

---

**Note**: This project is educational and created as part of the 42 School curriculum. 
