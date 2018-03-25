/*********************************************************************
** Program name: main.cpp
** Author: Alexandra Carper
** Date: 03/09/2018
** Description: This program displays a menu, retrieves user input,
 *              and either tests a buffer or creates a palindrome.
 *              To test the buffer, the user enters the percent
 *              chance that a value is pushed into the queue and
 *              the percent chance that a value is popped out of the
 *              queue. In each round, the program then generates a
 *              random value to be pushed and random numbers to
 *              compare against the user entered percentages. The
 *              program then either pushes a value, pops a value, or
 *              does neither. Then, the buffer, its length, and its
 *              average length is printed. To create a palindrome,
 *              the user enters a string, which is converted into
 *              a stack of characters, and characters are added
 *              to the stack as they are popped off. The palindrome
 *              is then printed to the screen.
*********************************************************************/

#include <iostream>
#include <stack>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <string>
#include <list>
#include <vector>
#include "menu.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::queue;
using std::stack;
using std::list;
using std::string;
using std::vector;
using std::getline;


int validateInput(int max, int min);
int generateRandom(int min, int max);
string createPalindrome(string palindrome);
void printQueue(queue <int, list<int> > q);
void printLength(queue <int, list<int> > q);
void printAverage(double average);

int main()
{
    //Seed time
    srand(time(NULL));

    //Prompt for first choice
    cout << "Welcome! Would you like to test the buffer or create a palindrome?" << endl;
    //Display menu and retrieve input
    int choice = menu();
    while(choice != 3)
    {
        //If user chooses to test buffer
        if(choice == 1)
        {
            //Initialize values for pushed and popped
            int pushed;
            int popped;
            //Initialize average to zero
            double avg = 0;
            //Initialize previous average
            double avg_prev;

            //Prompt for number of rounds
            cout << "How many rounds would you like to play?" << endl;
            //Validate input, initialize rounds
            int rounds = validateInput(100, 1);

            //Prompt for percent chance append
            cout << "Please enter the percent chance to put a randomly generated " << endl;
            cout << "number at the end of the buffer: " << endl;
            //Validate input, initialize percentAppend
            int percentAppend = validateInput(100, 0);


            //Prompt for percent chance remove
            cout << "Please enter the percent chance to take out a randomly generated " << endl;
            cout << "number at the front of the buffer: " << endl;
            //Validate input, initialize percentRemove
            int percentRemove = validateInput(100, 0);

            cout << endl;
            cout << "Starting simulation..." << endl;


            //Create queue with list base
            queue <int, list<int> > iQueue;
            //Create temp queue with list base
            queue <int, list<int> > temp;

            //For each round
            for(int i = 1; i <= rounds; i++)
            {
                //Display round number
                cout << "Round " << i << ": " << endl;

                pushed = 0;
                popped = 0;
                //Set previous round's average to average
                avg_prev = avg;

                //Initialize N to random number between 1 and 1000
                int N = generateRandom(1, 1000);
                //Initialize append to random number between 1 and 100
                int append = generateRandom(1, 100);

                cout << "Random number append: " << append << endl;

                //If append is less than or equal to percent user entered
                if(append <= percentAppend)
                {
                    //Push N into queue
                    iQueue.push(N);
                    //Increment pushed
                    pushed++;
                }

                //Initialize remove to random number between 1 and 100
                int remove = generateRandom(1, 100);

                cout << "Random number remove: " << remove << endl;

                //If remove is less than or equal to percent user entered
                if(remove <= percentRemove && !iQueue.empty())
                {
                    //Pop from queue
                    iQueue.pop();
                    //Increment popped
                    popped++;
                }

                //Fill temp with queue values
                temp = iQueue;

                //Indicate if a value was pushed or popped
                if(pushed && popped)
                {
                    cout << "Value pushed and popped.\n";
                    cout << N << " pushed.\n";
                }
                else if(pushed)
                {
                    cout << N << " pushed.\n";
                }
                else if(popped)
                {
                    cout << "Value popped.\n";
                }
                else
                {
                    cout << "No values pushed or popped.\n";
                }

                //Print queue
                printQueue(temp);
                //Print length of buffer
                printLength(iQueue);
                //Calculate average
                avg = (avg_prev * (i - 1) + iQueue.size()) / i;
                //Print average
                printAverage(avg);

            }
            choice = menu();
        }
        else if(choice == 2)
        {
            //Initialize string p
            string p;
            //Prompt user for string
            cout << "Please enter a string to create a palindrome: " << endl;
            cin.clear();
            cin.ignore();
            //Input string
            getline(cin, p);
            //Print palindrome
            cout << "Palindrome of " << p << " is " << createPalindrome(p) << endl;

            choice = menu();
        }
    }

    if(choice == 3)
    {
        cout << "Goodbye!" << endl;
    }

    return 0;
}

/*********************************************************************
** Description: Function to validate input
*********************************************************************/
int validateInput(int max, int min)
{
    //Initialize input variable
    int input;
    //Input validator
    bool validInput = false;
    //While input is not valid
    while(!validInput)
    {
        //Input variable
        cin >> input;

        //If wrong type
        if(cin.fail())
        {
            cout << "Error! Please enter a valid integer!" << endl;
            cin.clear();
            cin.ignore();
        }
            //If wrong value
        else if(input < min || input > max)
        {
            cout << "Error! Please enter a valid integer!" << endl;
            cin.clear();
            cin.ignore();
        }
            //If input valid
        else
        {
            //Don't return through loop
            validInput = true;
            //Return input from function
            return input;
        }
    }

}

/*********************************************************************
** Description: Function to generate random number
*********************************************************************/
int generateRandom(int min, int max)
{
    //Initialize number to random number between max and min
    int number = (rand() % max) + min;

    if(number >= min && number <= max)
    {
        return number;
    }
}

/*********************************************************************
** Description: Function to create palindrome
*********************************************************************/
string createPalindrome(string palindrome)
{
    //Create a vector of characters from the string
    vector<char> vect(palindrome.begin(), palindrome.end());

    //Create a stack from the vector and add
    //values of original string sequentially to stack
    stack<char, vector<char> > iStack(vect);

    //While the stack is not empty
    while(!iStack.empty())
    {
        //Add top character to palindrome
        palindrome += iStack.top();
        //Pop off top character
        iStack.pop();
    }

    //Return full palindrome
    return palindrome;
}

/*********************************************************************
** Description: Function to print queue
*********************************************************************/
void printQueue(queue <int, list<int> > q)
{
    cout << "Buffer: ";
    //While queue is not empty
    while(!q.empty())
    {
        //Print front character
        cout << q.front() << " ";
        //Pop character from queue
        q.pop();
    }
    cout << endl;
}

/*********************************************************************
** Description: Function to print length of queue
*********************************************************************/
void printLength(queue <int, list<int> > q)
{
    cout << "Length of buffer: " << q.size() << endl;
}

/*********************************************************************
** Description: Function to print average of queue
*********************************************************************/
void printAverage(double average)
{
    cout << "Average length of buffer: " << average << endl;
    cout << endl;
}
