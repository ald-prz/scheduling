#include "least_common_multiple.h"

long long LeastCommonMultiple::Calculate(vector<long long> number_vector)
{
    long long *number_array = &number_vector[0];
    return std::accumulate(number_array, number_array + number_vector.size(), 1, leastCommonMultiple);
}

int LeastCommonMultiple::greatestCommonDivisor(long long a, long long b)
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

long long LeastCommonMultiple::leastCommonMultiple(long long a, long long b)
{
    long long result = greatestCommonDivisor(a, b);

    return result ? (a / result * b) : 0;
}
