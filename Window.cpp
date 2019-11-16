#include "Window.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <cstddef>

using namespace std;

void Window::read_from_file(ifstream& in_ptr) //function to read the information in the file
{
    string first_line;
    getline(in_ptr, first_line);

    int new_size = (int)stoll(first_line);
    queues.resize(new_size); //resizes the queue to the number of windows in the file

    while (true) //while loop to read in as many students and time necessary
    {
        string s_time_tick;
        int time_tick;

        string s_number_of_students;
        int number_of_student;
        vector<int> amount_of_time;

        getline(in_ptr, s_time_tick);
        getline(in_ptr, s_number_of_students);

        try //attempts set the number of students and time of students_added
        {
            time_tick = stoll(s_time_tick);
            number_of_student = stoll(s_number_of_students);
        }
        catch (const invalid_argument&)
        {
            break;
        }
        catch (const out_of_range&)
        {
            break;
        }

        bool everything_correct = true;
        amount_of_time.resize(number_of_student);
        for (int i = 0; i < number_of_student; i++)
        {
            string line;
            getline(in_ptr, line);

            try
            {
                amount_of_time[i] = stoll(line);
            }
            catch (const invalid_argument&)
            {
                everything_correct = false;
                break;
            }
            catch (const out_of_range&)
            {
                everything_correct = false;
                break;
            }
        }

        if (!everything_correct) //checks to ensure everything is correct
        {
            break;
        }

        for (int i = 0; i < number_of_student; i++)
        {
            info.emplace_back(Student(time_tick, amount_of_time[i]));
        }
    }

    has_read = true;
}

void Window::process() //function to run the main stats for the program
{
    if (!has_read)
    {
        return;
    }

    idle_times.resize(queues.size()); //sets the number of windows
    wait.resize(info.size());

    int student_index = 0;
    int students_added = 0;

    int this_time = 0;
    while (true) //while loop to continue the function after breaking from the inner while loop
    {
        int index = 0;
        bool queues_empty = true;
        for (const Queue<Student>& queue: queues)
        {
            if (!queue.empty()) //checks if window is empty, if it is, add idle window time
            {
                queues_empty = false;
            }
            else
            {
                idle_times[index]++;
            }

            index++;
        }

        if (queues_empty && info.empty())
        {
            break;
        }

        while (true)
        {
            bool has_dequeued = false;
            for (Queue<Student>& queue: queues)
            {
                if (!queue.empty() && (queue.front()->elem.enter + queue.front()->elem.time_taken) == this_time) //checks if the window is not empty and the student has spent their allotted time at window
                {
                    queue.dequeue(); //removes the student fron the window after their time is up
                    student_index++;

                    has_dequeued = true;
                }
            }

            if (!has_dequeued) //starts the loop over once dequeue to add next student
            {
                break;
            }
        }

        while (!info.empty() && info[0].enter == this_time)
        {
            bool has_added = false;
            for (Queue<Student>& queue: queues)
            {
                if (queue.empty() && !has_added)
                {
                    queue.enqueue(info[0]);
                    students_added++;

                    has_added = true;
                }
            }

            if (!has_added)
            {
                queues[0].enqueue(info[0]);
            }

            info.erase(info.begin());
        }

        int queue_working = 0;
        for (Queue<Student>& queue: queues)
        {
            if (!queue.empty())
            {
                queue_working++;
            }
        }

        for (int i = student_index + queue_working; i < students_added; i++) //loop to add waiting time
        {
            wait[i]++;
        }

        this_time++; //keeps track of the time
    }

    double average_idle_time = accumulate( idle_times.begin(), idle_times.end(), 0.0) / idle_times.size(); //calculates average window idle time
    double average_waiting_time = accumulate( wait.begin(), wait.end(), 0.0) / wait.size(); //calculates average student waiting time

    sort(wait.begin(), wait.end());
    sort(idle_times.begin(), idle_times.end());

    double waiting_time_median = 0.0; //calculates the median student waiting time
    if (wait.size() % 2 == 0)
    {
        waiting_time_median =  ((double)wait[wait.size() / 2 - 1] + (double)wait[wait.size() / 2]) / 2.0;
    }
    else
    {
        waiting_time_median = (double)wait[wait.size() / 2];
    }

    double idle_time_median = 0.0; //calculates the median window idle time
    if (idle_times.size() % 2 == 0)
    {
        idle_time_median =  ((double)idle_times[idle_times.size() / 2 - 1] + (double)idle_times[idle_times.size() / 2]) / 2.0;
    }
    else
    {
        idle_time_median = (double)idle_times[idle_times.size() / 2];
    }

    double max_waiting_time = *max_element(wait.begin(), wait.end());
    double max_idle_time = *max_element(idle_times.begin(), idle_times.end());

    int student10 = 0; //cacluate students waiting over 10 minutes
    for (const int& waiting_time: wait)
    {
        if (waiting_time > 10 * 60) student10++;
    }

    int window_idle_over_5_mins = 0; //calculates window idle time
    for (const int& idle_time: idle_times)
    {
        if (idle_time > 5 * 60) window_idle_over_5_mins++;
    }
    //prints out the desired stats
    cout << "Average waiting time: " << average_waiting_time << " sec\n";
    cout << "Median waiting time: " << waiting_time_median << " sec\n";
    cout << "Longest waiting time: " << max_waiting_time << " sec\n";
    cout << "Students waiting over 10 mins: " << student10 << "\n\n";

    cout << "Average window idle time: " << average_idle_time << " sec\n";
    cout << "Median window idle time: " << idle_time_median << " sec\n";
    cout << "Longest window idle time: " << max_idle_time << " sec\n";
    cout << "Windows idle over 5 mins: " << window_idle_over_5_mins << "\n\n";
}
