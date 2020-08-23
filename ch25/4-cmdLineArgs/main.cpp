// Program to find the difference between two files
//  -- from _C++20 for Lazy Programmers_

#include <iostream>
#include <fstream>
#include <cstdlib> // for EXIT_FAILURE, EXIT_SUCCESS
#include <string>

using namespace std;

int main (int argc, char** argv)
{
    // Did we get right # of arguments? If not, complain and quit
    if (argc != 3) // 3 args: 1 program name, plus 2 files
    {              // On failure, tell user what user should've entered:
        cerr << "Usage: " << argv[0] << " <file 1> <file 2>\n";
        return EXIT_FAILURE;    
    }
    
    // Load the 2 files
    ifstream file1(argv[1]), file2(argv[2]); // open files
    if (! file1) // On failure, say which file wouldn't load
    {           
        cerr << "Error loading " << argv[1] << endl;
        return EXIT_FAILURE;
    }
    if (!file2) // On failure, say which file wouldn't load
    {           
        cerr << "Error loading " << argv[2] << endl;
        return EXIT_FAILURE;
    }

    string line1, line2;

    while (file1 && file2)                  // While BOTH files are not finished
    {
        getline(file1, line1);              //   read line from file1
        if (!file1) break;

        getline(file2, line2);              //   ...from file2
        if (!file2)                         //   if file2's done but file 1 isn't, then
        {
            cout << "<: " << line1 << endl; //     spit out last line read from file 1
            break;
        }

        if (line1 != line2)                 //   if lines differ print them
        {
            cout << "<: " << line1 << endl; //   < means "first file"
            cout << ">: " << line2 << endl; //   > means "second file"
                                            //   this is conventional
        }
    }

    // If either file has more lines than the other, print remainder
    while (file1) 
    { 
        getline(file1, line1); 
        if (file1) cout << "<: " << line1 << endl; 
    }
    while (file2) 
    { 
        getline(file2, line2); 
        if (file2) cout << ">: " << line2 << endl; 
    }

    // Clean up and return
    file1.close(); file2.close();

    return EXIT_SUCCESS;
}
