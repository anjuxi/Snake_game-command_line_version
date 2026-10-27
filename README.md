# Snake (Command-Line Version)

A classic Snake game written in C for the Windows console.

![C](https://img.shields.io/badge/language-C-blue.svg)
![Platform](https://img.shields.io/badge/platform-Windows-green.svg)
![License](https://img.shields.io/badge/license-MIT-yellow.svg)

## About

A console Snake game in C with the full game loop and a few extras: two control schemes, a temporary speed boost, persistent high scores, and adjustable base speed.

## Features

- Classic Snake gameplay
- Arrow keys or WASD
- Hold a direction key for a temporary 2× speed boost
- Live score and high score (saved to a file)
- Adjustable base speed with `+` / `-`
- Pause/resume with `P`
- Game-over screen
- Colored console output
- Prevents the snake from reversing directly into itself

## Rules

1. Use the arrow keys or WASD to steer the snake.
2. Eating a ★ grows the snake and adds 10 points.
3. Hitting a wall or your own body ends the game.
4. Hold a direction key to move faster temporarily.
5. Press `P` to pause; press any key to resume.
6. Press `+` to speed up the base speed, `-` to slow it down.
7. Press `X` to quit.

## Controls

| Key | Action |
| ----------- | ----------------- |
| ↑↓←→ / WASD | Steer the snake |
| Hold a direction key | Temporary 2× speed |
| P | Pause/resume |
| + / = | Increase base speed |
| - / _ | Decrease base speed |
| X | Quit |

## Build and Run

### Build

Use a C compiler that supports the Windows API (MinGW or MSVC):

```bash
gcc 贪吃蛇（命令行版）.c -o snake.exe -lmsvcrt
```

### Run

```bash
snake.exe
```

Or double-click `a.exe` (a prebuilt binary).

## Files

- `贪吃蛇（命令行版）.c` — main source
- `snake_highscore.txt` — high-score file
- `a.exe` — prebuilt executable

## Implementation

- Language: C
- Window control: Windows API
- Interface: console output
- Persistence: file read/write for the high score

## Development Notes

The source has detailed comments in Chinese and is meant partly as a learning reference. It is organized as:

1. Includes — standard library and Windows API
2. Constants — game parameters
3. Data structures — snake, food, game state
4. Function declarations
5. `main` — game loop
6. Function implementations

## Author

**Dr. Ailan Anjuxi (谙弆悕)**

- Email: `anjuxi.ME@outlook.com`
- SIP: `sip:anjuxi@sip.linphone.org`

---

© 2026 Ailan Anjuxi. All rights reserved.
