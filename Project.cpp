/* #region Includes */
#include<iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
/* #endregion */

/* #region Globals */
/**
 * The width of the board.
 */
const int WIDTH = 50;

/**
 * The height of the board.
 */
const int HEIGHT = 50;

/**
 * The total number of cells on the board.
 */
const int TOTAL_CELLS = WIDTH * HEIGHT;

/**
 * The maximum number of years to simulate.
 */
const int MAX_YEARS = 100;

/**
 * The maximum number of years the board can be stagnant before the game ends.
 */
const int MAX_STAGNANT_YEARS = 20;
/* #endregion */

/* #region Enums */
/**
 * The state of the game of life.
 */
enum GameOfLifeState {
    /**
     * The game is still running.
     */
    RUNNING,
    /**
     * The game has stagnated.
     */
    STAGNATED,
    /**
     * All cells are dead.
     */
    ALL_DEAD,
    /**
     * The maximum number of years has been reached.
     */
    MAX_YEARS_REACHED
};
/* #endregion */

/* #region Function Declarations */
/**
 * Clears the screen, using ANSI escape codes.
 */
void clearScreen();

/**
 * Pauses the program until the user presses Return.
 */
void pause();

/**
 * Initializes the board to all dead cells.
 * @param board The board to initialize.
 */
void initializeBoard(bool board[WIDTH][HEIGHT]);

/**
 * Simulates the Game of Life for a single year.
 * @param board The board to simulate.
 * @param lastBoard The board from the previous year.
 * @param years The current year.
 * @param stagnantYears The number of years the board has been stagnant.
 * @param interactive Whether to display the board after each year.
 */
void simulate(bool board[WIDTH][HEIGHT], bool lastBoard[WIDTH][HEIGHT], int& years, int& stagnantYears, bool interactive);

void csvParse(string fileName, int gridX, int gridY);

/**
 * Simulates a single year of the Game of Life.
 * @param board The board to simulate.
 * @param lastBoard The board from the previous year.
 * @param years The current year.
 * @param stagnantYears The number of years the board has been stagnant.
 */
void simulateYear(bool board[WIDTH][HEIGHT], bool lastBoard[WIDTH][HEIGHT], int& years, int& stagnantYears);

/**
 * Clears the input, setting the board to all dead cells and the current year to 0.
 * @param board The board to clear.
 * @param years The current year.
 */
void clearInput(bool board[WIDTH][HEIGHT], int& years);

/**
 * Draws the board to the console.
 * @param board The board to draw.
 */
void drawBoard(bool board[WIDTH][HEIGHT]);

/**
 * Copies the contents of one board to another.
 * @param from The board to copy from.
 * @param to The board to copy to.
 */
void copyBoard(bool from[WIDTH][HEIGHT], bool to[WIDTH][HEIGHT]);\

/**
 * Checks if the board is empty.
 * @param board The board to check.
 * @return Whether the board is empty.
 */
bool isBoardEmpty(bool board[WIDTH][HEIGHT]);

/**
 * Checks if the board has changed from the previous year.
 * @param board The board to check.
 * @param lastBoard The board from the previous year.
 * @return Whether the board has changed.
 */
bool boardChanged(bool board[WIDTH][HEIGHT], bool lastBoard[WIDTH][HEIGHT]);

/**
 * Counts the number of alive cells on the board.
 * @param board The board to check.
 * @return The number of alive cells.
 */
int aliveCells(bool board[WIDTH][HEIGHT]);

/**
 * Displays the state of the game of life.
 * Used for interactive mode.
 * @param board The board to display.
 * @param years The current year.
 * @param stagnantYears The number of years the board has been stagnant.
 * @param state The state of the game of life.
 */
void displayState(bool board[WIDTH][HEIGHT], int years, int stagnantYears, GameOfLifeState state);


/**
 * Detects the current state of the game of life.
 * @param board The board to check.
 * @param years The current year.
 * @param stagnantYears The number of years the board has been stagnant.
 * @return The state of the game of life.
 */
GameOfLifeState detectState(bool board[WIDTH][HEIGHT], int years, int stagnantYears);
/* #endregion */

