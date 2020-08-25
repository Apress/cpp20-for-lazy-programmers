// Example with a Vector of int
//      -- from _C++20 for Lazy Programmers_

#include <iostream>
#include <cassert>
#include "vector.h"

using namespace std;

int main ()
{
    Vector<int> V;

    for (int i = 1; i < 11; ++i) V.push_back (i);

    cout << "Can you count to 10?  The Count will be so proud!\n";

    for (unsigned int i = 0; i < V.size (); ++i) cout << V[i] << ' ';
    cout << '\n';

    return 0;
}

