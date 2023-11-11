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
void clearScreen();

void pause();

void initializeBoard(bool board[WIDTH][HEIGHT]);

void simulate(bool board[WIDTH][HEIGHT], bool lastBoard[WIDTH][HEIGHT], int& years, int& stagnantYears, bool interactive);

void simulateYear(bool board[WIDTH][HEIGHT], bool lastBoard[WIDTH][HEIGHT], int& years, int& stagnantYears);

void clearInput(bool board[WIDTH][HEIGHT], int& years);

void drawBoard(bool board[WIDTH][HEIGHT]);

void copyBoard(bool from[WIDTH][HEIGHT], bool to[WIDTH][HEIGHT]);\

bool emptyBoard(bool board[WIDTH][HEIGHT]);

bool boardChanged(bool board[WIDTH][HEIGHT], bool lastBoard[WIDTH][HEIGHT]);

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
                cout << "  Playing the Game of Life..." << endl;
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
void clearScreen() {
    cout << "\033[2J\033[1;1H" << flush;
}

void pause() {
    cout << "Press RETURN to continue..." << flush;
    cin.ignore();
    cin.get();
}

void initializeBoard(bool board[WIDTH][HEIGHT]) {
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            board[x][y] = false;
        }
    }
}

void copyBoard(bool from[WIDTH][HEIGHT], bool to[WIDTH][HEIGHT]) {
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            to[x][y] = from[x][y];
        }
    }
}

void clearInput(bool board[WIDTH][HEIGHT], int& years) {
    initializeBoard(board);
    years = 0;

    clearScreen();
    cout << "  Input cleared." << endl;
    drawBoard(board);
    cout << "  Current year: " << years << endl;
    pause();
}

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

void simulate(bool board[WIDTH][HEIGHT], bool lastBoard[WIDTH][HEIGHT], int& years, int& stagnantYears, bool interactive) {
    while (years < MAX_YEARS && stagnantYears < MAX_STAGNANT_YEARS && !emptyBoard(board)) {
        simulateYear(board, lastBoard, years, stagnantYears);
        if (interactive) {
            clearScreen();
            drawBoard(board);
            cout << "  Current year: " << years << endl;
            pause();
        }
    }
}

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

/* #endregion */