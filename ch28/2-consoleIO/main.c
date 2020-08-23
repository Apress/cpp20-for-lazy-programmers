//Program to test C's major standard I/O functions
//        -- from _C++20 for Lazy Programmers_ 

#include <stdio.h>

// Disable a warning about scanf, etc., in Visual Studio 
#ifdef _MSC_VER
#pragma warning (disable:4996) 
#endif

int main ()
{
    float number;           // number we'll read in and print out  
    int   age;              // your age                            
    enum {MAXSTR = 80};     // array size                          
    char  name [MAXSTR];    // your name                           

        // A printf showing float, and use of % sign               
    printf ("%3.2f%% of statistics are made up on the spot!\n\n", 
            98.23567894);

        // printfs using decimal, hex, and char array              
        // %02d means pad number to a width of 2 with leading 0's  
    printf ("%d is 0x%x in hexadecimal.\n\n", 16, 16);
    printf ("\"%s\" is a $%d.%02d word.\n\n", "hexadecimal", 
            5, 0);

        // Scanf needs & for the variables it sets 
    printf ("Enter a floating-point number:  "); 
    scanf ("%f", &number);
    printf ("%g is %f in fixed notation and %e in scientific.\n", 
            number, number, number);
    printf ("...in scientific with a precision of 2:  %.2e.\n\n", 
            number);

        // ...except arrays, since they're already addresses       
    printf ("Enter your name and age:  "); 
    scanf ("%s %d", name, &age);
    printf ("%s is %d years old!\n\n", name, age); 

    return 0;
}
