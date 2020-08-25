//Program to do statistics on some strings
//        from _C++20 for Lazy Programmers_

#include <stdio.h>  // for printf, scanf
#include <string.h> // for strlen       

// Disable a warning about scanf, etc., in Visual Studio 
#ifdef _MSC_VER
#pragma warning (disable:4996) 
#endif

void updateLineStats (char line[], unsigned int* length,
                      float* averageLineLength);

int main ()
{
    printf ("Type in a line and I'll reply. ");
    printf ("Type the end-of-file character to end.\n");

    while (1)   // forever (or until a break) ... 
    {
        enum { MAXSTRING = 256 };      // max line length    
        char line [MAXSTRING];         // the line           
        int  length;                   // its current length 
        float averageLineLength;    

        // get line of input                 
        if (!fgets (line, MAXSTRING, stdin)) break;

        // do the stats. We send addresses, not variables, using &
        updateLineStats (line, &length, &averageLineLength);

        // give the result  
        printf ("Length of that line, ");
        printf ("and average so far: %d, %.2f.\n",
                length, averageLineLength);
    }

    return 0;
}

void updateLineStats (char line[], unsigned int* length,
                      float* averageLineLength)
{
    static int totalLinesLength = 0;    // have to remember these 
    static int linesSoFar = 0;          //   for next time        

    // length is a pointer, so *length is the length
    *length = (unsigned int) strlen (line);
                        // casting from size_t to unsigned int

    // fgets included the final \n, but I won't count that:      
    --(*length); 

    ++linesSoFar;
    totalLinesLength += *length; 

    *averageLineLength = // and averageLineLength needs its *, too
        totalLinesLength / ((float) linesSoFar);
}