/* #region Main */
/*
1. Clear input (set the game of life to every cell being dead, set the current year to 0, display the new state to confirm)
2. Set state (prompt the user for a csv file, then load and store it in memory. Set the current year to 0, display the new state to confirm)
3. Play the game of life (using the current state, play the game of life until it halts,
    displaying the state of the game after each year, and displaying a report how many
    cells are alive/dead at the end and how many years it was played for).
4. Report summary statistics (output a report of, on average, how many cells survive the game of life, and how many years it takes, for every game played so far, including random play)
5. Random play (play the game many times, with random board states, these do not need to display the board state on every year)
    a. Prompt the user to input a number of times to play the game
    b. Prompt the user for a probability any given cell is alive (e.g. 0.5 to say that each cell has a 50/50 shot to start as alive)
    c. Play the game of life to completion as many times as told, using a random initial state each time.
6. Output histogram - create an output file named results_histogram.txt) that stores a histogram of how many years each game played so far has taken. A histogram is a bar chart that shows how many times a particular data item has occurred. Below is
*/
int main() {
    // Controls whether the game is still active
    bool gameActive = true;

    // The current state of the game of life
    bool board[WIDTH][HEIGHT];

    // The board from the previous year (used to detect when the board is stagnant)
    bool lastBoard[WIDTH][HEIGHT];

    // Initialize the boards
    initializeBoard(board);
    initializeBoard(lastBoard);

    // The current year
    int years = 0;
    // The number of years the board has been stagnant
    int stagnantYears = 0;
    // The user's choice from the menu
    int choice;

    // Main game loop
    while (gameActive) {
        // Display the menu
        clearScreen();
        cout << endl
            << "    Game of Life Simulator" << endl
            << endl
            << "  Options:" << endl
            << "    1. Clear input" << endl
            << "    2. Set state from CSV file" << endl
            << "    3. Play the Game of Life" << endl
            << "    4. Report summary statistics" << endl
            << "    5. Random Play" << endl
            << "    6. Output histogram" << endl
            << "    7. Quit" << endl
            << endl;

        // Input loop
        while (true) {
            // Prompt the user
            cout << "  Enter your choice: " << flush;
            
            // Input handling
            cin >> choice;
            cout << endl;

            // Handle the user's choice
            if (choice == 1) {
                // 1. Clear input
                clearInput(board, years);
                break;
            } else if (choice == 2) {
                // 2. Set state from CSV file
                cout << "  Setting state from CSV file..." << endl;
                break;
            } else if (choice == 3) {
                // 3. Play the Game of Life
                simulate(board, lastBoard, years, stagnantYears, true);
                break;
            } else if (choice == 4) {
                // 4. Report summary statistics
                cout << "  Reporting summary statistics..." << endl;
                break;
            } else if (choice == 5) {
                // 5. Random play
                cout << "  Random play..." << endl;
                break;
            } else if (choice == 6) {
                // 6. Output histogram
                cout << "  Outputting histogram..." << endl;
                break;
            } else if (choice == 7) {
                // 7. Quit
                gameActive = false;
                cout << endl << "Thanks for playing!" << endl;
                break;
            } else {
                // Invalid choice
                cout << "  Invalid choice. Please try again." << endl;
            }
        }
    }
    
    return 0;
}
/* #endregion */

/* #region Function Definitions */
/**
 * Clears the screen, using ANSI escape codes.
 * https://stackoverflow.com/questions/4062045/clearing-terminal-in-linux-with-c-code
 */
void clearScreen() {
    cout << "\033[2J\033[1;1H" << flush;
}

/**
 * Pauses the program until the user presses Return.
 */
void pause() {
    cout << "Press RETURN to continue..." << flush;
    cin.ignore();
    cin.get();
}

/**
 * Initializes the board to all dead cells.
 * @param board The board to initialize.
 */
void initializeBoard(bool board[WIDTH][HEIGHT]) {
    // Set all cells to dead
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            board[x][y] = false;
        }
    }
}

/**
 * Copies the contents of one board to another.
 * @param from The board to copy from.
 * @param to The board to copy to.
 */
void copyBoard(bool from[WIDTH][HEIGHT], bool to[WIDTH][HEIGHT]) {
    // Copy each cell from the first board to the second
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            to[x][y] = from[x][y];
        }
    }
}

/**
 * Clears the input, setting the board to all dead cells and the current year to 0.
 * @param board The board to clear.
 * @param years The current year.
 */
