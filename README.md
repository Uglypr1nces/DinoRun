# DinoRun - A Simple 2D Game Built with C++ and SDL2

DinoRun is a fun and simple 2D platformer game inspired by Google's offline dinosaur game. The player controls a dinosaur that must avoid obstacles by jumping over them.

![DinoRun Screenshot](screenshot.png)

## Features
- Player-controlled jumping mechanics
- Procedurally generated obstacles
- Collision detection
- Game over logic when an obstacle is hit

## Getting Started

### Prerequisites
To run the game, you'll need:
- C++11 or later
- [SDL2 Library](https://www.libsdl.org/download-2.0.php) installed on your system

### Installing SDL2

#### On Linux
You can install SDL2 using your package manager:
```bash
sudo apt-get install libsdl2-dev
```

#### On MacOS
Install SDL2 using Homebrew:
```bash
brew install sdl2
```

#### On Windows
Install SDL2 using Homebrew:

Download the SDL2 development libraries from the official website and follow the instructions to set it up with your compiler/IDE (Visual Studio, MinGW, etc.).

## Cloning the game
 1. Clone the repository:

```bash
git clone https://github.com/Uglypr1nces/DinoRun.git
cd DinoRun
```

2. Compile the game: Linux/MacOS:
```bash
g++ -o DinoRun main.cpp -lSDL2
```

Compile the game on Windows
2. Compile the game: Linux/MacOS:
```bash
g++ -o DinoRun.exe main.cpp -lmingw32 -lSDL2main -lSDL2
```

3. Run the game

```bash
./DinoRun
```
