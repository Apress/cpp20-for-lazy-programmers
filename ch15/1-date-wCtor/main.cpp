//A program to print an appointment time, and demo the Date class
// ...doesn't do that much (yet)
//  -- from _C++20 for Lazy Programmers_

#include <iostream>

using namespace std;

class Date
{
public:
    Date (int theDays, int theMonths, int theYears); // constructor prototype

    void print (std::ostream& out);

private:
    int days_;
    int months_;
    int years_;
};

Date::Date (int theDays, int theMonths, int theYears) : // ...constructor body
    days_ (theDays), months_ (theMonths), years_ (theYears)
    // theDays is the parameter passed into the Date constructor
    //   function.  days_ is the member that it will initialize.
{
}

void Date::print (std::ostream& out) 
{
    out << days_ << '-' << months_ << '-' << years_;
}

int main ()
{
    Date appointment (31,1,2595); 

    cout << "I'll see in you in the future, on ";
    appointment.print (cout);
    cout << " . . . pencil me in!\n";

    return 0;
}
