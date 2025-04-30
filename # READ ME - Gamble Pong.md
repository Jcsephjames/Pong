# READ ME - Gamble Pong
## Overview
Gamble Pong is a customized version of the classic Pong game with additional features and modes, including a QuickPlay, Set-upPlay, Obstacle Mode and a Chaos Mode. Players can customize colors, themes, and visual effects to enhance their gameplay experience.

## Features
- Multiple game modes: Quick Play, Set-up Play, Obstacle Mode and Chaos Mode
- AI with adjustable difficulty levels
- Customizable colors and themes
- Visual effects: explosion, trail, animated backgrounds (coming soon)
- Settings menu for various game options

## Setup and Installation

### Dependencies
- **raylib**: A simple and easy-to-use library to enjoy videogames programming.
- **C Compiler**: Ensure you have a C compiler installed (e.g., GCC).

### Run With
gcc GamblePong.c src/SoundManager.c src/SettingsMenu.c src/AI.c src/Custom.c src/GameLogic.c src/Menu.c src/Animations.c src/Global.c src/Tutorial.c -o game \
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
    gcc -o gamblepong gamblepong.c -lraylib
    ```

4. **Run the game**:
    ```sh
    ./gamblepong
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
  - `P`: Pause the game
  - `M`: Return to main menu
  - `R`: Restart the game
  - `D`: Enter Double or Nothing mode
  - `V`: Open settings
  - `C`: Open controls
  - `H`: Toggle AI

### Game Modes
- **Quick Play**: Faster-paced version of the game.
- **SetUp Play**: A fully customizable game of Pong.
- **Obstacle Mode**: Introduces obstacles on the field.
- **Chaos Mode**: Under Construction.


### Customization
- Access the customization menu to change colors for paddles, ball, background, text, and effects. Predefined themes are also available.

## Credits
Developed by Joseph.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSEdetails).
