// A program with a rudimentary Stack of a specified size
//      -- from _C++20 for Lazy Programmers_

#include <cassert>      // for assert

template <int SIZE>
class Stack             // Stack of chars with at most SIZE elements
{
public:
    Stack() : howMany_(0) {}

    bool full () const { return howMany_ >= SIZE; }
private:
    char contents_[SIZE];
    int  howMany_;
};

int main ()
{
    Stack<30> stack; 

    assert (! stack.full());

    return 0;
}

