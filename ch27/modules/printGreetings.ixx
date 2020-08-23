// Module for printing greetings in various languages
//	  -- for _C++20 for Lazy Programmers_

export module printGreetings;
 
import std.core;
export import greetings;
 
export void printHello   (int language)
{
    std::cout << languages::helloMessage [language] << '\n'; 
}

export void printGoodbye (int language)
{
    std::cout << languages::goodbyeMessage [language] << '\n';  
}

