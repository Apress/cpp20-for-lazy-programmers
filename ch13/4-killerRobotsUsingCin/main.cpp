// A (partial) game with killer robots
//    meant to demonstrate use of file I/O
// This loads 3 points and prints them
//       -- from _C++20 for Lazy Programmers_

#include <iostream>

using namespace std;

struct Point2D { int x_=0, y_=0; };

int main ()
{
                    // an array of robot positions
    constexpr int MAX_ROBOTS = 3;
    Point2D robots[MAX_ROBOTS];

    int whichRobot = 0;                 
    // while there's input and array's not full...
    while (cin && whichRobot < MAX_ROBOTS)
    {
        int x, y;
        cin >> x >> y;               // read in an x, y pair

        if (cin)                     // if we got valid input (not at end of file)
        {                            // store what we read
            robots[whichRobot] = {x, y};
            ++whichRobot;            // and remember there's 1 more robot
        }
    }

    for (int i = 0; i < MAX_ROBOTS; ++i)
        cout        << robots[i].x_ << ' '
                    << robots[i].y_ << endl;

    return 0;
}
