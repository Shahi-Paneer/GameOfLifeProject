#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int main()
{

    // Constants for file information
    const string FILE_NAME = "intialSetup.csv";
    const int FILE_LENGTH = 4;      // Number of rows in the game board
    const int FILE_LINE_LENGTH = 5; // Number of columns in the game board

    // 2D array to store the initial state of the Game of Life
    bool gameBoard[FILE_LENGTH][FILE_LINE_LENGTH];

    // check if the file provieded by the user exists
    ifstream checkFile(FILE_NAME);

    // if the file exists continue if not report out error message
    if (checkFile.good() == true)
    {

        // Open the CSV file for reading
        ifstream csvReader(FILE_NAME);
        string myText;

        // Variable to track the current line being read in the CSV file
        int fileLength = 0;

        // Process each line of the CSV file
        while (getline(csvReader, myText))
        {
            // Parse the current line using a stringstream
            stringstream lineParser(myText);

            // Variable to track the length of the current line
            int lineLength = 0;

            // Flag to indicate if there's an error in the current line
            bool valueError = false;

            // Process each value in the current line
            while (lineParser.good())
            {
                string val;
                // Get a value separated by a comma
                getline(lineParser, val, ',');

                // Check if the value is either 0 or 1 and update the game board storing info as a bool
                if (stoi(val) == 0)
                {
                    gameBoard[fileLength][lineLength] = false;
                }
                else if (stoi(val) == 1)
                {
                    gameBoard[fileLength][lineLength] = true;
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
            else if (lineLength != FILE_LINE_LENGTH)
            {
                cout << "ERROR: Line " << fileLength << " does not have " << FILE_LINE_LENGTH << " values!";
                break; // Exit the loop if the line length is incorrect
            }

            // Move to the next line in the file
            fileLength++;
        }

        // Display the populated game board (for debugging purposes)
        cout << "Initial Game Board:" << endl;
        for (int i = 0; i < FILE_LENGTH; i++)
        {
            for (int j = 0; j < FILE_LINE_LENGTH; j++)
            {
                int output = 0;
                if (gameBoard[i][j] == true)
                {
                    output = 1;
                }
                cout << gameBoard[i][j] << ", ";
            }
            cout << endl;
        }
    }
    else
    {

        cout << "ERROR: File " << FILE_NAME << " does not exist!";
    }

    //----------------------------------------------------------------------------------------------------------
    // start code here

    // function to check all neighbors then return report when passed a postition

    for (int y = 0; y < FILE_LENGTH; y++)
    {
        for (int x = 0; x < FILE_LINE_LENGTH; x++)
        {

            int aliveNeighbors = 0;

            if (y == 0)
            {

                if (x == 0)
                {
                    if (gameBoard[x + 1][y] == true)
                    {

                        aliveNeighbors++;
                    }

                    if (gameBoard[x + 1][y + 1] == true)
                    {

                        aliveNeighbors++;
                    }

                    if (gameBoard[x][y + 1] == true)
                    {

                        aliveNeighbors++;
                    }
                } else if (x == FILE_LINE_LENGTH)
                {

                    if (gameBoard[x - 1][y] == true)
                    {

                        aliveNeighbors++;
                    }

                    if (gameBoard[x - 1][y + 1] == true)
                    {

                        aliveNeighbors++;
                    }

                    if (gameBoard[x][y + 1] == true)
                    {

                        aliveNeighbors++;
                    }
                } else {

                    if (gameBoard[x - 1][y] == true) {aliveNeighbors++; cout << "\nLOL" << boolalpha << gameBoard[x - 1][y] << "\n";}

                    if (gameBoard[x + 1][y] == true) {aliveNeighbors++;}

                    if (gameBoard[x - 1][y + 1] == true) {aliveNeighbors++;}

                    if (gameBoard[x][y + 1] == true) {aliveNeighbors++;}
                    
                    if (gameBoard[x + 1][y + 1] == true) {aliveNeighbors++;}

                }

            } else if (y != 0 && y != FILE_LENGTH) {

                if (x == 0) {

                    if (gameBoard[x][y - 1] == true) {aliveNeighbors++;}

                    if (gameBoard[x + 1][y - 1] == true) {aliveNeighbors++;}

                    if (gameBoard[x + 1][y] == true) {aliveNeighbors++;}

                    if (gameBoard[x][y + 1] == true) {aliveNeighbors++;}

                    if (gameBoard[x + 1][y + 1] == true) {aliveNeighbors++;}

                } else if (x == FILE_LINE_LENGTH){

                   if (gameBoard[x - 1][y - 1] == true) {aliveNeighbors++;}

                    if (gameBoard[x][y - 1] == true) {aliveNeighbors++;}

                    if (gameBoard[x - 1][y] == true) {aliveNeighbors++;}
                    
                    if (gameBoard[x - 1][y + 1] == true) {aliveNeighbors++;}

                    if (gameBoard[x][y + 1] == true) {aliveNeighbors++;}

                } else {

                    if (gameBoard[x - 1][y - 1] == true) {aliveNeighbors++;}

                    if (gameBoard[x][y - 1] == true) {aliveNeighbors++;}

                    if (gameBoard[x + 1][y - 1] == true) {aliveNeighbors++;}

                    if (gameBoard[x - 1][y] == true) {aliveNeighbors++;}

                    if (gameBoard[x + 1][y] == true) {aliveNeighbors++;}
                    
                    if (gameBoard[x - 1][y + 1] == true) {aliveNeighbors++;}

                    if (gameBoard[x][y + 1] == true) {aliveNeighbors++;}

                    if (gameBoard[x + 1][y + 1] == true) {aliveNeighbors++;}

                }
                

            } else if (y == FILE_LENGTH) {

                if (x == 0) {

                    if (gameBoard[x][y- 1] == true) {aliveNeighbors++;}

                    if (gameBoard[x + 1][y - 1] == true) {aliveNeighbors++;}

                    if (gameBoard[x + 1][y] == true) {aliveNeighbors++;}

                } else if (x == FILE_LINE_LENGTH) {

                    if (gameBoard[x][y- 1] == true) {aliveNeighbors++;}

                    if (gameBoard[x - 1][y - 1] == true) {aliveNeighbors++;}

                    if (gameBoard[x - 1][y] == true) {aliveNeighbors++;}

                } else {

                    if (gameBoard[x - 1][y] == true) {aliveNeighbors++;}

                    if (gameBoard[x + 1][y] == true) {aliveNeighbors++;}

                    if (gameBoard[x - 1][y - 1] == true) {aliveNeighbors++;}

                    if (gameBoard[x][y - 1] == true) {aliveNeighbors++;}
                    
                    if (gameBoard[x + 1][y - 1] == true) {aliveNeighbors++;}

                }
                
            }



            cout << "Position( " << x + 1 << ", " << y + 1 << " ) Alive: " << aliveNeighbors << "   " << boolalpha << gameBoard[x + 1][y - 1] << endl;
        }
    }
}