// Class Employee
//      -- from _C++20 for Lazy Programmers_

#include "employee.h"

using namespace std;

Employee::Employee() :
    salary_(0), isOnPayroll_(false), badPerformanceReviews_(0)
{
}

Employee::Employee (const string& theFirstName, const string& theLastName, 
                    const Date& theDateHired, int theSalary) :
    firstName_ (theFirstName), lastName_ (theLastName),
    dateHired_ (theDateHired),
    salary_ (theSalary), isOnPayroll_ (false),
    badPerformanceReviews_ (0)
{
}

void Employee::print (ostream& out) const
{
    out << firstName() << ' ' << lastName()
        << ", salary: " << salary()
        << "\nHired: ";
    dateHired().print(out);
    out << "\nIs ";
    if (! isOnPayroll()) out << "NOT ";
    out << "on payroll.  ";
    out << "Bad reviews:  " << badPerformanceReviews() << '\n';
}
