#include <iostream>
#include <fstream>
#include <random>

using namespace std;

//declare constants for the specified range for creating a random number
const double PROB_MAX = 1.0; 
const double PROB_MIN = 0.0; 

const int ROWS = 50;
const int COLS = 50;

//function prototypes
void initializeRandomGrid (double , int grid[][COLS]);

int main()
{   
    //declare variables for the program
    int grid[ROWS][COLS];

    int randomPlayTimes;
    double aliveProbability;

    //get user input for the number of times to play the random play
    cout << "You chose a random play. Please enter a number of times to play the game. " ;
    cin >> randomPlayTimes;

    //validate input for the times to play the random play 
    while (randomPlayTimes <= 0)
    {
        cout << "Invalid input, please enter a positive integer. " ;
        cin >> randomPlayTimes;
    }

    //get user input for the probability of a cell being alive
    cout << "Please enter a probability for a cell to be alive," << endl;
    cout << "e.g. 0.5 to say that each cell has a 50/50 shot to start as alive. " ;
    cin >> aliveProbability;

    //validate input for the probability of a cell being alive
    while (aliveProbability < PROB_MIN || aliveProbability > PROB_MAX)
    {
        cout << "Invalid input, please enter a number between 0 and 1. " ;
        cin >> aliveProbability;
    }
    
    //loop through the number of random play iterations
    for (int play = 0; play < randomPlayTimes; play++)
    {   
        //call the function to initialize the board with random values based on user probability input
        initializeRandomGrid(aliveProbability, grid);

        /*
        //display random board states
        cout << "Initial grid for play " << play + 1 << ":" << endl;
        for (int i = 0; i < ROWS; ++i) 
        {
            for (int j = 0; j < COLS; ++j) 
            {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        */
    }

    return 0;
}

//the function to initialize the board with random values based on user probability input
void initializeRandomGrid (double userProbability, int grid[][COLS])
{
    //initialize random number generator
    random_device myEngine;
    //create a number between 0.0 and 1.0
    uniform_real_distribution<double> randomNum(PROB_MIN, PROB_MAX);

    for (int i = 0; i < ROWS; ++i) 
    {
        for (int j = 0; j < COLS; ++j) 
        {
            double cellResult = randomNum(myEngine);
            if (cellResult < userProbability) 
            {
                grid[i][j] = 1; //set as alive
            } 
            else 
            {
                grid[i][j] = 0; //set as dead
            }
        }
    }
}