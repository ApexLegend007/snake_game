# Snake Game (Terminal-Based)

This repository contains a terminal-based implementation of the classic Snake Game written in C++. It adheres to the following requirements:
- No GUI or external libraries (e.g., `conio.h`), making it compatible with Linux and Windows-Subsystem-Linux environments.
- Implements real-time input handling using `termios.h`.
- Uses basic programming constructs such as classes, arrays, and standard I/O.

---

## Game Features

1. **Grid-Based Board**:
   - A 10x10 grid acts as the play area.

2. **Snake Movement**:
   - The snake moves continuously in the current direction.
   - Players can control the snake using the following keys:
     - `W`: Move up
     - `A`: Move left
     - `S`: Move down
     - `D`: Move right

3. **Food**:
   - The snake grows when it eats food placed randomly on the board.

4. **Game Over**:
   - The game ends when the snake collides with itself or the boundary of the grid.

5. **Score Display**:
   - The score updates dynamically during the game.
   - The final score is displayed upon game over.

---

## Repository Structure

```
snake-game-terminal
├── README.md           # Documentation for the project
├── snake_game.cpp      # Main source code of the game
├── snake_game          # Binary File (Executable Game) 
├── LICENSE             # Open-source license (e.g., MIT License)
├── screenshots/        # Screenshots of the game running in the terminal
│   ├── screenshot_1.png
│   ├── Screenshot_2.png
│   ├── Screenshot_3.png
│   ├── Screenshot_4.png  
```

---

## How to Run the Game

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/ApexLegend007/snake_game.git
   cd snake_game
   ```

2. **Compile the Code**:
   ```bash
   g++ -o snake_game snake_game.cpp
   ```

3. **Run the Game**:
   ```bash
   ./snake_game
   ```

4. **Controls**:
   Use `W`, `A`, `S`, `D` keys to move the snake.

---

## Data Structure Analysis

### Objects and Responsibilities

#### 1. **GameBoard**:
- **Role**: Represents the grid.
- **Responsibilities**:
  - Initializes and resets the board.
  - Displays the current state of the game.
- **Data Structures**:
  - A 2D array (`char board[BOARD_SIZE][BOARD_SIZE]`) is used to represent the grid.

#### 2. **Snake**:
- **Role**: Manages the snake's body and movement.
- **Responsibilities**:
  - Tracks the snake's position using a vector of coordinate pairs.
  - Updates the snake's body for movement, growth, and shrinking.
  - Handles direction changes while preventing reversal.
- **Data Structures**:
  - **Vector of pairs (`vector<pair<int, int>>`)**:
    - Represents the snake's body as a series of (x, y) coordinates.
    - Efficiently supports insertion (for movement) and deletion (for shrinking).

#### 3. **Food**:
- **Role**: Places food randomly on the board.
- **Responsibilities**:
  - Ensures food does not overlap with the snake's body.
- **Data Structures**:
  - **Pair (`pair<int, int>`)**:
    - Represents the position of the food.

---

### Key Algorithms

1. **Snake Movement**:
   - Insert the new head position at the front of the vector.
   - Remove the tail unless food is eaten.
   - **Efficiency**: `O(1)` for insertion and deletion.

2. **Collision Detection**:
   - Wall Collision: Check if the head's position is out of bounds.
   - Self Collision: Linear scan (`O(n)`) through the snake's body (excluding the head).

3. **Food Placement**:
   - Randomly generates food coordinates.
   - Ensures the food does not overlap with the snake's body using a linear scan (`O(n)`).

4. **Game Over Condition**:
   - The game ends when the snake collides with the boundary or itself.
   - The final score is displayed upon game over.

5. **Score Tracking**:
   - Score increases with each piece of food consumed.
   - Displayed dynamically on the screen.

6. **Restart and Exit Option**:
   - Upon game over, provide an option to restart the game or exit.

---

## Future Enhancements

1. **Dynamic Grid Sizes**:
   - Allow the player to choose the grid size at the start of the game.

2. **Obstacles**:
   - Add fixed or randomly placed obstacles on the grid.
   - Make the game more challenging by avoiding collisions with obstacles.

3. **Levels**:
   - Increase difficulty as the player progresses.
   - Introduce higher speeds or additional challenges at each level.

4. **High Scores**:
   - Maintain a leaderboard for the highest scores.

5. **Special Food**:
   - Add power-ups or special food that gives bonuses or penalties.
---

## License
This project is open-source and available under the MIT License.

---

