//Class Manager
//      -- from _C++20 for Lazy Programmers_

#ifndef MANAGER_H
#define MANAGER_H

#include "employee.h"

using Meeting = std::string; 

class Manager: public Employee
{
public:
    Manager ();
    Manager (const Manager&) = delete;
    Manager (const std::string& theFirstName, 
             const std::string& theLastName,
             const Date&   theDateHired,
             int           theSalary);
    ~Manager () { if (schedule_) delete [] schedule_; }

    Manager& operator= (const Manager&) = delete;

    void hire (Employee& foo) const { foo.start (); }
    void fire (Employee& foo) const { foo.quit  (); }
    void laugh()              const
    {
        std::cout << firstName() << " says:  hee-hee!\n";
    }
    
    void torment (Employee&) const;

private:
    Meeting*    schedule_;
    int         howManyMeetingsOnSchedule_;
    void        copy (const Manager& other); 
};

#endif //MANAGER_H