void clearInput(bool board[WIDTH][HEIGHT], int& years) {
    initializeBoard(board);
    years = 0;

    clearScreen();
    cout << "  Input cleared." << endl;
    drawBoard(board);
    cout << "  Current year: " << years << endl;
    pause();
}

/**
 * Draws the board to the console.
 * @param board The board to draw.
 */
void drawBoard(bool board[WIDTH][HEIGHT]) {
    // Pattern:
    // +---+
    // |   |
    // | % |
    // |   |
    // +---+

    cout << "+" << string(WIDTH, '-') << "+" << endl;
    for (int y = 0; y < HEIGHT; y++) {
        cout << "|";

        for (int x = 0; x < WIDTH; x++) {
            if (board[x][y]) {
                cout << "%";
            }
            else {
                cout << " ";
            }
        }
        cout << "|" << endl;
    }
    cout << "+" << string(WIDTH, '-') << "+" << endl;   
}

/**
 * Displays the state of the game of life.
 * Used for interactive mode.
 * @param board The board to display.
 * @param years The current year.
 * @param stagnantYears The number of years the board has been stagnant.
 * @param state The state of the game of life.
 */
void displayState(bool board[WIDTH][HEIGHT], int years, int stagnantYears, GameOfLifeState state) {
    clearScreen();
    drawBoard(board);
    switch (state) {
        case RUNNING:
            cout << "  Current year: " << years << endl;
            break;
        case STAGNATED:
            cout << "  Game ended after " << years << " years." << endl
                << "    (Game stagnated for " << stagnantYears << " years.)" << endl;
            break;
        case ALL_DEAD:
            cout << "  Game ended after " << years << " years." << endl
                << "    (All cells are dead.)" << endl;
            break;
        case MAX_YEARS_REACHED:
            cout << "  Game ended after " << years << " years." << endl
                << "    (Maximum number of years reached.)" << endl;
            break;
    }
    cout << endl;
    pause();
}

/**
 * Detects the current state of the game of life.
 * @param board The board to check.
 * @param years The current year.
 * @param stagnantYears The number of years the board has been stagnant.
 * @return The state of the game of life.
 */
GameOfLifeState detectState(bool board[WIDTH][HEIGHT], int years, int stagnantYears) {
    if (isBoardEmpty(board)) { // Check if the board is empty
        return ALL_DEAD;
    } else if (stagnantYears >= MAX_STAGNANT_YEARS) { // Check if the board is stagnant for too long
        return STAGNATED;
    } else if (years >= MAX_YEARS) { // Check if the maximum number of years has been reached
        return MAX_YEARS_REACHED;
    }
    return RUNNING; // Otherwise, the game is still running
}

/**
 * Simulates the Game of Life for a single year.
 * @param board The board to simulate.
 * @param lastBoard The board from the previous year.
 * @param years The current year.
 * @param stagnantYears The number of years the board has been stagnant.
 * @param interactive Whether to display the board after each year.
 */
void simulate(bool board[WIDTH][HEIGHT], bool lastBoard[WIDTH][HEIGHT], int& years, int& stagnantYears, bool interactive) {
    // Detect the initial state of the game
    GameOfLifeState state = detectState(board, years, stagnantYears);

    // Display the last state, if interactive mode is enabled and the game is already over
    if (interactive && state != RUNNING) {
        displayState(board, years, stagnantYears, state);
        return;
    }

    // Simulate the game until it halts
    while (state == RUNNING) {
        // Simulate a single year
        simulateYear(board, lastBoard, years, stagnantYears);
        // Detect the new state
        state = detectState(board, years, stagnantYears);
        // Display the new state, if interactive mode is enabled
        if (interactive) {
            displayState(board, years, stagnantYears, state);
        }
    }
}

