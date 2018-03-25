#include <iostream>
#include "menu.hpp"

using std::cin;
using std::cout;
using std::endl;

int menu()
{
    cout << "Please choose an option: " << endl;
    cout << "1. Test the buffer\n";
    cout << "2. Create a palindrome\n";
    cout << "3. Quit\n";

    int choice;
    bool validInput = false;

    while(!validInput)
    {
        cin >> choice;

        if(cin.fail())
        {
            cout << "Error! Please enter a valid option!" << endl;
            cin.clear();
            cin.ignore();
        }
        else if(choice < 1 || choice > 3)
        {
            cout << "Error! Please enter a valid option!" << endl;
            cin.clear();
            cin.ignore();
        }
        else
        {
            validInput = true;
            return choice;
        }
    }

}