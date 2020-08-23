//Program to calculate the quadratic formula
//   using structured bindings and tuples
//       -- from _C++20 for Lazy Programmers_

#include <iostream>
#include <cmath>    // for sqrt
#include <tuple>    // for make_tuple
#include <cassert>

using namespace std;

// If auto's going to work in main, we need the 
//  function body *above* main. Else there's no way main 
//  can know what type is to be returned

auto quadraticFormula (double a, double b, double c)
{
    int numroots = 0;
    double root1 = 0.0;
    double root2 = 0.0;

    double underTheRadical = b * b - 4 * a*c;
    if (underTheRadical >= 0) // If we have to sqrt a neg #,
                              //  no solution. Otherwise...
    {
        root1 = (-b + sqrt (underTheRadical)) / (2 * a);
        root2 = (-b - sqrt (underTheRadical)) / (2 * a);

        if (root1 == root2) numroots = 1; else numroots = 2;
    }

    return std::make_tuple(numroots, root1, root2);
}

int main ()
{
    // Get user input
    cout << "Enter the a, b, c from ax^2+bx+c = 0: ";
    double a, b, c;  cin >> a >> b >> c;

    // Get the results
    auto[howMany, r1, r2] = quadraticFormula(a, b, c);

    // Print the results
    switch (howMany)
    {
    case 0: cout << "No solution.\n";                     break;
    case 1: cout << "Solution is "   <<r1<<endl;          break;
    case 2: cout << "Solutions are " <<r1<<' '<<r2<<endl; break;
    default:cout << "Can't have "    <<howMany<<" solutions!\n";
    }

    // ...and a little testing of std::get
    std::tuple<int, double, double> myTuple 
                                = std::make_tuple (0, 2.0, 3.0);
    assert(std::get<0> (myTuple) == 0);      // check the 0th value
    std::get<0> (myTuple) = 1;               // set   the 0th value

    assert(myTuple == std::make_tuple (1, 2.0, 3.0));

    return 0;
}

