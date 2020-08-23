//Program to use find, copy, copy_if, sort, erase, erase_if
//       -- from _C++20 for Lazy Programmers_

#include <vector>
#include <list>
#include <cassert>
#include <iterator> // for ostream_iterator
#include <iostream>
#include <algorithm>

using namespace std;

bool isEven (int i) { return i % 2 == 0; }

#ifdef __cpp_lib_ranges
int main()
{
    // Try out find
    vector<int> digits  = { 9,2,1,7,4,3,8,6,5,11,11,11 };
    auto i = ranges::find(digits, 7);
    assert(i != digits.end()); // 7 should be there!
    assert(*i == 7);

    // Now copy
    vector<int> newContainer;
    ranges::copy(digits, back_inserter(newContainer));
    assert(digits == newContainer);

    // Now sort
    ranges::sort(digits);

    // Now copy if number is even. Moving between containers is fine.
    list<int> evens;
    ranges::copy_if(digits, back_inserter(evens), isEven);

    // Now print using copy function
    cout << "This should be 2 4 6 8: ";
    ranges::copy(evens, ostream_iterator<int>(cout, " "));
    cout << endl;

    // This is a Bad Idea:

    // for (auto i = digits.begin(); i != digits.end(); ++i)
    //     if (isEven(*i))
    //         digits.erase(i);    // erase element referenced by i
    //                             // (different "erase" -- a member of vector)

    // This is better:
      
    // Erase all even #s from digits
    assert(erase_if(digits, isEven) == 4); // shd delete 4 things
    // And all 11's
    assert(erase(digits, 11) == 3);        // shd delete 3 things

    cout << "This should be 1 3 5 7 9: ";
    ranges::copy(digits, ostream_iterator<int>(cout, " "));
    cout << endl;

    return 0;
}
#else
int main()
{
    // Try out find
    vector<int> digits = { 9,2,1,7,4,3,8,6,5,11,11,11 };
    auto i = find(digits.begin(), digits.end(), 7);
    assert(i != digits.end()); // 7 should be there!
    assert(*i == 7);

    // Now copy
    vector<int> newContainer;
    copy(digits.begin(), digits.end(), back_inserter(newContainer));
    assert(digits == newContainer);

    // Now sort
    sort(digits.begin(), digits.end());

    // Now copy if number is even. Moving between containers is fine.
    list<int> evens;
    copy_if(digits.begin(), digits.end(), back_inserter(evens), isEven);
   
    // Now print using copy function
    cout << "This should be 2 4 6 8: ";
    copy(evens.begin(), evens.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    // This is a Bad Idea:

    // for (auto i = digits.begin(); i != digits.end(); ++i)
    //     if (isEven(*i))
    //         digits.erase(i);    // erase element referenced by i
    //                             // (different "erase" -- a member of vector)

    // This is better:

    // Erase all even #s from digits
    auto removables = remove_if(digits.begin(), digits.end(), isEven);
    digits.erase(removables, digits.end());
    // OR: digits.erase(remove_if(digits.begin(), digits.end(), isEven), digits.end());

    // And all 11's
    digits.erase(remove(digits.begin(), digits.end(), 11), digits.end());

    cout << "This should be 1 3 5 7 9: ";
    copy(digits.begin(), digits.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
   
    return 0;
}
#endif
