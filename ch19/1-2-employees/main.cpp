//Program to test Manager and Employee classes
//      -- from _C++20 for Lazy Programmers_
#include "manager.h"

using namespace std;

int main ()
{
    static constexpr long int A_MERE_PITTANCE = 1, 
                              OBSCENELY_LARGE_SALARY = 2147483647;

	Employee george ("George P.", "Burdell", Date (10, 3,1885),
                     A_MERE_PITTANCE);
    Employee bob    ("Bob",      "Cratchit", Date (12,25,1843),
                     A_MERE_PITTANCE);
    Manager  alfred ("Alfred E.", "Neumann", Date (10, 1,1952),
                     OBSCENELY_LARGE_SALARY);

	alfred.hire(alfred); alfred.hire(bob);
    alfred.hire(george);                           // Hiring

    alfred.torment (george); alfred.torment (bob); // Torment
	for (int i = 0; i < 10; ++i) bob.meetWithBoss();

    alfred.fire (bob);                             // Firing
	cout << alfred.firstName() << " makes " << alfred.salary () << " per month!\n";

    alfred.laugh();

	cout << "\n\nOur magnificent staff:\n\n";
    cout << alfred << endl;
    cout << george << endl;
    cout << bob    << endl;

    return 0;
}
