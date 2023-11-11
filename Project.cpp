/* #region Includes */
#include<iostream>
using namespace std;
/* #endregion */

/* #region Globals */
const int WIDTH = 50;
const int HEIGHT = 50;
const int TOTAL_CELLS = WIDTH * HEIGHT;
const int MAX_YEARS = 100;
const int MAX_STAGNANT_YEARS = 20;
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
    bool gameActive = true;
    bool board[WIDTH][HEIGHT];
    bool lastBoard[WIDTH][HEIGHT];
    initializeBoard(board);
    int years = 0;
    int stagnantYears = 0;

    while (gameActive) {
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

        while (true) {
            cout << "  Enter your choice: " << flush;
            
            int choice;
            cin >> choice;
            cout << endl;

            if (choice == 1) {
                clearInput(board, years);
                break;
            }
            else if (choice == 2) {
                cout << "  Setting state from CSV file..." << endl;
                break;
            }
            else if (choice == 3) {
                simulate(board, lastBoard, years, stagnantYears, true);
                break;
            }
            else if (choice == 4) {
                cout << "  Reporting summary statistics..." << endl;
                break;
            }
            else if (choice == 5) {
                cout << "  Random play..." << endl;
                break;
            }
            else if (choice == 6) {
                cout << "  Outputting histogram..." << endl;
                break;
            }
            else if (choice == 7) {
                gameActive = false;
                cout << endl << "Thanks for playing!" << endl;
                break;
            }
            else {
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
 * Simulates the Game of Life for a single year.
 * @param board The board to simulate.
 * @param lastBoard The board from the previous year.
 * @param years The current year.
 * @param stagnantYears The number of years the board has been stagnant.
 * @param interactive Whether to display the board after each year.
 */
void simulate(bool board[WIDTH][HEIGHT], bool lastBoard[WIDTH][HEIGHT], int& years, int& stagnantYears, bool interactive) {
    if (interactive) {
        clearScreen();
        drawBoard(board);
        cout << "  Current year: " << years << endl;
        pause();
    }
    
    bool isEmpty;
    while (years < MAX_YEARS && stagnantYears < MAX_STAGNANT_YEARS && !isEmpty) {
        simulateYear(board, lastBoard, years, stagnantYears);
        isEmpty = isBoardEmpty(board);
        if (interactive) {
            clearScreen();
            drawBoard(board);
            cout << "  Current year: " << years << endl;
            pause();
        }
    }

    if (interactive) {
        clearScreen();
        drawBoard(board);
        cout << "  Game ended after " << years << " years." << endl;
        if (isEmpty) {
            cout << "  All cells are dead." << endl;
        } else if (stagnantYears >= MAX_STAGNANT_YEARS) {
            cout << "  Game stagnated for " << stagnantYears << " years." << endl;
        }

        int alive = aliveCells(board);
        cout << endl << "  Alive cells: " << alive << endl
            << "  Dead cells: " << (TOTAL_CELLS - alive) << endl;

        pause();
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
    copyBoard(board, lastBoard);

    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            // TODO
        }
    }

    years++;
    if (boardChanged(board, lastBoard)) {
        stagnantYears = 0;
    }
    else {
        stagnantYears++;
    }
}

/**
 * Checks if the board has changed from the previous year.
 * @param board The board to check.
 * @param lastBoard The board from the previous year.
 * @return Whether the board has changed.
 */
bool boardChanged(bool board[WIDTH][HEIGHT], bool lastBoard[WIDTH][HEIGHT]) {
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            if (board[x][y] != lastBoard[x][y]) {
                return true;
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
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            if (board[x][y]) {
                return false;
            }
        }
    }
    return true;
}

/* #endregion */