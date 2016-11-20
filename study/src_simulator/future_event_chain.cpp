#include "future_event_chain.h"

FutureEventChain::FutureEventChain(vector<int> event)
{
    this->event = event;
    time = 0;
}

int FutureEventChain::DetermineNextEvent()
{
    int min_index = -1;          // -1 means that no event with positive start time found
    long long min_time;

    // determine next event

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

    // not found the next event

    if (min_index == -1)
        throw exception();

    // memorize the timespan

    Timespan = event.at(min_index) - time;

    // move to the next event

    time = event.at(min_index);

    return min_index;
}

long long FutureEventChain::getTime() const
{
    return time;
}

int FutureEventChain::getEvent(int index)
{
    return event.at(index);
}

void FutureEventChain::setEvent(int index, long long time)
{
    event.at(index) = time;
}
