//Program that uses stringstream to center 
//   multiple things on one line
//      -- from _C++20 for Lazy Programmers_

#include <sstream>
#include "SSDL.h"

using namespace std;

int main(int argc, char** argv)
{
    int points = 3200;       // Some arbitrary data to test
    double time = 30.2;      //  printing to HUD
    char mood[] = "Annoyed";

    stringstream out;
    out << "Points: " << points << "   /   Time left: "
        << time << "   /   Mood: " << mood;

    string result = out.str();           
    SSDL_RenderTextCentered(result.c_str(), SSDL_GetWindowWidth()/2, 10);

    SSDL_WaitKey();         // Wait for user to hit a key
    return 0;
}
