# Snake Game in C 

A classic Snake game implemented in C, using pointers, linked lists for the snake body, and the `ncurses` library for terminal graphics.

---

## Features

- **Dynamic Snake Body:** Managed as a singly linked list.
- **Real-time Controls:** Arrow keys for movement (using ncurses).
- **Random Food Placement:** Food never appears on the snake.
- **Collision Detection:** Game ends on wall or self-collision.
- **Score Display:** Score shown during gameplay and at game over.
- **Replay Option:** Play multiple rounds without restarting.
- **Adjustable Difficulty:** Choose from four speed levels (Beginner, Classic, Expert, Insane).

---

## Requirements

- **C Compiler:** (e.g., gcc)
- **ncurses Library:** Install via package manager (Linux/Unix)


---

## Controls

- **Arrow Keys:** Move the snake
- **q:** Quit game
- **y/n:** Play again after game over

---

## Gameplay

- Instruction page, followed by level selection.
- Eat food (`*`) to grow and increase your score.
- Avoid colliding with the walls (`#`) or yourself.
- Score is displayed at the top.

---

## Code Structure

- **Data Structures:**
    - `Position`: Holds (x, y) coordinates.
    - `snake_node`: Linked list node for each snake segment.
- **Major Functions:**
    - `food_pos(head)`: Places food at a valid, random location.
    - `gameBox(head, food)`: Draws the game area, snake, and food.
    - `addNode(x, y)`: Adds a new segment to the snake.
    - `addHead(head, direction)`: Moves the snake's head.
    - `ateFood(head, food)`: Checks if food is eaten.
    - `checkCollision(head)`: Detects wall/self collision.
    - `removeTail(head)`: Removes the last segment if food not eaten.

---

##  MIT License
---

Enjoy the game! 🐍




