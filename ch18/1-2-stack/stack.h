// Stack class, with a limited stack size
//      -- from _C++20 for Lazy Programmers_

#ifndef STACK_H
#define STACK_H

#include <string>

class Stack
{
public:
    class UnderflowException    {}; // Exceptions
    class OverflowException     {};

    static constexpr int MAX_ITEMS = 5;

    Stack()                     { howMany_ = 0;  }
    Stack(const Stack& other)                   = delete;
    const Stack& operator= (const Stack& other) = delete;

    const std::string& top () const
    {
        if (empty()) throw UnderflowException (); 
        else return contents_[howMany_-1];
    }

    void push (const std::string& what)
    {
        if (full ()) throw OverflowException  ();
        else contents_[howMany_++] = what; 
    }

    std::string pop   ()  
    {
        std::string result = top(); --howMany_; return result;
    }

    bool empty () const { return howMany_ == 0;         }
    bool full  () const { return howMany_ >= MAX_ITEMS; }
    // Why not just see if they're equal?  howMany_ *can't* be
    //   bigger than MAX_ITEMS, can it?
    //   Not if I did everything perfectly, but...  
    //   better to program defensively if you aren't perfect

private:
    std::string contents_ [MAX_ITEMS];
    int         howMany_;  // how many items are in the stack?
};
#endif // STACK_H
