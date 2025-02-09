#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h> // For usleep()
#include <termios.h>
#include <fcntl.h>

using namespace std;

const int BOARD_SIZE = 10; // NxN grid

// Function to check if a key is pressed (non-blocking)
int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

// Function to get a single character from the keyboard
char getch() {
    struct termios oldt, newt;
    char ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}

class GameBoard {
public:
    char board[BOARD_SIZE][BOARD_SIZE];

    void initializeBoard() {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                board[i][j] = '.'; // Empty cell
            }
        }
    }

    void displayBoard() {
        cout << "\033[2J\033[1;1H"; // Clear the screen and move cursor to the top-left
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                cout << board[i][j];
            }
            cout << endl;
        }
    }
};

class Snake {
public:
    vector<pair<int, int>> body;
    pair<int, int> direction;

    Snake(int startX, int startY) {
        body.push_back({startX, startY});
        body.push_back({startX - 1, startY});
        body.push_back({startX - 2, startY});
        direction = {1, 0}; // Initially moving right
    }

    void move() {
        pair<int, int> newHead = {body[0].first + direction.first, body[0].second + direction.second};
        body.insert(body.begin(), newHead); // Add new head
    }

    void shrink() {
        body.pop_back(); // Remove the tail
    }

    void setDirection(pair<int, int> newDirection) {
        if (newDirection.first + direction.first != 0 || newDirection.second + direction.second != 0) {
            direction = newDirection; // Prevent reversing
        }
    }
};

class Food {
public:
    pair<int, int> position;

    void placeFood(vector<pair<int, int>> &snakeBody) {
        while (true) {
            position = {rand() % BOARD_SIZE, rand() % BOARD_SIZE};
            bool isOnSnake = false;
            for (auto &segment : snakeBody) {
                if (segment == position) {
                    isOnSnake = true;
                    break;
                }
            }
            if (!isOnSnake) break; // Ensure food is not placed on the snake
        }
    }
};

void updateBoard(GameBoard &gameBoard, Snake &snake, Food &food) {
    gameBoard.initializeBoard();

    // Place the snake on the board
    for (auto &segment : snake.body) {
        gameBoard.board[segment.second][segment.first] = 'O';
    }

    // Place the food on the board
    gameBoard.board[food.position.second][food.position.first] = 'X';
}

bool isCollision(Snake &snake) {
    pair<int, int> head = snake.body[0];

    // Check collision with walls
    if (head.first < 0 || head.second < 0 || head.first >= BOARD_SIZE || head.second >= BOARD_SIZE) {
        return true;
    }

    // Check collision with itself
    for (size_t i = 1; i < snake.body.size(); i++) {
        if (snake.body[i] == head) {
            return true;
        }
    }

    return false;
}

int main() {
    srand(time(0));

    while (true) {
        // Initialize game components
        GameBoard gameBoard;
        Snake snake(3, 5);
        Food food;
        food.placeFood(snake.body);
        int score = 0;
        char input;

        while (true) {
            // Update the board with the snake and food positions
            updateBoard(gameBoard, snake, food);

            // Display the board
            gameBoard.displayBoard();
            cout << "Score: " << score << endl;
            cout << "Controls: W (Up), A (Left), S (Down), D (Right)" << endl;
            cout << "Press 'Q' to quit" << endl;

            // Handle input for direction
            if (kbhit()) {
                input = getch();
                switch (toupper(input)) {
                    case 'W': snake.setDirection({0, -1}); break; // Up
                    case 'A': snake.setDirection({-1, 0}); break; // Left
                    case 'S': snake.setDirection({0, 1}); break; // Down
                    case 'D': snake.setDirection({1, 0}); break; // Right
                    case 'Q': cout << "Game Over! Final Score: " << score << endl; return 0; // Quit
                }
            }

            // Move the snake
            snake.move();

            // Check for collisions
            if (isCollision(snake)) {
                cout << "Game Over!" << endl;
                cout << "Final Score: " << score << endl;
                break;
            }

            // Check if the snake eats the food
            if (snake.body[0] == food.position) {
                score++;
                food.placeFood(snake.body);
            } else {
                snake.shrink(); // Remove the tail if no food is eaten
            }

            usleep(200000); // Delay to control game speed
        }

        // Restart or quit
        cout << "Press 'R' to restart or any other key to exit: ";
        char restartInput;
        cin >> restartInput;
        if (toupper(restartInput) != 'R') {
            cout << "Thanks for playing!" << endl;
            break;
        }
    }

    return 0;
}
