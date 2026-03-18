# 🎮 Tetris Engine in C (raylib)

A real-time Tetris implementation built in C using raylib, designed to demonstrate **grid-based game architecture, deterministic logic, and low-level system control**.

![Gameplay](assets/preview.png)

---

## 🚀 Overview

This project recreates the classic Tetris experience while focusing on **how the system works internally**, not just the gameplay.

It emphasizes:

* Structured game loop design
* Memory-efficient grid representation
* Modular separation of logic and rendering

> Built to move beyond tutorial-level code into **system-oriented thinking**.

---

## 🧠 Core Systems

### 🧱 Grid Engine

* 2D matrix representing board state
* Handles occupancy, validation, and line clearing
* Efficient row shifting after clears

### 🔷 Tetromino Model

* Pieces defined using relative coordinate offsets
* Each shape contains multiple rotation states

### 🔄 Rotation System

* Rotation implemented via indexed state transitions
* Validated before applying to prevent illegal placement

### 💥 Collision Detection

* Boundary + block collision checks
* Ensures safe movement and rotation

### 🧹 Line Clearing Logic

* Detects complete rows
* Shifts grid downward dynamically
* Updates score in real time

---

## 🎮 Controls

| Key       | Action                  |
| --------- | ----------------------- |
| ← → / A D | Move left / right       |
| ↑ / W     | Rotate piece            |
| ↓ / S     | Soft drop               |
| R         | Restart after game over |

---

## 🎯 Scoring System

| Lines Cleared | Points |
| ------------- | ------ |
| 1 line        | 100    |
| 2 lines       | 200    |
| 3 lines       | 300    |
| 4 lines       | 400    |

---

## 🛠️ Build Instructions

### Requirements

* GCC
* raylib

### Compile

```bash
gcc *.c -o tetris.exe -I../raylib/include -L../raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm -static
```

---

## 📁 Project Architecture

```
src/
├── main.c        # Game loop, input handling
├── grid.c/h      # Board state, collision, line clearing
├── block.c/h     # Tetromino logic, rotation system
├── tiles.c/h     # Shape definitions
├── color.c/h     # Rendering utilities
└── common.h      # Shared constants & types
```

---

## 🔍 Design Highlights

* Separation of concerns between game logic and rendering
* Deterministic update loop (predictable behavior)
* Scalable structure for adding new mechanics
* Clean modular C design (no unnecessary coupling)

---

## 🧠 Key Learnings

* Building a **grid-based engine from scratch in C**
* Implementing rotation systems using state transformations
* Designing collision detection for discrete environments
* Managing real-time input and frame updates
* Structuring multi-file C projects cleanly

---

## 🚧 Future Improvements

* Wall kick system (advanced rotation handling)
* Next piece preview
* Hold piece mechanic
* Difficulty scaling (speed increase)
* UI/UX improvements

---

## ⬇️ Download & Play

1. Go to Releases
2. Download `tetris.zip`
3. Extract and run `tetris.exe`

> Windows only. No installation required.

---

## 👤 Author

**Zahin Bin Hasan**

---

## 🙏 Credits

Inspired by a tutorial, but extended with improved structure, modular design, and custom game logic implementation.
