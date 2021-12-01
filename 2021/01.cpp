// https://adventofcode.com/2021/day/1

#include <iostream>
#include <vector>

int main(void)
{
    int value = 0, lastValue = 0, increased = 0;
    int window[3] = { 0, 0, 0 }, lastWindow = 0, windowIncreased = 0, i = 0;

    while (!(std::cin >> value).eof())
    {
        if ((lastValue != 0) && (value > lastValue))
        {
            increased++;
        }

        lastValue = value;

        window[i % 3] = value;

        if (i > 1)
        {
            int thisWindow = window[0] + window[1] + window[2];

            if ((lastWindow > 0) && (thisWindow > lastWindow))
            {
                windowIncreased++;
            }

            lastWindow = thisWindow;
        }

        i++;
    }

    std::cout << increased << "\n" << windowIncreased << std::endl;
    return 0;
}
