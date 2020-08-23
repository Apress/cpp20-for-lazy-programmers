// Test List::iterator and some other List functions
//    -- from _C++20 for Lazy Programmers_

#include <iostream>
#include <cassert>
#include <string>
#include "list.h"

using namespace std;

int main ()
{
    // Test default ctor, size, empty, push_front, front
    List<int> L;
    assert(L.size() == 0); assert(L.empty());
    for (int i = 0; i < 4; ++i) 
    { 
        L.push_front(i); assert(L.front() == i); 
    }
    assert(L.size() == 4);  assert(!L.empty());

    // Test copy ctor, operator=, operator==, pop_front, print
    List <int> M = L;       assert(M == L);
    List <int> N; N = M;    assert(N == L);
    cout << "This should be [3 2 1 0 ]: " << N << '\n';
    M.pop_front(); assert(M.front() == 2); assert(!(M == L)); 

	// Test iterator
	// Test begin, end, and iterator's ctor, !=, ++, *, -> 
	List<string>S1; S1.push_front("phrase"); S1.push_front("word"); S1.push_front("three");

	cout << "These words are capitalized: ";
	for (List<string>::iterator i = S1.begin(); i != S1.end(); ++i)
	{
		(*i)[0] = toupper((*i)[0]);     // Verifies that you can change *i
		cout << string(*i) << ' ';
	}
	cout << '\n';

	// Let's compute the average length and verify it's OK
	unsigned int sum1 = 0;
	for (List<string>::iterator i = S1.begin(); i != S1.end(); ++i)
		sum1 += (unsigned int) i->size();
	assert(sum1 / S1.size() == 5);

    cout << "If that's right and there were no crashes, "
         << "looks like the list is working.\n";

    return 0;
}
