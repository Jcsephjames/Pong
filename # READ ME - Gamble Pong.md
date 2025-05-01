# READ ME - Gamble Pong
## Overview
Gamble Pong is an upadated version of the classic game Pong, with different modes such as, Set-up, Obstacle and Chaos Mode. Players can indulge in all the different customizable options to enhance their player experience

## Features
- Multiple game modes: Quick Play, Set-up Play, Obstacle Mode and Chaos Mode
- Including a working Tutorial to guide new players
- AI with adjustable difficulty levels
- Customizable colors and themes
- Visual effects: explosions, trails and menu animations
- Settings menu for various game options

## Setup and Installation

### Dependencies
- **raylib**: A simple and easy-to-use library to enjoy videogames programming.
- **C Compiler**: Ensure you have a C compiler installed. The example 'Run With' I am using is using GCC

### Run With
gcc GamblePong.c src/*.c -o game \
-Iinclude \
-I/opt/homebrew/include \
-L/opt/homebrew/lib \
-framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio \
-lraylib -lm

Then,
  ./game

### Installation
1. **Clone the repository**:
    ```sh
    git clone https://github.com/jcsephmoore/gamblepong.git
    cd gamblepong
    ```

2. **Install raylib**:
    Follow the instructions on the [raylib website](https://www.raylibr) your operating system.

3. **Compile the game**:
    ```sh
    gcc GamblePong.c src/*.c -o game \
  -Iinclude \
  -I/opt/homebrew/include \
  -L/opt/homebrew/lib \
  -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio \
  -lraylib -lm
    ```

4. **Run the game**:
    ```sh
    ./game
    ```

## How to Play

### Controls
- **Player 1**: 
  - `W`: Move paddle up
  - `S`: Move paddle down
- **Player 2**: 
  - `Up Arrow`: Move paddle up
  - `Down Arrow`: Move paddle down
- **General Controls**:
  - `T`: To Enter the Tutorial
  - `P`: Pause the game
  - `M`: Return to main menu
  - `R`: Restart the game
  - `D`: Enter Double or Nothing mode
  - `V`: Open settings
  - `C`: Open controls
  - `H`: Toggle AI

### Game Modes
- **Tutorial**: A way to teach new players the basics.
- **Quick Play**: Faster-paced version of the game.
- **SetUp Play**: A fully customizable game of Pong.
- **Obstacle Mode**: Introduces obstacles on the field.
- **Chaos Mode**: Under Construction.

## Credits
Developed by Joseph.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSEdetails).
