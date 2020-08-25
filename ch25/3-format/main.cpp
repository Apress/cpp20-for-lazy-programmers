// Program to illustrate further capabilities of C++20's fmt
//      -- from _C++ for Lazy Programmers_

#define FMT_HEADER_ONLY // Use this for now; when compiler supports
                        //  format, should be able to skip this

#include <iostream>
#include <string>
#include <fmt/format.h> // Use this for now; when compiler supports 
                        //  format, shd say just #include <format>

using namespace std;
using namespace fmt::v6;// Use this for now; when compiler supports
                        //  format, this should be in namespace std

int main()
{
    // Print the same integer using base 2, 8, 16, and 10
    cout << "Here's 15 written in...\n";
    cout << format("{0:>8}{1:>8}{2:>8}{3:>8}\n",
                   "binary", "octal", "hex", "decimal");
                   //(if you don't specify, you get decimal)
    cout << format("{0:>8b}{0:>8o}{0:>8X}{0:>8}\n\n", 15);
    // We used argument #0 four times; no law against that...

    // Print the same item with different types of padding
    cout << "Here's 15 padded with x's, .'s, and *'s: ";
    cout << format("{0:x>4} {0:.>4} {0:*>4}\n\n", 15);

    // Print a floating point number with different formats
    cout << "And here's 0.01234 in scientific, fixed, general, ";
    cout << "and default format,\n";
    cout << "showing how they interpret a precision of 2.\n";
    cout << format("{0:>10.2e} {0:>10.2f} {0:>10.2g} {0:>10.2}\n\n",
                   0.01234);

    // You can also print to a string with format_to:
    string str;
    format_to(back_inserter(str), "The language of choice is {}.\n",
              "C++");
    cout << str;

    return 0;
}

