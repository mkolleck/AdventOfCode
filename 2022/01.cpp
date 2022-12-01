// https://adventofcode.com/2022/day/1

#include <iostream>
#include <list>
#include <numeric>

void tally(int c, std::list<int>& m)
{
    m.push_back(c);
    m.sort();

    if (m.size() > 3)
    {
        m.pop_front();
    }
}

int main(void)
{
    int calories = 0;
    std::list<int> maxCalories;
    std::string line;

    while (!std::getline(std::cin, line).eof())
    {
        if (line.empty())
        {
            tally(calories, maxCalories);
            calories = 0;
            continue;
        }

        calories += std::stol(line);
    }

    // There's no empty line at the end of input, so tally the last elf now.
    tally(calories, maxCalories);

    std::cout << maxCalories.back() << "\n"
        << std::accumulate(maxCalories.begin(), maxCalories.end(), 0)
        << std::endl;
    return 0;
}
