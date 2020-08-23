//List class tester with iterator, const_iterator
//      -- from _C++20 for Lazy Programmers_

#include <iostream>
#include <cassert>
#include <string>
#include "list.h"

using namespace std;

/*
#ifdef __cpp_concepts   //This is commented out so the program will
                        //compile and run; uncomment to test concepts
                        //Ensures that if a base type lacks any 
                        //required feature, you can't use it.

struct A
{
    A();
    A& operator= (const A&);
    bool operator== (const A&) const;
};
ostream& operator<< (ostream&, const A&);

List<A> As; //no problem

struct B
{
    B() = delete;
    B& operator= (const B&);
    bool operator== (const B&) const;
};
ostream& operator<< (ostream&, const B&);

List<B> Bs; //won't work: no default ctor

struct C
{
    C();
    C& operator= (const C&);
};
ostream& operator<< (ostream&, const C&);

List<C> Cs; //won't work: no operator==

struct D
{
    D();
    D& operator= (const D&) =delete;
    bool operator== (const D&) const;
};
ostream& operator<< (ostream&, const D&);

List<D> Ds; //won't work: no operator=

struct E
{
    E();
    E& operator= (const E&);
    bool operator== (const E&) const;
};

List<E> Es; //won't work: no ostream& << 
#endif
*/

int main ()
{
        //Some functions left as exercises (==, front) are
        // needed before this will compile
 
    /*
    //Test default ctor, size, empty, print, push_front, front
    List<int> L;
    assert(L.size() == 0); assert(L.empty());
    for (int i = 0; i < 4; ++i) 
    { 
         L.push_front(i); assert(L.front() == i); 
    }
    assert(L.size() == 4);  assert(!L.empty());

    //Test copy ctor, operator=, operator==, pop_front, print
    List <int> M = L;       assert(M == L); 
    List <int> N; N = M;    assert(N == L);
    cout << "This should be [3 2 1 0 ]: " << L << endl;
    M.pop_front(); assert(M.front() == 2); assert(!(M == L)); 

    cout << "If that's right and there were no crashes, "
         << "looks like the list is working.\n";
    */

    return 0;
}
