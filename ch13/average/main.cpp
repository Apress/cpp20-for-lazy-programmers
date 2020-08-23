//Program to get an average
//      -- from _C++20 for Lazy Programmers_

#include <iostream>

using namespace std;

int main ()
{
    //initialize total and howMany
	double total = 0.0;
	int  howMany = 0;

    while (cin)              //while there are numbers in file
    {
        int num; cin >> num; //read one in

        if (cin)             //still no problems with cin, right?
        {
            total += num;    //keep running total
            ++howMany;
        }
    }

    //print average
    cout << "Average is " << total / howMany << '\n';
 
    return 0;
}
