/*
*   "2D Array"
*
*   This program demonstrates 2-dimensional arrays and user-defined functions.
*   The program reads from a file of locations on a 2-D board at which “pegs” are placed.
*
* Sources:
*   I got the code for the Sleep function here: https://www.softwaretestinghelp.com/cpp-sleep/
*
*
* History:
*   2020-11-21 Jesse Black  Based on an earlier program named "Starry Night"
*/

#include <iostream>         // cout and cin and endl
#include <fstream>          // for file I/O
#include <iomanip>          // for setw
#include <stdlib.h>         // for system() call

        // these next few lines will bring in the Sleep function in Windows and maybe Linux.
        // see https://www.softwaretestinghelp.com/cpp-sleep/
/* This line comments out the following code.
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
This line ends the previous comment */

using namespace std;        // so we don't need std:: in front of everything

    // Define named constants for the array size.
const string INPUT_FILE_NAME = "locations.txt";  // this will be our input file
const int MAX_ROWS = 40;    // Maximum number of rows in board
const int MAX_COLS = 70;    // Maximum number of columns in board
    // Define some characters that look good
const char ASTAR = '*';     // This character represents the peg
const char NOSTAR = '.';    // clear board character
const char CENTERED_DOT = 249; // one of the extended ASCII codes, looks good in Windows but not onlineGDB
const char ASCII_DOT = '.'; //


        // function prototypes
int clearBoard( char s[MAX_ROWS][MAX_COLS], char clearChar );
int putPeg( char board[MAX_ROWS][MAX_COLS], int nrows, int ncols, int r, int c, char peg );
int printBoard( char s[MAX_ROWS][MAX_COLS], int nrows, int ncols );
int horizontalRuler( int leading, int width, char, char, char );


int main()
{
    int ncols = 0;              // requested width of board
    int nrows = 0;              // requested height of board
    int r, c;                   // values entered by the user.
    char pegChar = 'O';        // default value for a "peg".
    int needed_fixing = 0;
    ifstream ifile; // this object will be our input file

    // Step 2. and allocates board for an array of maximum size.
    // const char ARRAYSIZE = 20;
    char board[MAX_ROWS][MAX_COLS];  // declare an array which will hold the board

    // Step 3. Displays a message to the user describing what the program will do.
    cout << "This program reads a data file and puts pegs into a 2D array."<< endl;

    cout << "Enter the character you want to use as a 'peg' and press Enter: ";
    cin >> pegChar;

        // Check if the file opened successfully.
        // Display the message “Loading” and the name of the file.
    cout << "Loading " << INPUT_FILE_NAME << " ..." << endl;
        // open the input file
    ifile.open( INPUT_FILE_NAME );
        // Check if the file opened successfully.
	if ( ! ifile.is_open()) // if the input file is not open ...
    {
		cout << "Unable to open input file " << INPUT_FILE_NAME << endl;
		 // get out of this function and return a negative value as an indicator of badness.
		return -1;
	} // check for open failure

        // get the dimensions of the user's drawing area
    ifile >> nrows >> ncols;
    ifile.ignore(1000,'\n'); // ignore the rest of the line - optional
    cout << "The drawing area is " << nrows << " rows high and " << ncols << " columns wide." << endl;
    cout << "When entering coordinates, be aware that the board begins at 0 0 and ends at " << nrows-1 << " " << ncols-1 << endl;

	        // clear the board
    clearBoard( board, ASCII_DOT );

        // read data from the file
    while ( ifile.good() )
    {
                // read data from the input file
        ifile >> r >> c;    // read a row and column from the file
        ifile.ignore(1000,'\n'); // ignore the rest of the line - optional
        if ( ! ifile.good() )
            break;  // the read operation did not succeed, so get out of the loop.

            // Break out of the loop if either of the coordinates is less than the minimum
        if ( r < 0 || c < 0 ) break;

         // Call a function to place a peg at the row and column specified by the user.
         // Pass the following to the function:
         //   1. The array you created.
         //   2. The number of rows and columns in the array, or the number of rows and columns the user specified earlier.
         //   3. The row and column of the peg.
        needed_fixing = putPeg( board, nrows, ncols, r, c, pegChar );

                // clear the screen.
                // This is not necessary, but if it works, the output is niftier.
                // Note: May be specific to Microsoft operating system or terminal.
//        system("cls");
        cout << "Row " << r << " , Column " << c << endl;    // for debugging
        printBoard( board, nrows, ncols );

                // sleep for this many seconds to slow output.
                // Comment this out if your compiler doesn't like it.
//       Sleep(500);

    } // while

    ifile.close();  // close the input file (always the polite thing to do!)


            // After the loop, the program should end,
            // returning the most recent result of the peg-placing function.
    return needed_fixing;       // return most recent value of "coordinates needed fixing".
} // main


        // function clearBoard
        // set the entire board to an initial value which indicates "no peg here".
        // we could have cleared only the part of the board that the user requested,
        // if we had also been given the actual number of rows and columns to be used.
int clearBoard( char s[MAX_ROWS][MAX_COLS], char clearChar )
{
            // for every row
    for ( int r=0; r<MAX_ROWS; ++r )
    {
            // for every column
        for ( int c=0; c<MAX_COLS; ++c )
            s[r][c] = clearChar;
    } // for
    return 0;   // nothing significant to return
} // clearBoard


    // function putPeg
    // The function should check if the user-requested row and column are inside the array.
    // If so, remember to return 0 from the function later. If the user-requested row and column are not within the bounds you are prepared to handle, applying the modulus operator to fix the row and column and remember to return 1 later.
         // Parameters to the function:
         //   1. The array you created.
         //   2. The number of rows and columns in the array, or the number of rows and columns the user specified earlier.
         //   3. The row and column of the peg.
int putPeg( char board[MAX_ROWS][MAX_COLS], int nrows, int ncols, int r, int c, char peg )
{
    int farout = 0;
    if ( r < 0 || r >= nrows )
    {
        farout = 1;     // remember that we had to correct one of the coordinates.
        r = r % nrows;  // wrap around top-to-bottom
    }

    if ( c < 0 || c >= ncols )
    {
        farout = 1;     // remember that we had to correct one of the coordinates.
        c = c % ncols;  // wrap around the sides
    }
    board[r][c] = peg;
    return farout;
} // putPeg


int printBoard( char s[MAX_ROWS][MAX_COLS], int nrows, int ncols )
{
            // print the rows
    for ( int r=0; r<nrows; ++r )
    {
        cout << setw(3) << r << ": ";   // display the row number in a fixed-width field
            // print a row of space or pegs
        for ( int c=0; c<ncols; ++c )
            cout << s[r][c];
        cout << endl;                   // end of the row
    } // for
    return 0;   // nothing significant to return
} // printBoard
