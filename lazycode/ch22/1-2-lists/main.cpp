//List class tester with iterator, const_iterator
//      -- from _C++20 for Lazy Programmers_

#include <iostream>
#include <cassert>
#include <string>
#include "list.h"

using namespace std;

//used for testing move semantics; see below
template<typename T>
List<T> testMove(const T& foo) { List<T> result; result.push_front (foo); return result; }

int main ()
{
        // Some functions left as exercises (==, front) are
        //  needed before this will compile
  
    // Test default ctor, size, empty, print, push_front, front
    List<int> L;
    assert (L.size() == 0); assert (L.empty());
    for (int i = 0; i < 4; ++i) 
    { 
        L.push_front(i); assert (L.front() == i); 
    }
    assert (L.size() == 4);  assert (!L.empty());

    // Test copy ctor, operator=, operator==, pop_front, print
    List <int> M = L;       assert (M == L); 
    List <int> N; N = M;    assert (N == L);
    cout << "This should be [3 2 1 0 ]: " << L << '\n';
    M.pop_front(); assert (M.front() == 2); assert (M != L); 

    L = testMove(0); 
           // You can use the debugger to verify you're using move functions, 
           //   if that's your plan

    cout << "If that's right and there were no crashes, "
         << "looks like the list is working.\n";

    return 0;
}
