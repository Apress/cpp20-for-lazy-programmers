// GridLoc class: a grid location, row and column
//        -- from _C++20 for Lazy Programmers_

#ifndef GRIDLOC_H
#define GRIDLOC_H

#include <iostream>
#include "io.h"

struct GridLoc
{
    int row_, clm_;

	//These member functions make life nicer
	GridLoc                  (int r=0, int c=0    ) 
		: row_(r), clm_(c) 
	{
	}
	GridLoc& operator= (const GridLoc& other) 
	{ 
		row_ = other.row_; clm_ = other.clm_; return *this; 
	}
};

inline
std::istream& operator>> (std::istream& in, GridLoc& foo)
{
	in >> foo.row_ >> foo.clm_; 
	if (!in) { in.clear(); in.ignore(256, '\n'); throw BadInput(); }
    //We saw this in the exercises from Chapter 17 's section on 
    //>> and <<: if you type a char when istream expects an int, 
    //it gets into an error state and won't come back. in.clear() 
    //fixes the problem, and in.ignore discards the rest of the 
    //line, which is likely wrong as well.
	
	return in;
}

#endif //GRIDLOC_H
