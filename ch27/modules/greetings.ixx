// Module for lists of hello, goodbye messages in different languages
//	-- for _C++20 for Lazy Programmers_

export module greetings;

namespace languages // Ordinarily I'd name this same as the module, but I want to
                    //  be clear when I'm referring to namespace and when I'm referring
                    //  to module, for this example
{
	export constexpr int NUM_LANGUAGES = 3;

	// Greetings in English, Espanol, Esperanto...
	export const char* helloMessage  [] = { "Hello",   "Hola",  "Saluton" };
	export const char* goodbyeMessage[] = { "Goodbye", "Adios", "Adiau"   };

	int secretFunction () { return 1; } // not visible to outside world
}; //namespace languages
