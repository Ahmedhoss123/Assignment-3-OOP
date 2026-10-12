# FCAI Game Hub

[![C++17](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Platform](https://img.shields.io/badge/platform-console-lightgrey)](#getting-started)
[![Architecture](https://img.shields.io/badge/architecture-object--oriented-blueviolet)](#system-architecture)
[![Repository](https://img.shields.io/badge/repository-GitHub-181717?logo=github)](https://github.com/Ahmedhoss123/Assignment-3-OOP)

A C++17 console game hub containing **14 playable Tic-Tac-Toe variants**, including classic, numerical, word-based, spatial, memory, and meta-board games. The project applies reusable object-oriented abstractions for boards, players, user interfaces, and game management while supporting human and computer-controlled players.

> **Project status:** Educational console application developed as an FCAI Object-Oriented Programming assignment.

## Table of Contents

- [Overview](#overview)
- [Key Features and Metrics](#key-features-and-metrics)
- [Game Modes](#game-modes)
- [System Architecture](#system-architecture)
- [Tech Stack](#tech-stack)
- [Repository Structure](#repository-structure)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [AI and Algorithms](#ai-and-algorithms)
- [Known Limitations](#known-limitations)
- [Contributing](#contributing)
- [License](#license)

## Overview

FCAI Game Hub provides a single menu-driven interface for exploring multiple implementations of Tic-Tac-Toe and related board-game mechanics. Instead of building each game as an isolated program, the codebase shares common abstractions for game state, players, moves, user interaction, and the game loop.

The result is a compact learning project that demonstrates how polymorphism, templates, composition, and game-specific rule implementations can be combined to support substantially different games behind a consistent runtime flow.

## Key Features and Metrics

- **14 game modes** available from the main console menu.
- **Human-versus-human and human-versus-computer** setup flows where supported by each game UI.
- **Reusable game framework** built around generic `Board<T>`, `Player<T>`, `UI<T>`, and `GameManager<T>` abstractions.
- **Multiple board models**, including 3×3, 4×4, 5×5, 6×7, pyramid, and nested Ultimate Tic-Tac-Toe layouts.
- **Specialized rule systems**, including word validation, numerical sum evaluation, moving pieces, hidden information, obstacles, expiring moves, and reverse-win conditions.
- **AI implementations** using game-specific strategies such as minimax, heuristic evaluation, dictionary lookup, and position-based decision making.
- **C++17 codebase** with Visual Studio project support for Win32 and x64 Debug/Release configurations.

### Engineering metrics

| Metric | Value |
|---|---:|
| Game modes | **14** |
| Primary language | **C++** |
| Language composition | **99.6% C++, 0.4% C** |
| Standard | **C++17** |
| Runtime model | **Interactive console application** |
| External services | **None** |
| Automated benchmark data | **Not currently published** |

> Performance claims such as latency, throughput, test coverage, and AI response time are intentionally not stated because the repository does not currently include a benchmark suite or published measurements.

## Game Modes

| Menu option | Game | Core mechanic |
|---:|---|---|
| 0 | Classic Tic-Tac-Toe | Traditional 3×3 X/O gameplay |
| 1 | SUS | Create the word `SUS` on the board |
| 2 | Four-in-a-Row | Connect four pieces on a vertical board |
| 3 | 5×5 Tic-Tac-Toe | Find a three-in-a-row pattern on a larger board |
| 4 | Word Tic-Tac-Toe | Form valid three-letter words using `dic.txt` |
| 5 | Misère Tic-Tac-Toe | Avoid forming the winning line |
| 6 | Diamond Tic-Tac-Toe | Meet the variant's simultaneous line conditions |
| 7 | 4×4 Moving Tic-Tac-Toe | Place and later move pieces on a 4×4 board |
| 8 | Pyramid Tic-Tac-Toe | Play on a pyramid-shaped board layout |
| 9 | Numerical Tic-Tac-Toe | Use numbers whose winning combination sums to 15 |
| 10 | Obstacles Tic-Tac-Toe | Play around dynamically introduced obstacles |
| 11 | Infinity Tic-Tac-Toe | Older moves expire as new moves are made |
| 12 | Ultimate Tic-Tac-Toe | Play a 3×3 board of smaller Tic-Tac-Toe boards |
| 13 | Memory Tic-Tac-Toe | Play with hidden board information |
| 14 | Exit | Close the application |

## System Architecture

The application follows a reusable, object-oriented game-engine structure:

```text
                    +-------------------+
                    |     main.cpp      |
                    |  Menu / Launcher   |
                    +---------+---------+
                              |
              selects a game and creates its components
                              |
       +----------------------+----------------------+
       |                      |                      |
+------v------+        +------v------+        +------v------+
| Game UI     |        | Game Board  |        | Players     |
| UI<T>       |        | Board<T>    |        | Player<T>   |
+------+------+        +------+------+        +------+------+ 
       |                      |                      |
       +----------------------+----------------------+
                              |
                    +---------v---------+
                    |  GameManager<T>   |
                    | turn loop / state |
                    +-------------------+
```

### Design principles

- **Template-based reuse:** Core classes are parameterized by the board cell type, allowing character-based and integer-based games to share the same framework.
- **Polymorphism:** Each game supplies its own board rules, move validation, win detection, and UI behavior through specialized classes.
- **Separation of concerns:** Board state, player behavior, user interaction, and game orchestration are kept in separate components.
- **Strategy-oriented AI:** Computer players can implement different decision strategies without changing the generic game loop.
- **Composition:** `main.cpp` assembles the appropriate UI, board, players, and `GameManager` for the selected mode.

## Tech Stack

| Area | Technology |
|---|---|
| Language | C++17 |
| Paradigm | Object-oriented programming and generic programming |
| Interface | Interactive terminal/console UI |
| Build tooling | Microsoft Visual Studio solution/project; compiler command line also possible |
| Compiler target | Visual C++ toolset v143 in the supplied project configuration |
| Algorithms | Minimax, heuristic evaluation, depth-first search, rule-based validation |
| Data structures | Vectors, arrays, dynamic allocations, sets/dictionary lookups |
| Data file | `dic.txt` for Word Tic-Tac-Toe vocabulary |

## Repository Structure

```text
Assignment-3-OOP/
├── main.cpp                    # Main menu and game selection
├── BoardGame_Classes.h         # Generic Board, Player, UI, and GameManager types
├── XO_Classes.*                # Classic Tic-Tac-Toe
├── SUS_*                       # SUS game
├── XO4R_*                      # Four-in-a-Row
├── TTC5_*                     # 5×5 Tic-Tac-Toe
├── WordTTT_*                  # Word Tic-Tac-Toe and dictionary-aware AI
├── MisereTTT_*                # Misère Tic-Tac-Toe
├── DiamondTTT_*               # Diamond Tic-Tac-Toe
├── FourByFour*                # 4×4 moving Tic-Tac-Toe
├── Pyramid*                   # Pyramid Tic-Tac-Toe
├── NumTTT_*                  # Numerical Tic-Tac-Toe
├── Obstacles*                # Obstacles Tic-Tac-Toe
├── InfinityTTT_*             # Infinity Tic-Tac-Toe
├── UltimateTTT_*             # Ultimate Tic-Tac-Toe
├── MemoryTTT_*               # Memory Tic-Tac-Toe
├── AIPlayer*                 # AI player implementations
├── dic.txt                   # Word-game dictionary
├── Ass3.sln                  # Visual Studio solution
├── Ass3.vcxproj              # Visual Studio project
└── README.md
```

## Getting Started

### Prerequisites

Choose one of the following development environments:

- **Windows:** Visual Studio 2022 with the Desktop development with C++ workload.
- **Cross-platform:** A C++17-compatible compiler such as GCC or Clang.
- A terminal capable of reading standard input and displaying standard output.

No database, network service, package manager, or environment variables are required.

### 1. Clone the repository

```bash
git clone https://github.com/Ahmedhoss123/Assignment-3-OOP.git
cd Assignment-3-OOP
```

### 2. Build with Visual Studio

1. Open `Ass3.sln` in Visual Studio 2022.
2. Select `Debug` or `Release`.
3. Select `x64` or `Win32`.
4. Build the solution with **Build → Build Solution**.
5. Run the console application with **Debug → Start Without Debugging**.

The supplied project targets the Visual C++ `v143` toolset and defines both Win32 and x64 configurations.

### 3. Build from the command line

The repository is a multi-file C++ application. A command-line build must compile the source files required by `main.cpp` and link them into one executable. For GCC or Clang, use a command similar to the following and adjust the source list if your compiler reports missing or unused translation units:

```bash
g++ -std=c++17 -O2 -Wall -Wextra \
  main.cpp \
  AIPlayer.cpp AIPlayer3.cpp \
  DiamondTTT_Board.cpp DiamondTTT_UI.Cpp \
  FourByFourBoard.cpp FourByFourUI.cpp \
  InfinityTTT_Board.cpp InfinityTTT_UI.cpp \
  MemoryTTT_Board.cpp MemoryTTT_UI.cpp \
  MisereTTT_Board.cpp \
  NumTTT_Board.cpp NumTTT_UI.cpp \
  ObstaclesBoard.cpp ObstaclesUI.cpp \
  PyramidBoard.cpp PyramidUI.cpp \
  SUS_Board.cpp SUS_UI.cpp \
  TTC5_Board.cpp TTC5_UI.cpp \
  UltimateTTT_Board.cpp UltimateTTT_UI.cpp \
  WordTTT_Board.cpp WordTTT_SmartAI.cpp WordTTT_UI.cpp \
  XO4R_Board.cpp XO4R_UI.cpp \
  XO_Classes.cpp \
  -o game_hub
```

Run the executable with:

```bash
./game_hub
```

On Windows using MinGW, run `game_hub.exe` instead.

> **Build note:** Source filenames are case-sensitive on Linux and macOS. In particular, preserve the repository's `DiamondTTT_UI.Cpp` filename exactly when building on a case-sensitive filesystem. The Visual Studio project is the recommended build path on Windows.

## Usage

Start the application and select a mode from the main menu:

```text
=============================
 FCAI Game Hub Menu
=============================
0. Classic Tic-Tac-Toe (X-O)
1. SUS Game
2. Four-in-a-Row
...
13. Memory Tic-Tac-Toe
14. Exit
=============================
Enter your choice: 0
```

For supported modes, the setup flow generally asks for:

1. Player names.
2. Player type: human or computer.
3. Game-specific moves, such as coordinates, columns, numbers, or letters.

Example session:

```text
Enter your choice: 0
Enter Player X name: Alice
Choose Player X type:
1. Human
2. Computer
1
Enter Player O name: Bob
Choose Player O type:
1. Human
2. Computer
2
```

The exact move format is displayed by the selected game UI because each variant has different board dimensions and rules.

## AI and Algorithms

The repository contains several game-specific computer-player implementations rather than one universal AI. Depending on the selected mode, the implementation may use:

- **Minimax search** for evaluating future game states.
- **Alpha-beta pruning** to reduce unnecessary branches during search.
- **Heuristic evaluation** for larger or more complex boards.
- **Position-based strategies** for prioritizing useful cells or moves.
- **Dictionary lookup** and word validation for Word Tic-Tac-Toe.
- **Variant-specific rule logic** for numerical, moving, reverse-win, and meta-board games.

AI difficulty and response time depend on the selected game and the current board state. The repository does not currently publish formal timing benchmarks.

## Known Limitations

- This is a console application; there is no graphical interface or network multiplayer mode.
- Some AI searches may take longer on complex positions.
- Terminal screen-clearing behavior can vary between operating systems and shells.
- The repository does not currently include an automated test suite or CI workflow.
- The repository does not currently include a license file, despite earlier documentation referring to MIT licensing.
- The Visual Studio project configuration may require source-file review when adding or building every game variant; verify the project file includes all translation units needed by your selected configuration.

## Contributing

Contributions and improvements are welcome.

1. Fork the repository.
2. Create a focused branch:

   ```bash
   git checkout -b feature/add-new-variant
   ```

3. Make the change while preserving the existing board/player/UI abstractions.
4. Build the project and manually test the affected game modes.
5. Commit with a clear message:

   ```bash
   git commit -m "Add new Tic-Tac-Toe variant"
   ```

6. Push the branch and open a pull request.

For new game modes, include the board rules, move validation, win/draw detection, UI flow, player setup, and any required AI behavior. Please also update this README when adding or renaming a mode.

## License

No `LICENSE` file is currently present in the repository, so the project does not yet declare a formal open-source license. Add a license file before distributing the code under specific reuse terms.

## Credits

- **Project:** FCAI Game Hub
- **Author:** Abdallah Ahmed
- **Institution:** Faculty of Computers and Artificial Intelligence (FCAI)
- **Repository:** [Ahmedhoss123/Assignment-3-OOP](https://github.com/Ahmedhoss123/Assignment-3-OOP)

---

If you find the project useful for learning C++, OOP, or game AI, consider starring the repository. 🎮
