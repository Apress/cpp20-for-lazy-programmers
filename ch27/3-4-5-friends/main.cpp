//Program to read in regions from a file, and tell which
//   is furthest north. Illustrates the friend keyword
//       -- from _C++20 for Lazy Programmers_

#include <iostream>
#include <fstream>
#include <vector>
#include "area.h"

using namespace std;

int main ()
{
    vector<Area> myAreas;

    ifstream infile ("areas.txt");
    if (!infile) { cerr << "Can't open file areas.txt.\n"; return 1; }
    while (infile)                // read in Areas
    {
        Area area; infile >> area;
        if (infile) myAreas.push_back (area);
    }

    // find the northernmost Area
    int northernmostIndex = 0;
    for (unsigned int i = 1; i < myAreas.size(); ++i) 
        if (furtherNorthThan (myAreas[i], myAreas[northernmostIndex]))
            northernmostIndex = i;

    // print it
    cout << "The northernmost area is " << myAreas [northernmostIndex] 
         << endl;

    return 0;
}
