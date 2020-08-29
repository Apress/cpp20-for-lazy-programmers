// Testing Vector with concepts
//      -- from _C++ for Lazy Programmers_

#ifndef __cpp_concepts
#warning "This compiler does not support concepts."
#endif

#include <iostream>
#include <cassert>
#include <string>
#include "vector.h"

using namespace std;

int main ()
{  
    struct A { A& operator= (const A&) = delete; }; // Two simple classes
    struct B { B() {};                           };

    Vector<int> someInts;       // No problem
    //Vector<A> a;              // Nope: no operator=
    //Vector<B> b1, b2;         // Nope: no operator==

    return 0;
}

template <typename T>
concept Printable = requires (std::ostream& out, const T& t)
{
    out << t;
};

template <Printable T>
void emphaticPrint (const T& t) { cout << '*' << t << '*'; }

void testPrintableConcept ()
{
    struct C {};           // Something that can't be printed

    emphaticPrint (2);     // No problem
    //emphaticPrint (C()); // Nope: C isn't printable
};

