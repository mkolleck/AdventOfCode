// https://adventofcode.com/2020/day/10

#include <algorithm>
#include <iostream>
#include <vector>

long long int trib(long long int i)
{
    if ((i == 0) || (i == 1))
    {
        return 0;
    }

    if (i == 2)
    {
        return 1;
    }

    return trib(i - 1) + trib(i - 2) + trib(i - 3);
}

int main(void)
{
    std::vector<int> jolts;
    jolts.push_back(0);

    int n = 0;

    while (!(std::cin >> n).eof())
    {
        jolts.push_back(n);
    }

    std::sort(jolts.begin(), jolts.end());
    jolts.push_back(jolts.back() + 3);

    int ones = 0, threes = 0, delta1 = 0;
    long long int arrangements = 1;

    for (int i = 0; i < jolts.size() - 1; i++)
    {
        int delta = jolts[i + 1] - jolts[i];

        if (delta == 1)
        {
            ones++;
            delta1++;
        }
        else if (delta == 3)
        {
            if (delta1 > 1)
            {
                arrangements *= trib(delta1 + 2);
            }

            delta1 = 0;
            threes++;
        }
    }

    std::cout << ones << " * " << threes << " = " << ones * threes << std::endl;
    std::cout << arrangements << std::endl;
    return 0;
}
