// A program to print an appointment time, and demo the Date class
//  ...doesn't do that much (yet)
//    -- from _C++20 for Lazy Programmers_

#include <iostream>

using namespace std;

class Date
{
public:
    Date (int theDay, int theMonth, int theYear); // constructor prototype

    void print (std::ostream& out);

private:
    int day_;
    int month_;
    int year_;
};

Date::Date (int theDay, int theMonth, int theYear) : // ...constructor body
    day_ (theDay), month_ (theMonth), year_ (theYear)
    // theDay is the parameter passed into the Date constructor
    //   function.  day_ is the member that it will initialize.
{
}

void Date::print (std::ostream& out) 
{
    out << day_ << '-' << month_ << '-' << year_;
}

int main ()
{
    Date appointment (31,1,2595); 

    cout << "I'll see in you in the future, on ";
    appointment.print (cout);
    cout << " . . . pencil me in!\n";

    return 0;
}
