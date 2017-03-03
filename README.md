# Orthogonal - a dual vision platformer game

## Introduction
The game is currently only a prototype/map editor

## Control
use `wasd` to control the character on the left

use `arrow keys` to control the characters on the right

press `Esc` to exit the game

## Map editor
use `left mouse button` to select areas in both view port

press `right mouse button` to cancel the selection

when you have selections on both view port, press `number keys` to fill the selection with one type of blocks

`1`: fill with air

`2`: fill with solid blocks

## Installation
This game only compiles in Linux by now

### Required libraries:
libSDL2, libSDL2\_image, libjsoncpp

#### For Fedora users:
Run
```bash
sudo dnf install make libSDL2-devel SDL2_image-devel jsoncpp-devel
```

### Build the game:
Enter the directory of this project and run
```bash
make
```

### Run the game:
Run
```bash
./game [mapnumber]
```
where `[mapnumber]` is here to tell the game to load the map in folder `assets/` named `test[mapnumber].map`
