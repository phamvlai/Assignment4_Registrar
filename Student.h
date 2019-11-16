#ifndef CPPQUEUE_STUDENT_H
#define CPPQUEUE_STUDENT_H

#include <cstdint>
#include <cstddef>

struct Student
{
    int enter;
    int time_taken;

    Student() = default;
    Student(int enter, int time_taken)
        : enter(enter), time_taken(time_taken)
    {

    }
};

#endif
