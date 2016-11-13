#ifndef FUTUREEVENTCHAIN_H
#define FUTUREEVENTCHAIN_H

#include <vector>

using namespace std;

class FutureEventChain
{
public:

    FutureEventChain(vector<int> future_event)
    {
        this->future_event = future_event;
        time = 0;
    }

    int DetermineNextEvent()
    {
        min_index = -1;          // -1 means that no event with positive start time found
        int min_time;

        for (int i = 0; i < future_event.size(); i++)
        {
            if (future_event.at(i) >= 0)
            {
                if (min_index != -1)
                {
                    if (future_event.at(i) < min_time)
                    {
                        min_index = i;
                        min_time = future_event.at(i);
                    }
                }
                else
                {
                    min_index = i;
                    min_time = future_event.at(i);
                }
            }
        }

        if (min_index == -1)
            throw exception();

        time = future_event.at(min_index);

        return min_index;
    }


    int getTime() const
    {
        return time;
    }

protected:

    vector<int> future_event;

    int time;

    int min_index;
};

#endif // FUTUREEVENTCHAIN_H


