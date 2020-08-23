//Program to generate a random passcode of digits
//        -- from _C++20 for Lazy Programmers_

#include <stdio.h>
#include <stdlib.h> // for srand, rand, malloc, free 
#include <time.h>   // for time                      

// Disable a warning about scanf, etc., in Visual Studio 
#ifdef _MSC_VER
#pragma warning (disable:4996) 
#endif

int main ()
{ 
    srand ((unsigned int) time(NULL));// start random # generator 
                                      // NULL, not nullptr        
 
    int codeLength;                   // get code length          
    printf ("I'll make your secret passcode. "
            "How long should it be? ");
    scanf ("%d", &codeLength);

                                        // allocate array         
    int* passcode = malloc(codeLength * sizeof(int));

    for (int i = 0; i < codeLength; ++i)// generate passcode      
        passcode[i] = rand () % 10;     // each entry is a digit  

    printf ("Here it is:\n");           // print passcode         
    for (int i = 0; i < codeLength; ++i)
        printf ("%d", passcode[i]);
    printf("\n");
    printf("But I guess it's not secret any more!\n");
    
    free (passcode);                    // deallocate array       

    return 0;
}
