/*
*   Colossal Cinema with Parallel Arrays
*
*   This program demonstrates use of structs.
*
* Notes:
*   The program reads age ranges and rates from a text file. See named constants.
*   The program can produce some unnecessary output to give clues as to what it's doing.
*
* History:
*   2020-10-11 Jesse Black  Adapt County Fair to Colossal Cinema
*   2020-11-17 Jesse Black  Adapt County Fair With Functions to use parallel arrays
*   2020-11-23 Randi Bolt   Added getNonNegativeDouble from CC with Functions, and
*                           find rate function
*
* Sources:
*   Past assignments and posted videos
*/

#include <iostream>         // cout and cin and endl
#include <fstream>          // file i/o functions
#include <iomanip>          // setprecision() and fixed


using namespace std;        // so we don't need std:: in front of everything

//define struct
struct priceTier
{
    int lower;              // lower bound of age range
    int upper;              // upper bound of age range
    double price;          // price for this ticket
    string rateName;        // friendly name of this tier
};

const double STATE_TAX_PCT = 6.5;       // state tax, in percent
const int MAX_RATES = 10;               // size of our rate arrays
const string RATE_FILE_NAME = "colossalrates.txt";  // this will be our input file
const double DEFAULT_TICKET_PRICE = 0.0; // if we can't find the right rate, let them for this price
const int BAD_INPUT_FILE = -1;      // error reading input file

        // function prototypes
double getNonNegativeDouble( string prompt );

int loadRates( string filename, priceTier rates[], int maxRanges);

void showRates( priceTier rates[], int nRates );

double findRate( priceTier rates[], int nRates, double age );

    ///////////// MAIN PROGRAM ////////////

int main()
{
    double age = 0.0;       // age of this person
    double cost = 0.0;      // cost for this person
    int nRates = 0;         // number of rates we actually have read.
    bool verbose = 1;       // true means produce more output
    priceTier rates[MAX_RATES];     //an array of this type of struct that holds rate information
    double cost_so_far = 0.00;
    double cost_per_group = 0.0;

    cout << "This program calculates the cost of admission to Colossal Cinema." << endl;
    cout << "Enter 1 for lots of output, 0 for less output: ";
    cin >> verbose;

        // load the rate table from a file
    nRates = loadRates(RATE_FILE_NAME,rates, MAX_RATES);
    if ( nRates <= 0 )
    {
        cout << "unable to load rates from " << RATE_FILE_NAME << endl;
        return BAD_INPUT_FILE;  // end with error code
    }

    if ( verbose )
        cout << nRates << " rates were loaded from " << RATE_FILE_NAME << endl;

        // call a function to display our rate table
    if ( verbose )
        showRates( rates , nRates );

        // now we're ready to total up the cost for a group of patrons

        // a big "cost per group" loop around:
        //    * the age question,
        //    * the decision-making with cost-for-this-person calculation,
        //    * a message indicating the cost for this person,
    cout << "(Use an age of 0 to indicate there are no more persons in this group.)" << endl;

    while ( true ) // group loop
    {
                // you may use your own function to get a non-negative number here
            age = getNonNegativeDouble( "Enter the age of this person: ");
            if ( age <= 0.0 )
            {
                //The "cost per group" loop should exit when the age is zero.
                break;  // break out of the group loop
            }

                // get the cost for a person of this age.
            cost = findRate(rates,nRates,age );

            cout << fixed << setprecision(2);
            cout << "The cost for this person is $" << cost << endl;

            cost_per_group += cost; // add in the cost for this person.
                // a "cost for the group so far" message.
            cout << "The cost for this group so far: $" << cost_per_group << endl;

    } // group loop

        // apply the state tax rate
    cost_per_group *= (1.0 + (STATE_TAX_PCT/100.0));

        // report the result
    cout << "Your cost with tax is $" << fixed << setprecision(2) << cost_per_group << endl;


    return 0;       // pretend all is well.
} // main


        // this function returns a non-negative double.
        // prompt is a message to display to the user
        // if the user enters a negative value, the function will not accept it, it will ask again.
double getNonNegativeDouble( string prompt )
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
} // getNonNegativeDouble

int loadRates( string filename, priceTier rates[], int maxRanges )
{
    ifstream ifile; // this object will be our input file
    int nR = 0;     // number of records (rates) read from the file

    cout << "Loading " << filename << " ..." << endl; // Display the message “Loading” and the name of the file.
    ifile.open( filename );      // open the input file

        // Check if the file opened successfully.
	if ( ! ifile.is_open()) // if the input file is not open ...
    {
		cout << "Unable to open input file " << filename << endl; //could use c error
		 // get out of this function and return a negative value as an indicator of badness.
		return -1;
	} // check for open failure

        // read data from the file
    int nRates = 0; // number of rows read
    for ( int i=0; i<nRates; ++i )
    {
        ifile >> rates[nRates].lower >> rates[nRates].upper >> rates[nRates].price >> rates[nRates].rateName;
        ifile.ignore(1000,'\n'); // ignore the rest of the line
        if ( ifile.good() )
            ++nRates; // we've successfully read one more row of data.
        else
            break;  // the read operation did not succeed, so give up.
    } // for


    cout << "retrieved " << nR << " rates from " << filename << endl;
    ifile.close();

    return nRates;
} // loadRates


        // this function displays the age ranges, costs, and names.
        // lower is an array which holds the lower limit of each age range
        // upper is an array which holds the upper limit of each age range
        // rate is an array which holds the cost for this age range
        // rateName is an array which holds a human-readable name for this age range
        // nRates is the actual number of ranges which have been loaded into the arrays.
void showRates( priceTier rates[], int nRates )
{
    cout << "Ticket Prices:" << endl;
    cout << "Min Age  Max Age    Rate  Ticket" << endl;
    for ( int i=0; i<nRates; i++ )
    {
        cout << fixed << setprecision(2);
        cout << setw(7) << rates[nRates].lower << setw(9) << rates[nRates].upper << setw(8) << rates[nRates].price << "  " << rates[nRates].rateName << endl;
    } // for
    cout << endl;
} // showRates


        // this function finds the first range which contains the given age.
        // lower is an array which holds the lower limit of each age range
        // upper is an array which holds the upper limit of each age range
        // rate is an array which holds the cost for this age range
        // rateName is an array which holds a human-readable name for this age range
        // nRates is the actual number of ranges which have been loaded into the arrays.
        // age is the age of the person for whom we're trying to find the rate
double findRate( priceTier rates[], int nRates, double age )
{
    double thisRate = DEFAULT_TICKET_PRICE;  // if we don't find a rate in the table, charge this amount.
    double cost = 0;

    for ( int i=0; i<nRates; i++ )
    {   // if the age is at least the lower end of this range ...
        // and the age is less than the upper end of this range ...
        if (age < rates[nRates].upper and age >= rates[nRates].lower)
        { // then announce the name of this range and remember the cost of this ticket
            cout << "Age " << age << " gets a " << rates[nRates].rateName << " ticket." << endl;
            cost = rates[nRates].price;
        }

    } // for
    return cost;    // return the cost of this ticket.
} // findRate

