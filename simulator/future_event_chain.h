#ifndef FUTUREEVENTCHAIN_H
#define FUTUREEVENTCHAIN_H

#include <vector>

using namespace std;

class FutureEventChain
{
public:

    FutureEventChain(vector<int> event)
    {
        this->event = event;
        current_time = 0;
    }

    int DetermineNextEvent()
    {
        min_index = -1;          // -1 means that no event with positive start time found
        long long min_time;

        for (unsigned int i = 0; i < event.size(); i++)
        {
            if (event.at(i) >= 0)
            {
                if (min_index != -1)
                {
                    if (event.at(i) < min_time)
                    {
                        min_index = i;
                        min_time = event.at(i);
                    }
                }
                else
                {
                    min_index = i;
                    min_time = event.at(i);
                }
            }
        }

        if (min_index == -1)
            throw exception();

        Last_difference = event.at(min_index) - current_time;

        current_time = event.at(min_index);

        return min_index;
    }


    long long getTime() const
    {
        return current_time;
    }

    int getEvent(int index)
    {
        return event.at(index);
    }

    void setEvent(int index, long long time)
    {
        event.at(index) = time;
    }

    long long Last_difference;

protected:

    vector<int> event;

    long long current_time;

    int min_index;
};

#endif // FUTUREEVENTCHAIN_H


