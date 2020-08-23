//Program to demonstrate stack, with exceptions
//      -- from _C++20 for Lazy Programmers_

#include <iostream>
#include "stack.h"

using namespace std;

char getAnswer (const char* question); // Ask question, get a (char) answer
void destroyAndPrint (Stack&);         // Take everything off stack, and
                                       // print what you see

int main ()
{
    Stack S;
    bool isDone = false;

    while (!isDone)
    {
        cout << "You can p(U)sh onto the stack, "
                "see the (T)op, (P)op, or (Q)uit.\n";
        char answer = getAnswer ("What do you want to do?");

        try 
        {
            string thingToPush;

            switch (toupper (answer))
            {
            case 'U':   cout << "Enter a character to push:  ";
                cin  >> thingToPush;
                S.push (thingToPush);
                break;
            case 'T':   cout << "The top of the stack is a "
                             << S.top () << endl;
                break;
            case 'P':   cout << "You just popped a "
                             << S.pop () << endl;
                break;
            case 'Q':   isDone = true;                                            
                break;
            default: cout << "Please enter U, T, P, or Q.\n";
            }
        }
        catch (const Stack::UnderflowException&)
        {
            cout << "Error in main:  stack underflow.\n"; 
        }
        catch (const Stack::OverflowException&)
        {
            cout << "Error in main:  stack overflow.\n";
        }
    }

    cout << "This is what was on the stack:  ";
    destroyAndPrint (S);

    return 0;
}

char getAnswer (const char* question) // Ask question, get a (char) answer
{
    char answer;

    cout << question << ' ';
    cin  >> answer;

    return answer;
}

void destroyAndPrint (Stack& foo)   // Take everything off stack,
                                    //   print what you see
{
    while (! foo.empty()) cout << foo.pop () << ' ';
    cout << '\n';
}
