// https://adventofcode.com/2020/day/6

#include <iostream>
#include <map>

typedef std::map<char, int> Group;

void process(int& anySum, int& allSum, const Group& group, int groupSize)
{
    anySum += group.size();

    for (const auto& g : group)
    {
        if (g.second == groupSize)
        {
            allSum++;
        }
    }
}

int main(void)
{
    int anySum = 0, allSum = 0, groupSize = 0;
    Group group;
    std::string line;

    while (!(std::getline(std::cin, line)).eof())
    {
        if (line.empty())
        {
            process(anySum, allSum, group, groupSize);
            group.clear();
            groupSize = 0;
            continue;
        }

        for (const auto& c : line)
        {
            group[c]++;
        }

        groupSize++;
    }

    if (group.size() != 0)
    {
        process(anySum, allSum, group, groupSize);
    }

    std::cout << "Sum (anyone): " << anySum << std::endl;
    std::cout << "Sum (everyone): " << allSum << std::endl;
    return 0;
}
