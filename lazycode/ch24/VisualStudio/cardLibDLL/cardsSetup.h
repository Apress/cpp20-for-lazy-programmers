// Header to make DLL functions import or export
//        -- from _C++20 for Lazy Programmers_

//This monstrosity is to tell the compiler to set a function up for export,
//  but only if we are compling the library. If not, set it up for import.

#ifndef SETUP_H
#define SETUP_H

# ifdef IM_COMPILING_MY_CARD_LIBRARY_RIGHT_NOW
#  define DECLSPEC __declspec(dllexport)
# else
#  define DECLSPEC __declspec(dllimport)
# endif //IM_COMPILING_MY_CARD_LIBRARY_RIGHT_NOW

#endif //SETUP_H

