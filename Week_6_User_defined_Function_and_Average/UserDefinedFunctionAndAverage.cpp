/*
*   This program computes the average n of even numbers in a user-specified range
*   Randi Bolt, October 29, 2020
*   Sources: Jesse Black: Lectures October 26, 2020
*   Sources: Check Even/Odd modified from Program by Chaitanya Sighn at beginnersbook.com
*   Sources: Tanner Heffner helped debug the for and if statement. He also caught the return=0 error.
*/

#include <iostream>

using namespace std;

bool checkEvenOdd (int &i);     //this is a function prototype

int main ()                 //main program
{
    //variables declaring
    int val1;               //users first input, lower range (int bc program asks for int values)
    int val2;               //user second input, upper ranger (int bc program asks for int values)
    int i;                  //i loop, that gets print, 1 added to it, and tested to see if it's even or odd
    int n=0;                //n counts the number of even int between range. Starts at zero.
    int sum=0;              //sum adds up the sum of n. Starts at zero.
    int avg;                //int math for average=sum/n
    bool isEven;            //bool that is true when i is even and false when i is odd.

    //tells the user what the program does
    cout << "This program computes the average of the even numbers in a user-specified range " << endl;

    //ask the user for an integer
    cout << "Enter the starting integer and ending integer for a range of values." << endl;     // asks the user for two integers for a range
    cout << "The starting value should be less than or equal to the ending value: ";            //tells user less starting value should be < the ending value
    cin >> val1 >> val2;                    //user inputs val1 and val2

        for (i=val1; i <= val2; i++)        //for loop that sets i = val1, when i is less than or equal to val2, the program add ones
        {
            cout << i << " " << endl;       //program outputs i to the user with a space after it.
            isEven = checkEvenOdd(i);       //the program checks if i is even or odd

            if (isEven)                     //if loop for when the int value is even
            {
                sum = sum + i;              //the even int value i is added to the sum
                n = n + 1;                  //1 is also added to the number, n, of even numbers being added
            }                               //close if loop
        }                                   //close for loop

    avg = sum / n ;                         //math that calculates the average of even integers from a range of val1 and val2

    //Prints out the average number of even integers 'n' between val1 and val2 to the user
    cout << "The average of " << n << " even integers in the range from " << val1 << " to " << val2 << " is " << avg << ".";

 return 0;       // return value that indicates all is well
}

bool checkEvenOdd (int &i)     //2nd parameter passes i through
{
    bool b;                     //declares bool variable b, only inside this parameter

    if (i%2 == 0)               // if i divided by 2 has a 0 remainder run this loop
    {
        b=true;                 // b is true
    }                           //ends loop

    else                        // else loop, 2 does not have a remainder of 2
    {
        b=false;                //b is false
    }                           //ends loop
    return b;               //Returns b not 0 bc/ 0 is a bool false which messes up the program. Find by Tanner.
                            //Jesse Monday Oct. 24th : "you're not suppose to pass numbers through to reference"
}                           //ends second parameter
