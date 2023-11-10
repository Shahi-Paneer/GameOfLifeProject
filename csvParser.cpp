#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int main()
{


// git add .
// git commmit -m "insert message here"
// git push

    const string FILE_NAME = "intialSetup.csv";
    const int FILE_LENGTH = 4;
    const int FILE_LINE_LENGTH = 5;

    int gameBoard[FILE_LENGTH][FILE_LINE_LENGTH];

    ifstream csvReader(FILE_NAME);
    string myText;

    int fileLength = 0;

    stringstream s("myText");
    while (getline(csvReader, myText))
    {
        // Output the text from the file
        cout << myText;
        

        stringstream lineParser(myText);

        int lineLength = 0;

        bool valueError = false;

        while (lineParser.good())
        {

            string val;
            getline(lineParser, val, ',');

            cout << endl
                 << val << endl;
                 
            if (stoi(val) == 0 || stoi(val) == 1)
            {
                gameBoard[fileLength][lineLength] = stoi(val);
            }
            else
            {
                valueError = true;
                break;

            }
            lineLength++;
        }



        if (valueError == true)
        {
            cout << "ERROR: Line " << fileLength << " charector " << lineLength << " does not have a valid value of 0 or 1!";
            break;
        }
        else if (lineLength != FILE_LINE_LENGTH)
        {
            cout << "ERROR: Line " << fileLength << " does not have " << FILE_LINE_LENGTH << " values!";
            break;
        }

        fileLength++;
    }

    cout << endl
         << endl;

    for (int i = 0; i < FILE_LENGTH; i++)
    {
        for (int j = 0; j < FILE_LINE_LENGTH; j++)
        {

            cout << gameBoard[i][j] << ", ";
        }
        cout << endl;
    }
}