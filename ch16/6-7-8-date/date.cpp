//class Date -- functions
//  -- from _C++20 for Lazy Programmers_

#include "date.h"

bool isLeapYear (int year)
{
    // If a year is divisible by 4, it's a leap year
    // Except if it's also divisible by 100, it's not
    // Except if it's also divisible by 400, it is
    // Not simple, but there it is

    bool result = false;

    if      (year %   4) result = false; 
    else if (year % 100) result = true;  
    else if (year % 400) result = false; 
    else result = true;                  

    return result;
}

int daysPerYear (int year)
{
    if (isLeapYear (year)) return 366; else return 365;
}

int daysPerMonth (int month, int year)
{
    // for convenience, I skip the 0th entry and start with month 1
    static int DAYS_PER_MONTH [] = {0,
                                    31, 28, 31,                 
                                    30, 31, 30,    
                                    31, 31, 30,    
                                    31, 30, 31 };  
    // Thirty days hath November,
    // April, June, and September,
    // All the rest have thirty-one,
    // Except February the only one
    // Which leap years change in its time
    // From twenty-eight to twenty-nine.

    if (month == int (Month::FEBRUARY) && isLeapYear (year)) return 29;
    else return DAYS_PER_MONTH [month]; 
}

void Date::normalize ()         // puts Date into form such that 
    // days <= days for that month,
    // months <= 12,
    // and months and years are adjusted
    // accordingly
{   
    days_ = totalDays ();

    // keep taking out year's worths of days
    //  till less than 365 (or 366)...
    for (years_ = 1; days_ > daysPerYear (years_); ++years_)
        days_ -= daysPerYear (years_);
        
    // keep taking out month's worth of days
    //  till less than those in current month...
    for (months_= 1; days_ > daysPerMonth (months_, years_); ++months_)
        days_ -= daysPerMonth (months_, years_);
}

int Date::totalDays () const
{
    int totalDays = 0;

    for (int i = 1; i < years_; ++i)    // accumulate years' days
        totalDays += daysPerYear (i);

    for (int m = 1; m < months_; ++m)   // then months'
        totalDays += daysPerMonth (m, years_);

    totalDays += days_;                 // then remaining days

    return totalDays;
}
