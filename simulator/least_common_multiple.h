#ifndef LOWEST_COMMON_MULTIPLE_H
#define LOWEST_COMMON_MULTIPLE_H

#include <vector>
#include <numeric>

using namespace std;

class LeastCommonMultiple
{
public:

    static long long Calculate(vector<long long> number_vector)
    {
        long long *number_array = &number_vector[0];
        return std::accumulate(number_array, number_array + number_vector.size(), 1, pairLcm);
    }

private:

    static int greatestCommonDivisor(long long a, long long b)
    {
        for (;;)
        {
            if (a == 0)
                return b;

            b %= a;

            if (b == 0)
                return a;

            a %= b;
        }
    }

    static long long pairLcm(long long a, long long b)
    {
        long long result = greatestCommonDivisor(a, b);

        return result ? (a / result * b) : 0;
    }
};

#endif // LOWEST_COMMON_MULTIPLE_H
