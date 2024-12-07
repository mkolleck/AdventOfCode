// https://adventofcode.com/2024/day/7

#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

static long long int shiftBase10(long long int value, long long int other)
{
    return value * (long long int)(
            pow(10, (long long int)(log(other) / log(10)) + 1));
}

static bool check(const long long int result, long long int intermediate,
        char op, const std::vector<long long int>& values, size_t offset,
        bool shift)
{
    if (offset < values.size())
    {
        switch (op)
        {
            case '+':
                intermediate += values[offset];
                break;

            case '*':
                intermediate *= values[offset];
                break;

            case '|':
                intermediate = shiftBase10(intermediate, values[offset])
                    + values[offset];
                break;
        }
    }

    if (offset == values.size() - 1)
    {
        return intermediate == result;
    }

    if (intermediate > result)
    {
        return false;
    }

    if (shift)
    {
        return check(result, intermediate, '+', values, offset + 1, shift)
            || check(result, intermediate, '*', values, offset + 1, shift)
            || check(result, intermediate, '|', values, offset + 1, shift);
    }

    return check(result, intermediate, '+', values, offset + 1, shift)
        || check(result, intermediate, '*', values, offset + 1, shift);
}

int main(void)
{
    size_t result1 = 0, result2 = 0;
    std::string line;

    while (!std::getline(std::cin, line).eof())
    {
        std::istringstream s(line);
        std::vector<long long int> values;
        long long int result, a;
        char sep;

        s >> result >> sep;

        while (s.good())
        {
            s >> a;
            values.push_back(a);
        }

        if (check(result, 0, '+', values, 0, false))
        {
            result1 += result;
        }

        if (check(result, 0, '+', values, 0, true))
        {
            result2 += result;
        }
    }

    std::cout << result1 << std::endl << result2 << std::endl;
    return 0;
}
