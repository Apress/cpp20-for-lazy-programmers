//class Date
//       -- from _C++20 for Lazy Programmers_

#ifndef DATE_H
#define DATE_H

#include <iostream>

enum class Month { JANUARY=1, FEBRUARY, MARCH, APRIL, MAY, JUNE, 
                   JULY, AUGUST, SEPTEMBER, OCTOBER, DECEMBER};

bool isLeapYear   (int year);
int  daysPerYear  (int year);
int  daysPerMonth (int month, int year);// Have to specify year,
                                        // in case month is FEBRUARY
                                        //  and we're in a leap year
class Date
{
public:
    Date(int theDays=1, int theMonths=1, int theYears=1) :
       days_(theDays), months_(theMonths), years_(theYears)
    {
        normalize();
    }
    // Because of its default parameters, this 3-param
    //  ctor also serves as a conversion ctor
    //  (when you give it one int)
    //  and the default ctor (when you give it nothing)
    
    // Default is chosen so that the default day 
    //  is Jan 1, 1 A.D.
    
    Date(const Date& otherDate) : // copy ctor
           days_  (otherDate.days_  ),
           months_(otherDate.months_),
           years_ (otherDate.years_ )
    {
    }

    // Access functions
    int days        () const { return days_;   }
    int months      () const { return months_; }
    int years       () const { return years_;  }

    int totalDays() const; // convert to total days since Dec 31, 1 BC

    void print (std::ostream& out = std::cout) const
    {
        out << days_ << '-' << months_ << '-' << years_;
    }

private:
    int days_;
    int months_;
    int years_;

    void normalize  ();
};

#endif //DATE_H
