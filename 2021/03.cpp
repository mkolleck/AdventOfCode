// https://adventofcode.com/2021/day/3

#include <iostream>
#include <vector>

static int onesAt(const std::vector<int>& numbers, int index)
{
    int result = 0, mask = 1 << index;

    for (int n : numbers)
    {
        if (n & mask)
        {
            result++;
        }
    }

    return result;
}

static int part2(const std::vector<int>& numbers, int needle, int bits)
{
    std::vector<int> t1 = numbers, t2;
    int value = 0, mask = 0;

    while (bits > 0)
    {
        int ones = onesAt(t1, bits - 1);

        if (2 * ones >= t1.size())
        {
            if (needle)
            {
                value |= 1 << (bits - 1);
            }
        }
        else
        {
            if (!needle)
            {
                value |= 1 << (bits - 1);
            }
        }

        mask |= 1 << (bits - 1);
        bits--;

        if (t1.size() > 1)
        {
            t2.clear();

            for (auto i : t1)
            {
                if ((i & mask) == (value & mask))
                {
                    t2.push_back(i);
                }
            }

            t1 = t2;
        }
    }

    return t1[0];
}

int main(void)
{
    std::vector<int> ones, numbers;
    std::string line;

    while (!(std::cin >> line).eof())
    {
        int i = 0;
        int number = 0;

        if (ones.size() == 0)
        {
            ones.resize(line.length());
        }

        for (auto c : line)
        {
            if (c == '1')
            {
                ones[i]++;
                number |= 1;
            }

            i++;
            number <<= 1;
        }

        number >>= 1;
        numbers.push_back(number);
    }

    int γ = 0, ε = 0;

    for (auto o : ones)
    {
        if (2 * o > numbers.size())
        {
            γ |= 1;
        }
        else
        {
            ε |= 1;
        }

        γ <<= 1;
        ε <<= 1;
    }

    std::cout << (γ >> 1) * (ε >> 1) << std::endl;
    std::cout
        << part2(numbers, 1, ones.size()) * part2(numbers, 0, ones.size())
        << std::endl;
    return 0;
}
