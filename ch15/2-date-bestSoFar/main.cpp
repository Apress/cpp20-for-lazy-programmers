// A program to test the Date class
//    -- from _C++20 for Lazy Programmers_

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
    Date (int theDay=1, int theMonth=1, int theYear=1);
                              // Because of default parameters,
                              //  this serves as constructor taking 3 ints;
                              //  a new one taking day and month;
                              //  the conversion from int constructor;
                              //  and the default constructor
    
    Date (const Date&);       // copy constructor

    void print (std::ostream& out = std::cout) const;

    int totalDays   () const; // total days since Dec 31, 1 B.C.
private:
    int day_;
    int month_;
    int year_;

    void normalize  ();
};

Date::Date (int theDay, int theMonth, int theYear) :
    day_ (theDay), month_ (theMonth), year_ (theYear)
{
    normalize ();
}

Date::Date (const Date& other) :
    day_ (other.day_), month_ (other.month_), year_ (other.year_)
{
}

void Date::print (std::ostream& out) const 
{
    out << day_ << '-' << month_ << '-' << year_;
}

bool isLeapYear (int year)
{
    // If a year is divisible by 4, it's a leap year
    // Except if it's also divisible by 100, it's not
    // Except if it's also divisible by 400, it is
    // Not simple, but there it is

    bool result = false;

    if (year % 4   == 0) result = true;
    if (year % 100 == 0) result = false;
    if (year % 400 == 0) result = true;          

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
                                // day <= day for the month,
                                // month <= 12,
                                // and month and year are adjusted
                                // accordingly
{   
    day_ = totalDays ();

                                // keep taking out year's worths of days
                                //  till less than 365 (or 366)...
    for (year_ = 1; day_ > daysPerYear (year_); ++year_)
        day_ -= daysPerYear (year_);
        
                                // keep taking out month's worth of days
                                //  till less than those in current month...
    for (month_= 1; day_ > daysPerMonth (month_, year_); ++month_)
        day_ -= daysPerMonth (month_, year_);
}

int Date::totalDays () const
{
    int totalDays = 0;

    for (int i = 1; i < year_; ++i)    // accumulate years' days
        totalDays += daysPerYear (i);

    for (int m = 1; m < month_; ++m)   // then months'
        totalDays += daysPerMonth (m, year_);

    totalDays += day_;                 // then remaining days

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

    Date d (21, 12, 2000);          // using our old constructor...
    Date e = d;                     // e is now exactly the same as d
    Date f;                         // now one with no arguments
    Date dateArray [MAX_DATES];     // still no arguments
    Date g (22000);                 // 22,000 days, nearly a lifetime

    cout << "This should print 26-3-61 with lots of *'s:\n";
    fancyDisplay (22000);           // tests conversion-from-int constructor

    return 0;
}
