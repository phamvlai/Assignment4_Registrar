#include <iostream>
#include <fstream>
#include <cstddef>

#include "Window.h"

using namespace std;

bool file_exists(const char *filename) //checks to see if file exist in the library
{
    ifstream temp(filename, ios::binary);
    if (temp.good())
    {
        temp.close();
        return true;
    }

    return false;
}

int main(int argc, char *argv[]) //main function to run the program
{
    if (argc != 2) //checks to see the format is correct
    {
        cout << "Input is: Program Filename\n";
        return 1;
    }

    if (!file_exists(argv[1])) //checks to see if file exists
    {
        cout << "File does not exist.\n";
        return 2;
    }

    ifstream in_ptr(argv[1]);

    Window window;
    window.read_from_file(in_ptr);
    window.process();

    return 0;
}
