// Program to do some things with ranged loops
//      -- from _C++20 for Lazy Programmers_

#include <iostream>
#include <vector>
#include <string>
#include <list>
#ifdef __cpp_concepts
#include <concepts>
#endif

using namespace std;

int main ()
{
    // An array of ints -- print it, double it, print it
    int myArray[] = { 0,1,2,3 };
    for (auto i : myArray)  cout << i << ' '; cout << '\n';

    cout << "Let's see that doubled:\n";
    for (auto& i : myArray)  i *= 2; 
    for (auto  i : myArray)  cout << i << ' '; cout << '\n';

    cout << "Printing same sequence 3 times:\n";

    vector<string> myVector = { "Somewhat Competent Boy", "Amazing Girl",
                                "Bug Spray Man", "Wunderkind" };

    // Can specify the base type, like so; or use auto, as below
    for (const string& i : myVector)   // a "range-based" for-loop
        cout << i << ' ';
    cout << '\n';

    // calls copy ctors needlessly...
    for (auto i : myVector) cout << i << ' '; cout << '\n';
    
    // ...doesn't.
    for (const auto& i : myVector) cout << i << ' '; cout << '\n';

    // Bring Somewhat Competent Boy to the front
    list<string> myList = {"Amazing Girl", "Bug Spray Man",
                           "Somewhat Competent Boy", "Wunderkind" };
    for (auto& i: myList)
        if (i.size() > myList.front().size()) // if more than first item
            std::swap(i, myList.front());  //  move i to front
    
    cout << "This should be Somewhat Competent Boy, the longest name: "
        << myList.front() << '\n';

    std::swap(myList.front(), myList.back());

#if defined (__cpp_concepts) && defined (__GNUC__)
                        // VS does concepts, but (at time of writing) not
                        //  this part. But g++10 does
    // for (std::integral auto& i: myVector) i *= 2;
                    // Won't compile because myVector's base type isn't integral
    for (std::integral auto& i: myArray ) i *= 2;
                    // No problem
#endif
    return 0;
}
