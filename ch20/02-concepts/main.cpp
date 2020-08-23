//Utterly useless program that uses
// a function template with a concept
//      -- from _C++20 for Lazy Programmers_

#ifndef __cpp_concepts
#warning "This compiler does not support concepts."
#endif

#include <concepts> 

template <typename T, typename U>
requires std::swappable_with<T&, U&>
void mySwap (T& t, U& u)
{
    T temp = t; t = u; u = temp;
}

class A {};
class B {};

int main ()
{
    int x, y;
    mySwap (x, y);
    //mySwap (2, 3); // won't compile -- can't swap literals

    //A a; B b;
    //mySwap (a,b);  // won't compile -- A and B aren't swappable
    
    return 0;
}
