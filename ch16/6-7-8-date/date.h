// class Date
//        -- from _C++20 for Lazy Programmers_

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
    Date(int theDay=1, int theMonth=1, int theYear=1) :
       day_(theDay), month_(theMonth), year_(theYear)
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
           day_  (otherDate.day_  ),
           month_(otherDate.month_),
           year_ (otherDate.year_ )
    {
    }

    // Access functions
    int day        () const { return day_;   }
    int month      () const { return month_; }
    int year       () const { return year_;  }

    int totalDays() const; // convert to total days since Dec 31, 1 BC

    void print (std::ostream& out = std::cout) const
    {
        out << day_ << '-' << month_ << '-' << year_;
    }

private:
    int day_;
    int month_;
    int year_;

    void normalize  ();
};
#endif //DATE_H
