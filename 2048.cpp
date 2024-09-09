#include<bits/stdc++.h>

using namespace std;

class Game2048 {
private:
    int size;            // size of the grid
    int total;
    vector<vector<int>> grid;

public:
    // Constructor to initialize grid size and target
    Game2048(int size = 4, int total = 2048) : size(size), total(total) {
        grid = createNewGrid();    // Initialize the grid
        addNew();                  // To add some default (2) values to start the game
        addNew();                  // adding two 2's 
    }

    // intialise the grid with 0's.which indicate empty spaces. 
    vector<vector<int>> createNewGrid(bool empty = false) {
        vector<vector<int>> newGrid(size, vector<int>(size, 0));
        return newGrid;
    }

    // Add a new value (2) to a random empty spot in the grid
    void addNew() {
        bool added = false;
        while (!added) {
            int row = rand() % size;
            int col = rand() % size;
            if (grid[row][col] == 0) {
                grid[row][col] = 2;
                added = true;
            }
        }
    }

    // Shift all values in the grid to the left
    vector<vector<int>> moveLeft() {
        vector<vector<int>> newGrid = createNewGrid();
        for (int i = 0; i < size; ++i) {
            int count = 0;
            for (int j = 0; j < size; ++j) {
                if (grid[i][j] != 0) {
                    newGrid[i][count] = grid[i][j];
                    count++;
                }
            }
        }
        return newGrid;
    }

    // Reverse the grid (used for right or down movement)
    vector<vector<int>> reverse() {
        vector<vector<int>> newGrid(size, vector<int>());
        for (int i = 0; i < size; ++i) {
            for (int j = size - 1; j >= 0; --j) {
                newGrid[i].push_back(grid[i][j]);
            }
        }
        return newGrid;
    }

    // Transpose the grid (used for up and down movement)
    vector<vector<int>> transpose() {
        vector<vector<int>> newGrid(size, vector<int>());
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                newGrid[i].push_back(grid[j][i]);
            }
        }
        return newGrid;
    }

    // Double adjacent values that are the same
    void addValues() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size - 1; ++j) {
                if (grid[i][j] == grid[i][j + 1]) {
                    grid[i][j] *= 2;
                    grid[i][j + 1] = 0;
                }
            }
        }
    }

    // Check if there's any empty spot left in the grid
    bool isAnyEmpty() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (grid[i][j] == 0) return true;
            }
        }
        return false;
    }

    // Check for game over condition (no more moves left)
    bool isGameOver() {
        if (isAnyEmpty()) return false;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size - 1; ++j) {
                if (grid[i][j] == grid[i][j + 1]) return false;
            }
        }
        return true;
    }

    // Check if the player has won the game
    bool winCheck() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (grid[i][j] == total) return true;
            }
        }
        return false;
    }

    // Display the current grid
    void displayGrid() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                cout << grid[i][j] << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }

    // To Move the grid in the left direction
    void Left() {
        grid = moveLeft();
        addValues();
        grid = moveLeft();
        addNew();
    }

    // To Move the grid in the right direction
    void Right() {
        grid = reverse();
        grid = moveLeft();
        addValues();
        grid = moveLeft();
        grid = reverse();
        addNew();
    }

    // To Move the grid up
    void Up() {
        grid = transpose();
        grid = moveLeft();
        addValues();
        grid = moveLeft();
        grid = transpose();
        addNew();
    }

    // To Move the grid down
    void Down() {
        grid = transpose();
        grid = reverse();
        grid = moveLeft();
        addValues();
        grid = moveLeft();
        grid = reverse();
        grid = transpose();
        addNew();
    }

    // Start the game loop
    void startGame() {
        char command;
        bool play = true;
        cout << "\nInstructions:\n"
             << "Use 'a' to move left\n"
             << "Use 'd' to move right\n"
             << "Use 'w' to move up\n"
             << "Use 's' to move down\n"
             << "Reach 2048 to win the game\n";

        while (play) {
            displayGrid();
            cout << "Enter command: ";
            cin >> command;

            switch (command) {
                case 'a':
                    Left();
                    break;
                case 'd':
                    Right();
                    break;
                case 'w':
                    Up();
                    break;
                case 's':
                    Down();
                    break;
                default:
                    cout << "Invalid input!" << endl;
            }

            if (winCheck()) {
                displayGrid();
                cout << "You win!" << endl;
                play = false;
            } else if (isGameOver()) {
                displayGrid();
                cout << "Game over!" << endl;
                play = false;
            }
        }
    }
};

// Main function to start the game
int main() {
    srand(time(0));
    Game2048 game;
    game.startGame();
    return 0;
}
