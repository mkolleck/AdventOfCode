// https://adventofcode.com/2022/day/2

#include <cctype>
#include <iostream>
#include <vector>

int value(char c)
{
    if (std::isupper(c))
    {
        return c - 'A' + 27;
    }
    else
    {
        return c - 'a' + 1;
    }

    return 0;
}

int misplaced(const std::string& line)
{
    std::string c1 = line.substr(0, line.length() / 2);
    std::string c2 = line.substr(line.length() / 2);

    for (auto c : c1)
    {
        if (c2.find(c) != std::string::npos)
        {
            return value(c);
        }
    }

    return 0;
}

int badge(const std::vector<std::string>& lines)
{
    for (auto c : lines[0])
    {
        if (lines[1].find(c) != std::string::npos)
        {
            if (lines[2].find(c) != std::string::npos)
            {
                return value(c);
            }
        }
    }

    return 0;
}

int main(void)
{
    std::string line;
    std::vector<std::string> lines;
    int priority1 = 0, priority2 = 0;

    while (!std::getline(std::cin, line).eof())
    {
        priority1 += misplaced(line);

        lines.push_back(line);

        if (lines.size() == 3)
        {
            priority2 += badge(lines);
            lines.clear();
        }
    }

    std::cout << priority1 << "\n" << priority2 << std::endl;
    return 0;
}
