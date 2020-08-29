// Class Area
//   Each Area is read in as 
//     <north bound> <south bound> <west bound> <east bound> <name>
//     as in
//     5 3 1 6 Elbonia
//   ...and that's what it contains

//       -- from _C++20 for Lazy Programmers_

#include "area.h"

void Area::copyBoundingBox (const Area& other)
{
    for (int direction = 0; direction < DIRECTIONS; ++direction)
        boundingBox_[direction] = other.boundingBox_[direction];
}
