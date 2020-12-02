// https://adventofcode.com/2020/day/1

#include <iostream>
#include <vector>

int main(void)
{
    std::vector<int> entries;
    int value = 0;

    while (!(std::cin >> value).eof())
    {
        for (int entry : entries)
        {
            if (entry + value == 2020)
            {
                std::cout << entry << " * " << value
                    << " = " << entry * value << std::endl;
            }

            for (int entry2 : entries)
            {
                if (entry + entry2 + value == 2020)
                {
                    std::cout << entry << " * " << entry2 << " * " << value
                        << " = " << entry * entry2 * value << std::endl;
                }
            }
        }

        entries.push_back(value);
    }

    return 0;
}
