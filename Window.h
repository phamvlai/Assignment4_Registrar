#ifndef CPPQUEUE_WINDOW_H
#define CPPQUEUE_WINDOW_H

#include <fstream>
#include <vector>
#include <cstddef>
#include "Queue.h"
#include "Student.h"

using namespace std;

class Window
{
    vector<Queue<Student>> queues;
    vector<Student> info;
    bool has_read;

    vector<int> wait;
    vector<int> idle_times;

public:
    Window()
    {
        has_read = false;
    }

    void read_from_file(ifstream& in_ptr);
    void process();
};

#endif
