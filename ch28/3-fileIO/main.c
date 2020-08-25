// Program to test C's major standard I/O functions
//        -- from _C++20 for Lazy Programmers_

#include <stdio.h>

// Disable a warning about fopen, etc., in Visual Studio 
#ifdef _MSC_VER
#pragma warning (disable:4996) 
#endif

int main ()
{
    FILE* file;             // a file to write to or read from     
    float number;           // number we'll read in and print out  
    enum { MAXSTR = 80 };   // array size                          
    char junk [MAXSTR];     // a char array for reading in (and thus    
                            //         discarding) a word            
        
        // printing to file. The number gets 4 digits of precision 
    file = fopen ("newfile.txt", "w"); 
    if (!file) 
    { 
        printf("Can't open newfile.txt for writing!\n"); return 0; 
    }
    printf  (      "Avagadro's number is %.4e.\n", 6.023e+023);
    fprintf (file, "Avagadro's number is %.4e.\n", 6.023e+023);
    fclose  (file);    

        // reading from a file                                     
    file = fopen ("newfile.txt", "r");
    if (!file) 
    { 
        printf("Can't open newfile.txt for reading!\n"); return 0; 
    }
    fscanf (file, "%s %s %s %e", junk, junk, junk, &number);
                       // Read in 3 words, then the number we want 
    fclose (file);
    printf ("Looks like Avagadro's number is still %.4e.\n", number);

    return 0;
}
