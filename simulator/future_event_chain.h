#ifndef FUTUREEVENTCHAIN_H
#define FUTUREEVENTCHAIN_H

#include <vector>

using namespace std;

class FutureEventChain
{
public:

    FutureEventChain(vector<int> event);

    int DetermineNextEvent();

    long long GetCurrentTime() const;

    int GetEvent(int index);
    void SetEvent(int index, long long time);

    long long GetTimeDifference() const;
    void SetTimeDifference(long long value);

protected:

    vector<int> event;

    long long current_time;

    int min_index;

    long long time_difference;
};

#endif // FUTUREEVENTCHAIN_H



