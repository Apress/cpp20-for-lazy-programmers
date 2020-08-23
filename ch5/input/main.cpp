//Program to insult the user based on input
//		-- from _C++ for Lazy Programmers_

#include "SSDL.h"

int main(int argc, char** argv)
{
	int ageInYears = 0;

	sout << "Let's see if you can handle the truth.\n";
	sout << "How old are you? "; ssin >> ageInYears;

	bool isOlder = (ageInYears >= 20);
	//Seriously? Well, 20 *is* old if you're a computer program

	if (isOlder) sout << "The truth is you are OLD.\n";
	else         sout << "You're not old enough.  Sorry, kid.\n";

	sout << "Hit any key to end.\n";

	SSDL_WaitKey();

	return 0;
}
