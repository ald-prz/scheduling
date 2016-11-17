#ifndef FUTUREEVENTCHAIN_H
#define FUTUREEVENTCHAIN_H

#include <vector>

using namespace std;

class FutureEventChain
{
public:

    FutureEventChain(vector<int> event);

    int DetermineNextEvent();

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


