/* #region Includes */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include <vector>
#include <cctype>
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

//declare constants for the probability
const double PROB_MAX = 1.0; 
const double PROB_MIN = 0.0; 

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

/* #region Structs and Enums */

// NOTE: I (Anna) used this struct because we will need to extract a lot of data
// in a lot of different places, and it will be easier to do that if we have a
// struct to centralize all of the data.
/**
 * Statistics collector for the Game of Life.
 * Used to store statistics for each game played.
 */
struct Statistics {
   /**
    * How many years each game played so far has taken for its completion.
    */
    vector<int> endYears;

    // NOTE: This part is not trivial for me (Anna) because the description is not clear enough.
    // Ask the professor for clarification.
    /*
    Report of, on average, how many cells survive the game of life,
    and how many years it takes, for every game played so far (including random play)
    */
   // Average at the end of each game? or at each year?
   // How many cells survive from the beginning of the game? or at each year? or at the end of each game?
   // Do we have to track % of total vs alive cells? or just the number of alive cells?
};

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
 * Randomizes the board to a random state.
 * @param aliveChance The chance that any given cell is alive, between 0 and 1.
 * @param board The board to randomize.
 */
void randomizeBoard(double aliveChance, bool board[WIDTH][HEIGHT]);

/**
 * Simulates the Game of Life for a single year.
 * @param board The board to simulate.
 * @param lastBoard The board from the previous year.
 * @param years The current year.
 * @param stagnantYears The number of years the board has been stagnant.
 * @param stats The statistics collector for the Game of Life.
 * @param interactive Whether to display the board after each year.
 */
void simulate(bool board[WIDTH][HEIGHT], bool lastBoard[WIDTH][HEIGHT], int& years, int& stagnantYears, Statistics& stats, bool interactive);

/**
 * Parses an input Game of Life CSV file and loads it into the given board.
 * @param fileName The name of the file to load.
 * @param board The board to load the file into.
 * @return Whether the file was parsed successfully.
*/
bool parseCsv(string fileName, bool board[WIDTH][HEIGHT]);

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
 * Routine for random play.
 * The main function passes off the interactive control to this function.
 * 
 * @param board The board to simulate.
 * @param lastBoard The board from the previous year.
 * @param years The current year.
 * @param stagnantYears The number of years the board has been stagnant.
 * @param stats The statistics collector for the Game of Life.
 */
