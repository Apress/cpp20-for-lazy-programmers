// Program to get the frequencies of letters
//       -- from _C++20 for Lazy Programmers_

#include <iostream>

using namespace std;

int main ()
{
    // make an array of frequencies for letters, all initially zero
    constexpr int LETTERS_IN_ALPHABET = 26;
    int frequenciesOfLetters[LETTERS_IN_ALPHABET] = {}; // all zeroes

    // read in the letters
    while (cin)              // while there are letters left
    {
        char ch; cin >> ch;  // read one in
        ch = toupper(ch);    // capitalize it

        if (cin)             // Still no problems with cin, right?
            if (isalpha(ch)) //   and this is an alphabetic letter?
                ++frequenciesOfLetters[ch - 'A'];
                             // A's go in slot 0, B's in slot 1...
    }

    // print all those frequencies
    cout << "Frequencies are:\n";
    cout << "Letter\tFrequency\n";
    for (char ch = 'A'; ch <= 'Z'; ++ch) // for each letter A to Z...
        cout << ch << '\t' << frequenciesOfLetters[ch - 'A'] << '\n';

    return 0;
}
