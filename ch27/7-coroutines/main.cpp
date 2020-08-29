// Program to print several factorials using a coroutine
//      -- from _C++ for Lazy Programmers_

#include <iostream>
#include <experimental/generator>

std::experimental::generator<int> factorial()
{
    int whichOne = 0;                 // start with 0!
    int result = 1;                   // 0! is 1

    while (true)
    {
        co_yield result;
        ++whichOne;                   // go on to next one
        result *= whichOne;           // and calculate next result
    }
}

int main ()
{
    std::cout << "The first 8 factorials:\n";

    for (int i : factorial())
    {
        static int whichOne = 0;

        std::cout << whichOne << ": " << i << '\n';

        ++whichOne;                  // go on to next
        if (whichOne > 8) break;     // stop at 8
    }

    std::cout << std::endl;

    return 0;
}
