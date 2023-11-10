/* #region Includes */
#include<iostream>
using namespace std;
/* #endregion */

/* #region Globals */
const int WIDTH = 50;
const int HEIGHT = 50;
/* #endregion */

/* #region Function Declarations */
void clearScreen();

int menuRoutine();
/* #endregion */

/* #region Main */
int main()
{
    clearScreen();
    std::cout << "Hello World!\n";
    return 0;
}
/* #endregion */

/* #region Function Definitions */
void clearScreen() {
    cout << "\033[2J\033[1;1H" << flush;
}

int menuRoutine() {
    return 0; // TODO: Implement
}

/* #endregion */