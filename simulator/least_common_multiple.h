#ifndef LOWEST_COMMON_MULTIPLE_H
#define LOWEST_COMMON_MULTIPLE_H

#include <vector>
#include <numeric>

using namespace std;

class LeastCommonMultiple
{
public:

    static int Calculate(vector<int> number_vector)
    {
        int *number_array = &number_vector[0];
        return std::accumulate(number_array, number_array + number_vector.size(), 1, pairLcm);
    }

private:

    static int greatestCommonDivisor(int a, int b)
    {
        for (;;)
        {
            if (a == 0) return b;
            b %= a;
            if (b == 0) return a;
            a %= b;
        }
    }

    static int pairLcm(int a, int b)
    {
        int result = greatestCommonDivisor(a, b);

        return result ? (a / result * b) : 0;
    }
};

#endif // LOWEST_COMMON_MULTIPLE_H
