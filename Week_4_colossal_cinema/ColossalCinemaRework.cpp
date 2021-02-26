/*
*   This program calculates the cost of admission to the Colossal Cinema
*   Randi Bolt, October 16, 2020
*   Sources: Jesse Black: Lectures October 12, October 14, October 19, and October 21
*/

#include <iostream>
#include <iomanip>                  // allows us to use setprecision(), fixed, and showpoint

using namespace std;

int main ()
{
    //variables declaring
    double age;                            // double b/c 1.5 was an example age
    double ticketPreTax;                   // ticket place holder before tax
    double ticketTaxed;                    // ticket place holder after tax

    const double toddlerRate = 1.00;            // toddler ticket price
    const double childRate = 12.00;             // child ticket price
    const double standardRate = 20.00;          //standard ticket price
    const double discount = 0.1;           // 10% discount, can be changed here
    const double tax = 0.065;              // 6.5% tax, can be changed here

    cout << fixed << showpoint << setprecision(2);          // fixed # to right of decimal, and shows the decimal point to 2 places

    //tells the user what the program does
    cout << "This program calculates the cost of admission to Colossal Cinema." << endl;    // greets the user and tells them about the program

    //asks the user for their age, and verifies that age back to the user
    cout << "What is the age (in years) of this person? ";                                  // asks the user to input their age
    cin >> age;                                                                             // saves their input into age variable
    cout << "Hmmm ... " << age <<  " years old ... Let me check my rate sheet." << endl;     // tells the user the age they input

    //if/else statement
    if( age < 2 )                                           // if the user is less than 2 years old
    {
        cout << "What a cutie you have there!" <<endl;      // compliments the baby
        ticketPreTax = toddlerRate;                                   // calculates Ticket Price $1.00
    }

    else if (2 <= age and age < 10)                         // if the user is greater than or 2 years old AND less than 10 years old
    {
        ticketPreTax = childRate;                                 // calculates Ticket Price $12.00
    }

    else if (10 <= age and  age < 60 )                      //if the user is greater than or 10 years old AND less than sixty years old
    {
        ticketPreTax = standardRate ;                                 // calculates Ticket Price $20.00
    }
    else                                                    // if the user is 60 years old, or older
    {
        cout <<"You qualify for the senior discount!" << endl;      // tells the user they qualify for the senior discount
        ticketPreTax = standardRate - ( standardRate * discount );                      // calculates the discounted senior ticket price
    }

    ticketTaxed = ticketPreTax + (ticketPreTax*tax);                // calculates ticket price with tax

    cout << "Your cost with tax is $" << ticketTaxed <<  endl;      // tells the user their ticket price

 return 0;                                                          // return value that indicates all is well
}
