/*
*   This program calculates the cost of admission to the Colossal Cinema.
*
*   Randi Bolt, November 24, 2020
*
*   Sources: Past Colossal Cinema Programs
*
*   Sources: Jesse Black's CS-161 lectures
*
*   Update : Added comments to functions
*            and removed verbose for ages
*            2-10.
*
*/

#include <iostream>                 // cin, cout, and endl
#include <iomanip>                  // setprecision(), fixed, and showpoint

using namespace std;

//function prototypes
double getNonNegativeDouble ( string prompt );
double colossalCost (double age, bool verbose=false);

// main function that prints the final Group Cost Taxed
// no parameters
int main ()
{
    //variables declaring
    bool extraMessages = false;            // extraMessages = false, extra messages are turned off
    double cost;                           // ticket cost
    double age;                           // age
    double GroupCost;                     // group cost before tax
    double GroupCostTaxed;                // group total  taxed
    const double tax = 0.065;             // 6.5% tax, can be changed here

    //tells the user what the program does, and that 0 ends the loop
    cout << "This program calculates the cost of admission to Colossal Cinema." << endl;
    cout << "(Use age of 0 to indicate there are no more persons in this group.)" << endl;

    // fixed # to right of decimal, and shows the decimal point to 2 places
    cout << fixed << showpoint << setprecision(2);

    //beginning of do ... while bottom tested loop
    do
    {
        //asks the user for their age, and checks it's not negative
        age = getNonNegativeDouble("Enter the age of this person: ");

        //if loop for ages greater than 0
        if (age > 0 )
        {
            //matches the users age with ticket cost, and prints extraMessages if boolean is = true
            cost = colossalCost(age,extraMessages);

            GroupCost = GroupCost + cost;                                         //running total of cost
            cout << "The cost for this group so far: $" << GroupCost <<endl;      //prints group cost pretax to user
        }                                                                          // end of if for age > 0

    } while (age != 0);                                                           //end do/while loop when user enters 0


    GroupCostTaxed = GroupCost + (GroupCost*tax);                       // calculates group ticket price with tax

    cout << "Your cost with tax is $" << GroupCostTaxed <<  endl;      // tells the user their group ticket price with tax


 return 0;                                                          // return value that indicates all is well
}                                                                   // ends main function

//function prompts the user for their age, and tells them negatives are not allowed if one is entered
// parameter is the string prompting the user for their age
// return value is a double for age
double getNonNegativeDouble ( string prompt )
{
    double age;                         // variables declared

    cout << endl;                      //adds empty line before asking the user to enter their age
    cout << prompt;                    // prompts user to input age: "Enter the age of this person"
    cin >> age;                       // saves input into age variable

    if (age < 0)                                                // if loop for negative ages
        {
            cout << "Negative value is not allowed." << endl;    //tells the user negative are not allowed
            cin.clear();                                        // clear the error
            cin.ignore(210000000000, '\n');                     // ignore lots of input on this line
        }                                                       // ends if loop for age < 0

 return age;                                                    // returns age to the main function
}                                                               // end getNonNegativeDouble function

// function matches the ticket cost with age, and prints verbose is set to true in main function
// parameter is double age, and a bool t/f verbose if the user would like added commentary
// return value is a double value for the cost
double colossalCost (double age, bool verbose)
{
    // variables declaring
    double cost;                                // ticket cost
    const double toddlerRate = 1.00;            // toddler ticket price
    const double childRate = 12.00;             // child ticket price
    const double standardRate = 20.00;          //standard ticket price
    const double discount = 0.1;          // 10% discount, can be changed here

    if (verbose)                                // if verbose is true
    {
            cout << "Hmmm ... " << age <<  " years old ... Let me check my rate sheet." << endl;     // tells the user the age they input
    }

    if( age < 2 )                                                // if the user is less than 2 years old
    {
        if (verbose)                                            // if verbose is true
        {
            cout << "What a cutie you have there!" <<endl;      // compliments the baby
        }                                                      // ends if verbose statement

        cost = toddlerRate;                                   // calculates Ticket Price $1.00
    }                                                         // ends if age < 2 statement

    else if (2 <= age and age < 10)                      // if the user is greater than or 2 years old AND less than 10 years old
    {
            cost = childRate;                            // calculates Ticket Price $12.00
    }                                                   // ends if age is between 2-10 statment

    else if (10 <= age and  age < 60 )                      //if the user is greater than or 10 years old AND less than sixty years old
    {
        cost = standardRate;                                 // calculates Ticket Price $20.00
    }                                                       // ends if age is between 10-60 statement

    else                                                    // if the user is 60 years old, or older
    {
        if (verbose)                                                       // if verbose is true
        {
            cout <<"You qualify for the senior discount!" << endl;        // tells the user they qualify for the senior discount
        }                                                                 // ends if verbose statement
        cost = standardRate - ( standardRate * discount );               // calculates the discounted senior ticket price
    }

    cout << "The cost for this person is $" << cost << endl;            // prints the cost that matches the users age


    return cost;                                        // returns cost to the main program
}                                                       // ends colassalCost function
