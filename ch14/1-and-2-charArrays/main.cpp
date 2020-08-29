// Program to illustrate a few char-array functions
//    -- from _C++20 for Lazy Programmers_

#include <iostream>

using namespace std;

constexpr int MAX_LINE_LENGTH=255;

bool         getYOrNAnswer (const char question[]);
unsigned int myStrlen      (const char str[]);

int main ()
{
    bool letsRepeat;                        // keep going?

    static char line [MAX_LINE_LENGTH];     // a line to read in    
    
    do
    {
        cout << "Enter a line and I'll tell you how long it is.\n";
        cout << "Enter: "; cin.getline (line, MAX_LINE_LENGTH);
        cout << "That's " << myStrlen (line) << " characters.\n";
        
        letsRepeat = getYOrNAnswer ("Continue (Y/N)? ");
    }
    while (letsRepeat);
    
    return 0;
}

bool getYOrNAnswer (const char question[])
{
    char answer;

    do
    {
        cout << question;
        cin  >> answer;
        answer = toupper (answer);
    }
    while (answer != 'Y' && answer != 'N');

    cin.ignore (MAX_LINE_LENGTH, '\n'); // dump rest of this line

    return answer == 'Y';
}

unsigned int myStrlen (const char str[]) 
                                 // "strlen" is the conventional
                                 //     name for this function
{
    int where = 0;

    while (str[where] != '\0')   // count the chars
        ++where;

    return where;                // length is final "where"
}
