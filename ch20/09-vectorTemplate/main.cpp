// Example with a Vector of strings and more
//      -- from _C++20 for Lazy Programmers_

#include <iostream>
#include <cassert>
#include <string>
#include "vector.h"

using namespace std;

int main ()
{
    // Setting up the band...
    Vector<string> FabFour;
    string names[] = { "John","Paul","George","Ringo" };
    constexpr int NUM_BEATLES = 4;

    for (int i = 0; i < NUM_BEATLES; ++i)
        FabFour.push_back (names[i]);

    // Printing them out...
    cout << "The Fab Four: ";
    for (int i = 0; i < NUM_BEATLES; ++i)
        cout << FabFour[i] << ' ';
    cout << endl;

    // Ensuring other base types compile...
    Vector<int> V; for (int i = 0; i < 10; ++i) V.push_back (i);
    Vector<Vector<double>> G1, G2; assert(G1 == G2);

    return 0;
}

