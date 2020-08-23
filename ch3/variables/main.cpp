//Program to print facts about an amazing show
//		-- from _C++ for Lazy Programmers_

#include "SSDL.h"

int main(int argc, char** argv)
{
	int    seasonsOfAmericanIdol 			= 17;
						//after a while you lose track
	float  hoursIveWatchedAmericanIdol 		= 424.5F;
						//missed half an episode, dang it
	double howMuchIShdCareAboutAmericanIdol = 1.0E-21;
						//1x10 to the -21 power
	double howMuchIDoCareAboutAmericanIdol 	= 0.000000000000001;
						//So why'd I watch it if I don't care?
	
	sout << "Through watching " << seasonsOfAmericanIdol << "seasons, ";
	sout << "I have seen " << hoursIveWatchedAmericanIdol << " hours of American Idol.\n";

	sout << "I think I should care about it this much:\t" << howMuchIShdCareAboutAmericanIdol << "\n";
	sout << "and I do care about it this much:\t"		  << howMuchIDoCareAboutAmericanIdol << "\n";
	sout << "I'm sure Wikipedia has an entry on 'denial'!\n";

	//end program
	SSDL_WaitKey();
	return 0;
}