void csvParse(string fileName, bool board[WIDTH][HEIGHT]) {

   // 2D array to store the initial state of the Game of Life

    // check if the file provieded by the user exists
    ifstream checkFile(fileName);

    // if the file exists continue if not report out error message
    if (checkFile.good() == true)
    {

        // Open the CSV file for reading
        ifstream csvReader(fileName);
        string myText;

        // Variable to track the current line being read in the CSV file
        int fileLength = 0;

        // Process each line of the CSV file
        while (getline(csvReader, myText) && fileLength <= HEIGHT)
        {
            // Parse the current line using a stringstream
            stringstream lineParser(myText);

            // Variable to track the length of the current line
            int lineLength = 0;

            // Flag to indicate if there's an error in the current line
            bool valueError = false;

            // Process each value in the current line
            while (lineParser.good() && fileLength <= (HEIGHT - 1))
            {
                string val;
                // Get a value separated by a comma
                getline(lineParser, val, ',');

                // Check if the value is either 0 or 1 and update the game board storing info as a bool
                if (stoi(val) == 0)
                {
                    board[fileLength][lineLength] = false;
                }
                else if (stoi(val) == 1)
                {
                    board[fileLength][lineLength] = true;
                }
                else
                {
                    // Set an error flag if the value is not 0 or 1
                    valueError = true;
                    break;
                }

                // Move to the next position in the line
                lineLength++;
            }

            // Check for errors in the current line
            if (valueError == true)
            {
                cout << "ERROR: Line " << fileLength << " character " << lineLength << " does not have a valid value of 0 or 1!";
                break; // Exit the loop if an error is encountered
            }
            else if (lineLength != WIDTH)
            {
                cout << "ERROR: Line " << fileLength << " does not have " << WIDTH << " values!";
                break; // Exit the loop if the line length is incorrect
            }

            // Move to the next line in the file
            fileLength++;
        }
    }
    else
    {

        cout << "ERROR: File " << fileName << " does not exist!";
    }
}



/**
 * Simulates a single year of the Game of Life.
 * @param board The board to simulate.
 * @param lastBoard The board from the previous year.
 * @param years The current year.
 * @param stagnantYears The number of years the board has been stagnant.
 */
void simulateYear(bool board[WIDTH][HEIGHT], bool lastBoard[WIDTH][HEIGHT], int& years, int& stagnantYears) {
    // Copy the board to the last board
    copyBoard(board, lastBoard);

    // Update each cell, according to its neighbors
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            int aliveNeighbors = 0; // The number of alive neighbors
            for (int offsetX = -1; offsetX <= 1; offsetX++) { // Loop through the neighbors
                for (int offsetY = -1; offsetY <= 1; offsetY++) {
                    if (offsetX == 0 && offsetY == 0) { // Skip the current cell
                        continue;
                    }
                    int neighborX = x + offsetX, neighborY = y + offsetY; // The coordinate of the neighbor
                    if (neighborX < 0 || neighborX >= WIDTH || neighborY < 0 || neighborY >= HEIGHT) { // Skip neighbors outside the board
                        continue;
                    }
                    if (lastBoard[neighborX][neighborY]) { // Check if the neighbor is alive
                        aliveNeighbors++;
                    }
                }
            }
            // Update the cell
            board[x][y] = lastBoard[x][y] ? aliveNeighbors == 2 || aliveNeighbors == 3 : aliveNeighbors == 3;
        }
    }

    // Increment the year
    years++;
    // Detect board stagnation
    if (boardChanged(board, lastBoard)) {
        stagnantYears = 0; // Reset the stagnant years
    } else {
        stagnantYears++; // Increment the stagnant years
    }
}

/**
 * Checks if the board has changed from the previous year.
 * @param board The board to check.
 * @param lastBoard The board from the previous year.
 * @return Whether the board has changed.
 */
bool boardChanged(bool board[WIDTH][HEIGHT], bool lastBoard[WIDTH][HEIGHT]) {
    // Compare each cell to the corresponding cell on the last board
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            if (board[x][y] != lastBoard[x][y]) {
                return true; // Short-circuit if a cell has changed
            }
        }
    }

    return false;
}

/**
 * Counts the number of alive cells on the board.
 * @param board The board to check.
 * @return The number of alive cells.
 */
int aliveCells(bool board[WIDTH][HEIGHT]) {
    int alive = 0;

    // Count the number of alive cells
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            if (board[x][y]) {
                alive++;
            }
        }
    }

    return alive;
}

/**
 * Checks if the board is empty.
 * @param board The board to check.
 * @return Whether the board is empty.
 */
bool isBoardEmpty(bool board[WIDTH][HEIGHT]) {
    // Check if any cells are alive
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            if (board[x][y]) {
                return false; // Short-circuit if a cell is alive
            }
        }
    }
    return true;
}

/* #endregion */