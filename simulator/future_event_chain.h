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
        time = 0;
    }

    int DetermineNextEvent()
    {
        min_index = -1;          // -1 means that no event with positive start time found
        int min_time;

        for (int i = 0; i < event.size(); i++)
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

        time = event.at(min_index);

        return min_index;
    }


    int getTime() const
    {
        return time;
    }

    int getEvent(int index)
    {
        return event.at(index);
    }

    int setEvent(int index, int time)
    {
        event.at(index) = time;
    }

protected:

    vector<int> event;

    int time;

    int min_index;
};

#endif // FUTUREEVENTCHAIN_H


