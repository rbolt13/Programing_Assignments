// This program prompts the user to enter voltage
// (measured in Volts) and resistance (measured in Ohms),
// to output current(in Amps).
// Randi Bolt, October 11, 2020
// Sources: Jesse Blacks CS-161 Wednesday October 7th, 2020 lecture
//Sources: https://phet.colorado.edu/sims/html/ohms-law/latest/ohms-law_en.html

#include <iostream>
#include <iomanip> // allows us to use setprecision()

using namespace std;

int main()
{
    // variables declaring
    double current = 0.0;
    double resistance = 0.0;
    double voltage = 0.0;

    cout << fixed << showpoint; // fixed # to right of decimal, and shows the decimal point

    cout << setprecision(2) << endl; // sets decimal precision to two places

    // Tells user about the program
    cout << "This program allows the user to enter voltage (in Volts) and resistance (in Ohms)." << endl;
    cout << "Then tells the user the current in Amps." << endl;

   // Program
    cout << "Enter voltage in Volts: "; // asks the user to enter in voltage in volts
    cin >> voltage; // stores that value into 'voltage'
    cout << "Enter resistance in Ohms: "; // asks the user to enter in resistance in ohms
    cin >> resistance; // stores that value into 'resistance'

    current = voltage/resistance; // formula for current

    cout << "The current in Amps: " << current; // tells the user the current in amps

    return 0; // signals all is good
}
