// https://adventofcode.com/2022/day/4

#include <iostream>
#include <regex>
#include <sstream>

int main(void)
{
    std::string line;
    int overlap1 = 0, overlap2 = 0;

    while (!std::getline(std::cin, line).eof())
    {
        int a1, a2, a3, a4;
        std::istringstream(std::regex_replace(line, std::regex("[,-]"), " "))
            >> a1 >> a2 >> a3 >> a4;

        if (((a3 <= a1) && (a1 <= a4) && (a3 <= a2) && (a2 <= a4))
                || ((a1 <= a3) && (a3 <= a2) && (a1 <= a4) && (a4 <= a2)))
        {
            overlap1++;
        }

        if (((a1 <= a3) && (a3 <= a2)) || ((a1 <= a4) && (a4 <= a2))
                || ((a3 <= a1) && (a1 <= a4)) || ((a3 <= a2) && (a2 <= a4)))
        {
            overlap2++;
        }
    }

    std::cout << overlap1 << "\n" << overlap2 << std::endl;
    return 0;
}
