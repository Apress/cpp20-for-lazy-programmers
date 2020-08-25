// Program to illustrate a few char-array functions
//     -- from _C++20 for Lazy Programmers_

#include <iostream>

using namespace std;

// Ways to copy source to destination
void myStrcpy1 (char  destination[], const char  source[]);
void myStrcpy2 (char* destination,   const char* source);
void myStrcpy3 (char* destination,   const char* source);
void myStrcpy4 (char* destination,   const char* source);
void myStrcpy5 (char* destination,   const char* source);

int main ()
{
    constexpr int MAXSTR = 256;

    char name [MAXSTR];

    cout << "What's your name? "; cin >> name;

    // I fill the arrays with x's so I can be SURE myStrcpy is putting the
    //  final \0's on
    char copy1 [MAXSTR]; for(int i=0; i<MAXSTR;++i) copy1[i]='x';
    myStrcpy1 (copy1, name);
    char copy2 [MAXSTR]; for(int i=0; i<MAXSTR;++i) copy2[i]='x';
    myStrcpy2 (copy2, name);
    char copy3 [MAXSTR]; for(int i=0; i<MAXSTR;++i) copy3[i]='x';
    myStrcpy3 (copy3, name);
    char copy4 [MAXSTR]; for(int i=0; i<MAXSTR;++i) copy4[i]='x';
    myStrcpy4 (copy4, name);
    char copy5 [MAXSTR]; for(int i=0; i<MAXSTR;++i) copy5[i]='x';
    myStrcpy5 (copy5, name);

    cout << "Here's 5 copies of that:\n";
    cout << copy1 << '\n';
    cout << copy2 << '\n';
    cout << copy3 << '\n';
    cout << copy4 << '\n';
    cout << copy5 << '\n';

    return 0;
}

void myStrcpy1 (char destination [], const char source[])
{
    int i = 0;

    while (source[i] != '\0')
    {
        destination[i] = source[i];
        ++i;
    }

    destination[i] = '\0'; // put that null character at the end
}

// Here's a version that doesn't use the []'s.
void myStrcpy2 (char* destination, const char* source)
{
    int i = 0;

    while (*(source + i) != '\0')
    {
        *(destination + i) = *(source+i);
        ++i;
    }

    *(destination+i) = '\0'; // put null character at the end
}

// Not clearly better, but it will still work.  Here we
//   eliminate the use if i, and just update source and
//   destination directly:
void myStrcpy3 (char* destination, const char* source)
{
    while (*source != '\0')
    {
        *destination = *source;
        ++source; ++destination;
    }

    *destination = '\0'; // put null character at the end
}

void myStrcpy4 (char* destination, const char* source)
{
    while (*source)
        *destination++ = *source++;

    *destination = '\0'; // put null character at the end
}

// Remember that the value of X=Y is whatever value was
//   assigned -- which in the case of *destination++ = *source++
//   is simply *source.  We want to continue as long as this is nonzero.
void myStrcpy5 (char* destination, const char* source)
{
    while (*destination++ = *source++); *destination = '\0';
}
