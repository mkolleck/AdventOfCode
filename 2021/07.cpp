// https://adventofcode.com/2021/day/7

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

static int fuel1(const std::vector<int>& crabs)
{
    int fuel = 0;
    int position = crabs[crabs.size() / 2];

    for (const auto& c : crabs)
    {
        fuel += std::abs(c - position);
    }

    return fuel;
}

static int fuel2(const std::vector<int>& crabs, int position)
{
    int fuel = 0;

    for (const auto& c : crabs)
    {
        int delta = std::abs(c - position);
        fuel += (delta * (delta + 1)) / 2;
    }

    return fuel;
}

static int fuel2(const std::vector<int>& crabs)
{
    int fuel = std::numeric_limits<int>::max();

    for (int i = 0; i < 1000; i++)
    {
        int f = fuel2(crabs, i);

        if (f < fuel)
        {
            fuel = f;
        }
    }

    return fuel;
}

int main(void)
{
    std::vector<int> crabs;

    while (!std::cin.eof())
    {
        int crab; char comma;
        std::cin >> crab >> comma;
        crabs.push_back(crab);
    }

    std::sort(crabs.begin(), crabs.end());

    std::cout << fuel1(crabs) << "\n" << fuel2(crabs) << std::endl;
    return 0;
}
