// Test initializer_list ctor/= for Vector
//      -- from _C++20 for Lazy Programmers_

#include <iostream>
#include <cassert>
#include "vector.h"

using namespace std;

int main ()
{
    // Try another base type, and test initializer_list ctor and =
    Vector<int> V = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }; 

    cout << "1 to 10 I hope: ";
    for (int i = 0; i < 10; ++i) cout << V[i] << ' ';
    cout << '\n';

	Vector<int> U; U = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	assert(V == U);

    return 0;
}

