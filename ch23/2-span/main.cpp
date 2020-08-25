// Program to read in & dissect a phone number
//       -- from _C++20 for Lazy Programmers_

#include <iostream>

#if __has_include (<span>)
#include <span>    // for std::span
#else
#warning "This compiler does not support spans."
#endif

using namespace std;

// Converts a char to a single-digit number
int char2digit(char c) { return c - '0'; }

// Read/print arrays, I mean, spans
void read (const span<      int>& s);
void print(const span<const int>& s);

int main(void)
{
    int phoneNumber[10]; 
    cout << "Enter your phone # (10 digits, no punctuation, ";
    cout << "e.g 2025550145):  ";  read (phoneNumber);
    cout << "You entered:       "; print(phoneNumber);
    cout << '\n';
    cout << "Area code was:     "; 
    print(span(phoneNumber).subspan(0, 3));     cout << '\n';

    // subspan is better, but this shows how to use 
    //     a span with a pointer
    int* remainder = phoneNumber + 3;
    cout << "Rest of number is: ";  print(span(remainder, 7));
    cout << '\n';

    return 0;
}

void print(const span<const int>& s)
{
    for (const auto& element : s) cout << element;
}

void read (const span<      int>& s)
{
    for (auto& element : s)
        element = char2digit(cin.get());
            // read in a digit, convert to int
            //  keeping it simple: no check for bad input         
}