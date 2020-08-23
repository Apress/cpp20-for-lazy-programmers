//A (partial) game with killer robots
//  meant to demonstrate use of file I/O
//This loads 3 points and prints a report
//      -- from _C++20 for Lazy Programmers_

#include <iostream>
#include <fstream>  //1. include <fstream>

using namespace std;

struct Point2D { int x_=0, y_=0; };

int main ()
{
                    //an array of robot positions
    constexpr int MAX_ROBOTS = 3;
    Point2D robots[MAX_ROBOTS];

                    //2. Declare file variables. 
                    //3. Open the files.
                    //Here's two ways to do both; either's fine
    ifstream inFile; inFile.open("level1.txt");
    ofstream outFile ("saveGame1.txt");

                    //4. Verify the files opened without error
    if (!inFile)
    {
        cout << "Can't open level1.txt!\n"; return 1;       
                    // 1 is a conventional return value for error
    }
    if (! outFile)
    {
        cout << "Can't create file saveGame1.txt!"; return 1;
    }

                   //5. Change cin to inFile, cout to outFile
    int whichRobot = 0;                 
    //while there's input and array's not full...
    while (inFile && whichRobot < MAX_ROBOTS)
    {
        int x, y;
        inFile >> x >> y;               //read in an x, y pair

        if (inFile)                     //if we got valid input (not at eof)
        {                               //store what we read
            robots[whichRobot] = {x, y};
            ++whichRobot;               //and remember there's 1 more robot
        }
    }

    for (int i = 0; i < MAX_ROBOTS; ++i)
        outFile     << robots[i].x_ << ' '
                    << robots[i].y_ << endl;

                   //6. When done, close the files
    inFile.close(); outFile.close();

                   //can still use cout for other things
    cout << "Just saved saveGame1.txt.\n"; 

    return 0;
}
