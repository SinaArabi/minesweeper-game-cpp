# Minesweeper (Console C++)

A console-based clone of the classic **Minesweeper** game, written in C++ with a colorful text UI using [`clui`](https://github.com/SBU-CE/clui).  
This project was developed as a programming mini-project and includes random bomb placement, flagging, multiple difficulty levels, save/load support, and a leaderboard system.

---

## 🎮 Features
- Random bomb placement every game  
- Colored text-based user interface (CLUI)  
- Multiple difficulty levels (Easy, Casual, Hard, Custom)  
- Save and load game from 4 slots  
- Flagging system to mark suspected mines  
- Leaderboard stored in text files (sorted by score)  
- Player name management (new or returning users)  
- Auto expansion when a zero-cell is revealed  
- Keyboard controls with arrow keys and ESC to exit  

---

## 🛠 Requirements
- **C++ Compiler** supporting C++11 or later (e.g., g++, clang, MSVC)  
- **Windows/Linux terminal** (tested in Windows with `conio.h`)  
- [`clui.h`](https://github.com/SBU-CE/clui) header for console UI utilities  

---

## 🚀 Build & Run
Clone this repository:
```bash
git clone https://github.com/your-username/minesweeper-game-cpp.git
cd minesweeper-game-cpp
```

Compile (example with g++):
```bash
g++ main.cpp -o minesweeper
```

Run:
```bash
./minesweeper
```

---

## 🎯 Controls
- **Arrow keys** → move cursor  
- **Enter** → select a cell  
- **S** → select a cell (reveal)  
- **F** → place or remove a flag  
- **O** → save and quit  
- **ESC** → quit game immediately  

---

## 📂 Project Structure
```
├── main.cpp                # Game source code
├── clui.h                  # Console UI library (external dependency)
├── leaderboard_Names.txt   # Stored leaderboard names
├── leaderboard_Scores.txt  # Stored leaderboard scores
├── SlotX_main.txt          # Saved maps (X = 1..4)
├── SlotX_user.txt          # Saved user maps (X = 1..4)
└── README.md               # Project documentation
```

---

## 📝 License
This project is for educational purposes. You are free to use and modify it.  
