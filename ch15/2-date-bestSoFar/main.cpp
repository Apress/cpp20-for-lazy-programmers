//A program to print an appointment time, and demonstrate the Date class
// ...doesn't do that much (yet)
//  -- from _C++20 for Lazy Programmers_

#include <iostream>

using namespace std;

enum class Month {JANUARY=1, FEBRUARY, MARCH, APRIL, MAY, JUNE, 
                  JULY, AUGUST, SEPTEMBER, OCTOBER, DECEMBER};

bool isLeapYear   (int year);
int  daysPerYear  (int year);
int  daysPerMonth (int month, int year);
                              // We have to specify year in case month
                              //  is FEBRUARY and it's a leap year
class Date
{
public:
    Date (int theDays=1, int theMonths=1, int theYears=1);
                              // Because of default parameters,
                              //  this serves as ctor taking 3 ints;
                              //  a new one taking days and months;
                              //  the conversion from int ctor;
                              //  and the default ctor
    
    Date (const Date&);       // copy ctor

    void print (std::ostream& out = std::cout) const;

    int totalDays   () const; // total days since Dec 31, 1 B.C.
private:
    int days_;
    int months_;
    int years_;

    void normalize  ();
};

Date::Date (int theDays, int theMonths, int theYears) :
    days_ (theDays), months_ (theMonths), years_ (theYears)
{
    normalize ();
}

Date::Date (const Date& other) :
    days_ (other.days_), months_ (other.months_), 
    years_ (other.years_)
{
}

void Date::print (std::ostream& out) const 
{
    out << days_ << '-' << months_ << '-' << years_;
}

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
    static const int DAYS_PER_MONTH [] 
                                 = {0,
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

    if (month == int(Month::FEBRUARY) && isLeapYear (year)) return 29;
    else return DAYS_PER_MONTH [month]; 
}

void Date::normalize ()         // puts Date into form such that 
                                // days <= days for the month,
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

void fancyDisplay (const Date& myDate, ostream& out = std::cout)
{
    cout << "*************\n";
    cout << "* "; myDate.print (); cout << " *\n";
    cout << "*************\n";
}

int main () 
{
    constexpr int MAX_DATES = 10;

    Date d (21, 12, 2000);          // using our old ctor...
    Date e = d;                     // e is now exactly the same as d
    Date f;                         // now one with no arguments
    Date dateArray [MAX_DATES];     // still no arguments
    Date g (22000);                 // 22,000 days, nearly a lifetime

    cout << "This should print 26-3-61 with lots of *'s:\n";
    fancyDisplay (22000);           // tests conversion-from-int ctor
    
    return 0;
}
