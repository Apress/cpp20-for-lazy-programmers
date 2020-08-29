// Class Manager
//      from _C++20 for Lazy Programmers_

#include "manager.h"

using namespace std;

Manager::Manager () : schedule_ (nullptr), howManyMeetingsOnSchedule_ (0) 
{
}

Manager::Manager (const string& theFirstName,
                  const string& theLastName, 
                  const Date& theDateHired,
                  int theSalary) :
    Employee (theFirstName, theLastName, theDateHired, theSalary),
    schedule_ (nullptr), howManyMeetingsOnSchedule_ (0)
{
}

void Manager::torment (Employee& victim) const
{
    cout << firstName () << " just tormented "
         << victim.firstName() << "!\n";
}

void Manager::copy (const Manager& other)
{
    schedule_ = new Meeting [other.howManyMeetingsOnSchedule_]; 
    howManyMeetingsOnSchedule_ = other.howManyMeetingsOnSchedule_;

    for (int i = 0; i < howManyMeetingsOnSchedule_; ++i)
        schedule_ [i] = other.schedule_ [i];
}

