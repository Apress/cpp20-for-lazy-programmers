// Class Employee
//      -- from _C++20 for Lazy Programmers_

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string>
#include "date.h" 

class Employee
{
public:
    Employee();
    Employee (const Employee&) = delete;
    Employee (const std::string& theFirstName,
              const std::string& theLastName,
              const Date& theDateHired, int theSalary);

    Employee& operator= (const Employee&) = delete;

    void print(std::ostream&) const;

    // access functions
    const std::string& firstName () const { return firstName_;   }
    const std::string& lastName  () const { return lastName_;    }
    const Date&        dateHired () const { return dateHired_;   }
    int   salary                 () const { return salary_;      }
    bool  isOnPayroll            () const { return isOnPayroll_; }
	int   badPerformanceReviews  () const 
    {
        return badPerformanceReviews_; 
    }

    void  quit                   ()       { isOnPayroll_ = false;}
    void  start                  ()       { isOnPayroll_ = true; }
    void  meetWithBoss           () { ++badPerformanceReviews_;  }

private:
    std::string firstName_, lastName_;
    Date dateHired_;
    int  salary_;
    bool isOnPayroll_;
    int  badPerformanceReviews_;
};

inline
std::ostream& operator<< (std::ostream& out, const Employee& foo)
{
    foo.print (out); return out;
}

#endif //EMPLOYEE_H
