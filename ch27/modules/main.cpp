//Telling the world hello in different languages using modules
//  -- for _C++20 for Lazy Programmers_

import printGreetings;      // for printHello, NUM_LANGUAGES

int main()
{
    for (int lang = 0; lang < languages::NUM_LANGUAGES; ++lang)
        printHello  (lang); // for each language, say hello

    return 0;
}