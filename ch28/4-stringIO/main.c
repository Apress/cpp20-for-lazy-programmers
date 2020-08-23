//Program to test sprintf, sscanf, fgets, fputs 
//        -- from _C++20 for Lazy Programmers_

#include <stdio.h>

// Disable a warning about scanf, etc., in Visual Studio 
#ifdef _MSC_VER
#pragma warning (disable:4996) 
#endif

int main ()
{
    while (1)                  // forever, or until break... 
    {
        enum {MAXLINE=256};    // array size for line        
        char line [MAXLINE];   // a line of text             
        enum {MAXSTR = 80};    // array size for word        
        char word [MAXSTR];    // your word                  
        int  number;           // a number to read in        
        
        // get an entire line with gets; on EOF quit        
        printf("Enter a line with 1 word & 1 number, EOF to quit: ");
        if (! gets (line, MAXSTR)) break;

        // repeat line with puts                            
        printf("You entered:  "); 
        puts (line);

        // Use char array as source for 2 arguments          
        if (sscanf (line, "%s %i", word, &number) != 2)
            puts ("That wasn't a word and a number!\n");
        else
        {
            // Print using sprintf and puts                  
            sprintf(line, "The name was %s and the number was %i.\n", 
                    word, number);
            puts   (line);
            // If this weren't a demo of new functions, I'd say
            //    printf ("The name was %s and the number was %f.\n", 
            //          name, number); 
        }
    }

    puts ("\n\nBye!\n");
    
    return 0;
}
