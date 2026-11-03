# Catch the Box

A simple 2D clicking game built using **C++** and **SFML 3.0.2**.

The objective is to click the moving target before it teleports to another position. The game includes multiple difficulty levels and a scoring system.

## Features

- Three difficulty levels: Easy, Medium, and Hard.
- Target changes position periodically.
- Target changes color.
- Score tracking.
- Menu, gameplay, and game-over screens.
- Retry option that preserves the selected difficulty.

## Technologies Used

- **Language:** C++
- **Graphics Library:** SFML 3.0.2
- **Compiler:** GCC (MinGW-w64)
- **IDE:** Visual Studio Code

## Project Structure

```text
ClickTheBox/
├── assets/
│   └── arialbd.ttf
├── include/
│   ├── Colors.h
│   ├── Game.h
│   └── Target.h
├── src/
│   ├── Game.cpp
│   └── Target.cpp
├── .gitignore
└── main.cpp
```

## Requirements

- C++ compiler supporting C++17 or later.
- SFML 3.0.2.
- Windows (current development environment).

## How to Build and Run

### Prerequisites

- Windows 10/11
- GCC compiler (MSYS2 UCRT64)
- SFML 3.0.2
- Visual Studio Code (optional)

### Build Instructions

1. Make sure SFML 3.0.2 is installed and configured in your MSYS2 UCRT64 environment.
2. Open the project folder in VS Code.
3. Open the terminal and navigate to the project directory.
4. Compile the project using:

```bash
g++ main.cpp src/Game.cpp src/Target.cpp -o main.exe -Iinclude -lsfml-graphics -lsfml-window -lsfml-system
```

### Run the Game

After successful compilation, execute:

```powershell
.\main.exe
```

**Note:** Run the executable from the project's root directory so the game can locate its font file at `assets/arialbd.ttf`.


## Learning Objectives

This project was developed to practise:

- C++ programming.
- Object-oriented programming.
- Header and source file organization.
- Working with the SFML library.
- Basic game loops and event handling.
- Git and GitHub version control.

## Author

**Htrap1**

