// https://adventofcode.com/2022/day/6

#include <iostream>
#include <set>

static bool distinct(const std::string& m)
{
    std::set<char> s;

    for (auto c : m)
    {
        s.insert(c);
    }

    return s.size() == m.length();
}

static void process(const std::string& line, int l)
{
    for (size_t i = l; i < line.length(); i++)
    {
        if (distinct(line.substr(i - l, l)))
        {
            std::cout << i << std::endl;
            break;
        }
    }
}

int main(void)
{
    std::string line;

    while (!std::getline(std::cin, line).eof())
    {
        process(line, 4);
        process(line, 14);
    }

    return 0;
}
