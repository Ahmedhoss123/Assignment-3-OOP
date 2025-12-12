# 🎮 FCAI Game Hub - The Ultimate Tic-Tac-Toe Collection

[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-Cross--Platform-green.svg)]()

> A comprehensive collection of 14 unique Tic-Tac-Toe variants with intelligent AI opponents! 🤖

## 📋 Table of Contents
- [About](#about)
- [Game Collection](#game-collection)
- [Features](#features)
- [Installation](#installation)
- [How to Play](#how-to-play)
- [AI Implementation](#ai-implementation)
- [Project Structure](#project-structure)
- [Technologies Used](#technologies-used)
- [Contributing](#contributing)
- [License](#license)
- [Credits](#credits)

## 🎯 About

Welcome to the **FCAI Game Hub** - where Tic-Tac-Toe meets innovation! 🚀 

This project showcases 14 different variants of the classic Tic-Tac-Toe game, each with unique rules and mechanics. Built using **Object-Oriented Programming** principles in C++, this collection features sophisticated AI opponents powered by **Minimax algorithms** with **Alpha-Beta pruning** for an unbeatable gaming experience!

Perfect for:
- 🎓 Learning game AI algorithms
- 💻 Understanding OOP design patterns
- 🎲 Having endless fun with friends (or crushing them with AI)
- 🧠 Challenging your strategic thinking

## 🎲 Game Collection

### 1. Classic Tic-Tac-Toe (X-O) 📐
The timeless 3×3 grid classic. Simple, elegant, nostalgic!

### 2. SUS Game 🎯
Form the word "SUS" on the board. Among Us vibes included! 😄

### 3. Four-in-a-Row (Connect 4) 🔴🟡
The vertical 6×7 classic. Gravity-defying strategy! Features an **unbeatable AI**!

### 4. 5×5 Tic-Tac-Toe 📏
Bigger board, more possibilities, longer games! Get 3-in-a-row on a 5×5 grid.

### 5. Word Tic-Tac-Toe 📝
Form valid 3-letter words from a dictionary. For the linguistically gifted! 🎓

### 6. Misère Tic-Tac-Toe 🔄
Reverse psychology edition - **AVOID** getting 3-in-a-row to win!

### 7. Diamond Tic-Tac-Toe 💎
Win by forming both a 3-line AND a 4-line simultaneously. Mind-bending! 🤯

### 8. 4×4 Moving Tic-Tac-Toe ♟️
Chess meets Tic-Tac-Toe! Move your pieces strategically after placement.

### 9. Numerical Tic-Tac-Toe ➕
Odd vs Even numbers. Get three numbers that sum to **15**. Math nerds unite! 🤓

### 10. Obstacles Tic-Tac-Toe 🚧
Random obstacles appear every 2 moves. Adapt or perish!

### 11. Infinity Tic-Tac-Toe ♾️
Only your last 3 moves remain on the board. Memory challenge activated! 🧠

### 12. Ultimate Tic-Tac-Toe 🎯🎯
Meta-gaming: A 3×3 grid of 3×3 Tic-Tac-Toe boards. Inception vibes! 🌀

### 13. Memory Tic-Tac-Toe 🙈
Your moves are hidden! Play blind and trust your memory.

### 14. Pyramid Tic-Tac-Toe 🔺
Triangular board layout. Get 3-in-a-row on the pyramid!

## ✨ Features

- 🎮 **14 Unique Game Modes** - Never get bored!
- 🤖 **Smart AI Opponents** - Minimax with Alpha-Beta pruning
- 👥 **Multiplayer Support** - Human vs Human or Human vs AI
- 🎨 **Clean Console Interface** - Easy to navigate menu system
- 🏗️ **OOP Architecture** - Modular, extensible, maintainable
- 📚 **Dictionary Support** - For Word Tic-Tac-Toe (dic.txt included)
- 🧠 **Multiple Difficulty Levels** - Some games feature adjustable AI difficulty
- 🔄 **Move Validation** - No cheating allowed! 😤
- 🏆 **Win Detection** - Automatic game state evaluation

## 🚀 Installation

### Prerequisites
- C++17 compatible compiler (g++, clang++, MSVC)
- Standard C++ libraries

### Steps

1. **Clone the repository**
   ```bash
   git clone https://github.com/yourusername/Assignment-3-OOP.git
   cd Assignment-3-OOP
   ```

2. **Compile the project**
   ```bash
   g++ -std=c++17 main.cpp XO_Classes.cpp SUS_Board.cpp SUS_UI.cpp XO4R_Board.cpp XO4R_UI.cpp TTC5_Board.cpp TTC5_UI.cpp AIPlayer3.cpp WordTTT_Board.cpp WordTTT_UI.cpp WordTTT_SmartAI.cpp MisereTTT_Board.cpp DiamondTTT_Board.cpp DiamondTTT_UI.cpp FourByFourBoard.cpp FourByFourUI.cpp AIPlayer.cpp PyramidBoard.cpp PyramidUI.cpp NumTTT_Board.cpp NumTTT_UI.cpp ObstaclesBoard.cpp ObstaclesUI.cpp InfinityTTT_Board.cpp InfinityTTT_UI.cpp UltimateTTT_Board.cpp UltimateTTT_UI.cpp MemoryTTT_Board.cpp MemoryTTT_UI.cpp -o game_hub
   ```

3. **Run the game**
   ```bash
   ./game_hub
   ```

## 🎮 How to Play

1. **Launch the game** and you'll see the main menu
2. **Select a game** by entering the corresponding number (0-14)
3. **Enter player names** when prompted
4. **Choose player types**:
   - `1` for Human player 👤
   - `2` for Computer/AI player 🤖
5. **Follow the game-specific instructions**
6. **Make your moves** by entering coordinates when it's your turn
7. **Win, lose, or draw!** 🏆

### Example Gameplay
```
=============================
 FCAI Game Hub Menu 
=============================
0. Classic Tic-Tac-Toe (X-O)
1. SUS Game
...
14. Exit
=============================
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

[Game starts...]
```

## 🧠 AI Implementation

Our AI opponents use state-of-the-art game theory algorithms:

### Minimax Algorithm 🎯
- **Exhaustive search** of game tree
- **Optimal move selection** at each turn
- **Depth-limited** for performance optimization

### Alpha-Beta Pruning ✂️
- **Reduces computation** by eliminating branches
- **Faster decision making** without sacrificing accuracy
- **Dynamic evaluation** of board positions

### Game-Specific Heuristics 🎲
- **Position weighting** (center, corners, edges)
- **Pattern recognition** (potential wins/blocks)
- **Strategic move prioritization**

### AI Features by Game
| Game | AI Type | Difficulty |
|------|---------|-----------|
| Classic X-O | Random | Easy |
| SUS | Perfect Minimax | Unbeatable 🔥 |
| Connect 4 | Perfect Minimax | Unbeatable 🔥 |
| 5×5 TTT | Strategic Heuristic | Hard |
| Word TTT | Dictionary + Minimax | Hard |
| Misère | Reverse Logic | Hard |
| Diamond | Deep Search | Medium |
| 4×4 Moving | Position Eval | Medium |
| Pyramid | Minimax | Hard |

## 📁 Project Structure

```
Assignment-3-OOP/
├── 📄 main.cpp                      # Main menu and game launcher
├── 📚 BoardGame_Classes.h           # Base classes (Board, Player, UI, GameManager)
│
├── 🎮 Game Implementations/
│   ├── XO_Classes.{h,cpp}           # Classic Tic-Tac-Toe
│   ├── SUS_Classes.{h,cpp}          # SUS Game
│   ├── XO4R_Classes.{h,cpp}         # Four-in-a-Row
│   ├── TTC5_Board.{h,cpp}           # 5×5 Tic-Tac-Toe
│   ├── WordTTT_*.{h,cpp}            # Word Tic-Tac-Toe
│   ├── MisereTTT_*.{h,cpp}          # Misère variant
│   ├── DiamondTTT_*.{h,cpp}         # Diamond variant
│   ├── FourByFour*.{h,cpp}          # 4×4 Moving variant
│   ├── PyramidBoard.{h,cpp}         # Pyramid variant
│   ├── NumTTT_*.{h,cpp}             # Numerical variant
│   ├── ObstaclesBoard.{h,cpp}       # Obstacles variant
│   ├── InfinityTTT_*.{h,cpp}        # Infinity variant
│   ├── UltimateTTT_*.{h,cpp}        # Ultimate variant
│   └── MemoryTTT_*.{h,cpp}          # Memory variant
│
├── 🤖 AI Implementations/
│   ├── AIPlayer.{h,cpp}             # 4×4 Moving AI
│   ├── AIPlayer3.{h,cpp}            # 5×5 TTT AI
│   └── WordTTT_SmartAI.{h,cpp}      # Word TTT AI
│
├── 📖 dic.txt                       # Dictionary for Word Tic-Tac-Toe
├── 📝 README.md                     # This file!
└── 📜 LICENSE                       # MIT License
```

## 🛠️ Technologies Used

- **Language**: C++17 🔷
- **Paradigm**: Object-Oriented Programming (OOP)
- **Design Patterns**: 
  - Template Method Pattern
  - Strategy Pattern
  - Factory Pattern
- **Algorithms**:
  - Minimax Algorithm
  - Alpha-Beta Pruning
  - Depth-First Search
  - Heuristic Evaluation Functions
- **Data Structures**:
  - 2D Vectors (Board representation)
  - Hash Sets (Dictionary lookup)
  - Dynamic Arrays

## 🎨 Design Highlights

### Base Class Architecture
```cpp
Board<T>       → Game-specific boards
Player<T>      → Human/AI players
UI<T>          → User interface handlers
GameManager<T> → Game loop controller
```

### Polymorphism in Action 🎭
- Virtual functions for game rules
- Template classes for flexibility
- Dynamic dispatch for AI behavior

## 🤝 Contributing

Contributions are welcome! 🎉

1. **Fork the repository**
2. **Create a feature branch** (`git checkout -b feature/AmazingGame`)
3. **Commit your changes** (`git commit -m 'Add SuperTicTacToe'`)
4. **Push to the branch** (`git push origin feature/AmazingGame`)
5. **Open a Pull Request**

### Ideas for Contribution
- 🎮 Add new game variants
- 🤖 Improve AI algorithms
- 🎨 Add GUI using SFML/SDL
- 🌐 Implement network multiplayer
- 📊 Add game statistics tracking
- 🎵 Add sound effects

## 🐛 Known Issues

- Some AI computations may take time on first move (complexity is high!)
- Console clearing may not work on all terminals
- Memory game doesn't persist across sessions

## 📝 License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

Free to use, modify, and distribute! Just give credit where it's due. 😊

## 👥 Credits

**Project by**: Abdallah Ahmed  
**Institution**: FCAI (Faculty of Computers and Artificial Intelligence)  
**Inspired by**: Dr. El-Ramly's teachings 🎓

### Special Thanks
- 🙏 Coffee for keeping me awake during debugging sessions
- 🎮 All the classic board game designers
- 🤖 The AI/ML community for algorithm inspiration
- 💻 Stack Overflow (the real MVP)

## 📞 Contact

Have questions, suggestions, or just want to chat about game AI? 

- 📧 Email: [your.email@example.com](mailto:your.email@example.com)
- 🐙 GitHub: [@yourusername](https://github.com/yourusername)
- 💬 Open an issue on this repo!

---

<div align="center">

### 🎮 Ready to Play? Let's Go! 🚀

**Star ⭐ this repo if you enjoyed the games!**

Made with ❤️ and lots of ☕

*"The only winning move is to play!"* 🎯

</div>

---

## 🏆 Game Statistics

| Metric | Value |
|--------|-------|
| Total Games | 14 🎮 |
| Lines of Code | ~4000+ 💻 |
| AI Algorithms | 6 🤖 |
| Coffee Consumed | ∞ ☕ |
| Fun Level | Over 9000! 🚀 |

## 🎓 Learning Outcomes

By exploring this project, you'll learn:
- ✅ Advanced C++ and OOP concepts
- ✅ Game tree algorithms (Minimax, Alpha-Beta)
- ✅ Template programming
- ✅ Design patterns in action
- ✅ Code organization and modularity
- ✅ How to build unbeatable AI (Skynet, here we come! 🤖)

---

**Happy Gaming! May the best strategy win! 🎊**