void randomPlayRoutine(bool board[WIDTH][HEIGHT], bool lastBoard[WIDTH][HEIGHT], int& years, int& stagnantYears, Statistics& stats);

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

    // Statistics collector for the Game of Life
    Statistics stats;

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
                // TODO: Implement this
                break;
            } else if (choice == 3) {
                // 3. Play the Game of Life
                simulate(board, lastBoard, years, stagnantYears, stats, true);
                break;
            } else if (choice == 4) {
                // 4. Report summary statistics
                cout << "  Reporting summary statistics..." << endl;
                // TODO: Implement this
                break;
            } else if (choice == 5) {
                // 5. Random play
                randomPlayRoutine(board, lastBoard, years, stagnantYears, stats);
                break;
            } else if (choice == 6) {
                // 6. Output histogram
                cout << "  Outputting histogram..." << endl;
                // TODO: Implement this
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
 * Routine for random play.
 * The main function passes off the interactive control to this function.
 * 
 * @param board The board to simulate.
 * @param lastBoard The board from the previous year.
 * @param years The current year.
 * @param stagnantYears The number of years the board has been stagnant.
 * @param stats The statistics collector for the Game of Life.
 */
void randomPlayRoutine(bool board[WIDTH][HEIGHT], bool lastBoard[WIDTH][HEIGHT], int& years, int& stagnantYears, Statistics& stats) {
    // Variables to store user input
    int randomPlayTimes;
    double aliveChance;

    // Prompt the user for input
    while (true) {
        cout << "Please enter a number of times of random play to occur:" << endl;
        cin >> randomPlayTimes;

        if (randomPlayTimes > 0) {
            break;
        }

        cout << "Invalid input: The number of times to play must greater than 0." << endl;
    }
    
    // Prompt the user for input
    while (true) {
        // cout << "Please enter a probability for a cell to be alive," << endl;
        // cout << "e.g. 0.5 to say that each cell has a 50/50 shot to start as alive. " ;
        cout << "Please enter a probability for a cell to be alive:" << endl;
        cout << "  (eg. 0.5 means a 50/50 chance for a cell to be alive)" << endl;
        cin >> aliveChance;

        if (aliveChance >= PROB_MIN && aliveChance <= PROB_MAX) {
            break;
        }

        cout << "Invalid input: The probability must be between 0 and 1." << endl;
    }
    
    // Loop #randomPlayTimes times of random play iterations
    for (int play = 0; play < randomPlayTimes; play++) {
        // Randomize the board to a random state
        randomizeBoard(aliveChance, board);
        // Reset the years and stagnant years
        years = 0;
        stagnantYears = 0;

        simulate(board, lastBoard, years, stagnantYears, stats, false);
        // TODO: Statistics thing
    }
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
 * @param stats The statistics collector for the Game of Life.
 * @param interactive Whether to display the board after each year.
 */
void simulate(bool board[WIDTH][HEIGHT], bool lastBoard[WIDTH][HEIGHT], int& years, int& stagnantYears, Statistics& stats, bool interactive) {
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
        // TODO: Statistics thing
    }
}

/**
 * Parses an input Game of Life CSV file and loads it into the given board.
 * @param fileName The name of the file to load.
 * @param board The board to load the file into.
 * @return Whether the file was parsed successfully.
*/
bool parseCsv(string fileName, bool board[WIDTH][HEIGHT]) {
    ifstream csvReader(fileName); // Reader for the CSV file

    if (!csvReader.good()) { // Check if the file exists
        cout << "ERROR: File " << fileName << " does not exist!";
        return;
    }

    string csvLine; // Variable to store the current line of the CSV file
    int boardX = 0, boardY = 0; // Variables to track the current position on the board
    bool error = false; // Flag to indicate if there's an error in the file

    // Process each line of the CSV file
    while (!error && boardY < HEIGHT && getline(csvReader, csvLine)) {
        // Parse the current line using a stringstream
        stringstream lineParser(csvLine);

        boardX = 0; // Reset the X position

        // Process each value in the current line
        while (!error && boardX < WIDTH && lineParser.good()) {
            string valueString;
            // Get a value separated by a comma
            getline(lineParser, valueString, ',');

            // Check if the value is empty
            if (valueString.empty()) {
                cout << "ERROR: Cell (" << boardX << ", " << boardY << ") does not have a value!";
                error = true; // Set the error flag
                break;
            }

            // Check if the value is longer than 1 character
            if (valueString.length() > 1) {
                cout << "ERROR: Cell (" << boardX << ", " << boardY << ") has a value longer than 1 character!";
                error = true; // Set the error flag
                break;
            }

            // Check if the value is not a digit
            if (!isdigit(valueString[0])) {
                cout << "ERROR: Cell (" << boardX << ", " << boardY << ") does not have a valid value!";
                error = true; // Set the error flag
                break;
            }

            int value = stoi(valueString); // Convert the value to an int

            // Check if the value is not 0 or 1
            if (value != 0 && value != 1) {
                cout << "ERROR: Cell (" << boardX << ", " << boardY << ") does not have a valid value of 0 or 1!";
                error = true; // Set the error flag
                break;
            }

            board[boardX][boardY] = (value == 1); // Store the value as a bool

            boardX++; // Move to the next position in the line
        }

        // Check if not enough values were read in the line
        if (boardX != WIDTH) {
            cout << "ERROR: Line " << boardY << " does not have " << WIDTH << " values!";
            error = true; // Set the error flag
            break;
        }
        
        // Check if there are more values to be read in the line
        if (!lineParser.eof()) {
            // There are more values in the line than expected
            cout << "ERROR: Line " << boardY << " has more than " << WIDTH << " values!";
            error = true; // Set the error flag
            break;
        }

        // Move to the next line in the file
        boardY++;
    }

    // Check if not enough lines were read in the file
    if (boardY != HEIGHT) {
        cout << "ERROR: File does not have " << HEIGHT << " lines!";
        error = true; // Set the error flag
    }

    // Check if there are more lines to be read in the file
    if (!csvReader.eof()) {
        // There are more lines in the file than expected
        cout << "ERROR: File has more than " << HEIGHT << " lines!";
        error = true; // Set the error flag
    }

    return !error; // Return whether there was an error
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

//the function to initialize the board with random values based on user probability input
void randomizeBoard(double aliveChance, bool board[WIDTH][HEIGHT]) {
    random_device randomEngine; // Random number engine
    uniform_real_distribution<double> randomDouble(PROB_MIN, PROB_MAX); // Create a random double between PROB_MIN and PROB_MAX

    // Loop through each cell
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            board[x][y] = (randomDouble(randomEngine) < aliveChance); // Set each cell to alive or dead based on the chance
        }
    }
}
/* #endregion */