#ifndef LOWEST_COMMON_MULTIPLE_H
#define LOWEST_COMMON_MULTIPLE_H

#include <vector>
#include <numeric>

using namespace std;

class LeastCommonMultiple
{
public:

    static long long Calculate(vector<long long> number_vector);

private:

    static int greatestCommonDivisor(long long a, long long b);

    static long long leastCommonMultiple(long long a, long long b);
};

#endif // LOWEST_COMMON_MULTIPLE_H
