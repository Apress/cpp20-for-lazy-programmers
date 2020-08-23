//A "driver" program to test the Date class
//  -- from _C++20 for Lazy Programmers_

#include <iostream>
#include "date.h"

using namespace std;

int main ()
{
    Date t (5,11,1955); // Test the 3-int ctor

    // ... and print
    cout << "This should print 5-11-1995:\t";
    t.print (cout);
    cout << endl;

    // Test access functions                     
    if (t.days () != 5 || t.months () != 11 || t.years () != 1955)
    {
        cout << "Date t should have been 5-11-1955, but was ";
        t.print ();
        cout << endl;
    }

    Date u = t;         // ...the copy ctor
    if (u.days () != 5 || u.months () != 11 || u.years () != 1955)
    {
        cout << "Date u should have been 5-11-1955, but was ";
        u.print ();
        cout << endl;
    }

    const Date DEFAULT; // ...and the default ctor
                        // I do consts to test const functions
    if (DEFAULT.days  () != 1 || DEFAULT.months () != 1 || 
        DEFAULT.years () != 1)
    {
        cout << "Date v should have been 1-1-1, but was ";
        DEFAULT.print ();
        cout << endl;
    }

    // ...and total days
    constexpr int DAYS_FOR_JAN1_5AD = 1462; // I found this number myself 
                                            //   with a calculator
    Date Jan1_5AD(1, 1, 5);
    if (Jan1_5AD.totalDays () != DAYS_FOR_JAN1_5AD)
        cout << "Date Jan1_5AD should have had 1462 days, but had "
             << DAYS_FOR_JAN1_5AD << endl;      

    // Test normalization
    const Date JAN1_2000 (32, 12, 1999);
    if (JAN1_2000.days  () != 1 || JAN1_2000.months () != 1 || 
        JAN1_2000.years () != 2000)
    {
        cout << "Date JAN1_2000 should have been 1-1-2000, but was ";
        JAN1_2000.print ();
        cout << endl;
    }

    cout << "If no errors were reported, "
         << " it looks like class Date works!\n";

    return 0;
}
