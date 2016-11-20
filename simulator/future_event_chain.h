#ifndef FUTUREEVENTCHAIN_H
#define FUTUREEVENTCHAIN_H

#include <vector>

using namespace std;

/*!
 * \brief The FutureEventChain class is used for FEC algorithm implementation
 */
class FutureEventChain
{
public:

    FutureEventChain(vector<int> event);

    /*!
     * \brief Determines next event and moves the chain to that moment (sets time)
     * \return Index of the next event in event vector
     */
    int DetermineNextEvent();

    long long getTime() const;

    int getEvent(int index);

    void setEvent(int index, long long time);

    /*!
     * \brief Timespan between current and previous event
     */
    long long Timespan;

protected:

    /*!
     * \brief Vector of time of the next events
     */
    vector<int> event;

    /*!
     * \brief Current simulation time
     */
    long long time;
};

#endif // FUTUREEVENTCHAIN_H


