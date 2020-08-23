//A program with a rudimentary Stack of a specified size
//      -- from _C++20 for Lazy Programmers_

template <int SIZE>
class Stack             // Stack of chars with at most SIZE elements
{
public:
    // ...
    bool full () const { return howMany_ >= SIZE; }
private:
    char contents_[SIZE];
    int  howMany_;
};

int main ()
{
    Stack<30> stack; // Will get a warning of unreferenced local variable -- it's OK
    return 0;
}

