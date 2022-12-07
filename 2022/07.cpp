// https://adventofcode.com/2022/day/7

#include <iostream>
#include <list>
#include <map>
#include <sstream>

static std::string path(const std::list<std::string>& fs)
{
    std::string result;

    for (auto d : fs)
    {
        result += '/' + d;
    }

    if (result.empty())
    {
        return "/";
    }

    return result;
}

int main(void)
{
    std::string line, a, b, c;
    std::list<std::string> fs;
    std::map<std::string, size_t> directories;

    while (!std::getline(std::cin, line).eof())
    {
        std::istringstream(line) >> a >> b >> c;

        if (a == "$")
        {
            if (b == "cd")
            {
                if (c == "/")
                {
                    fs.clear();
                }
                else if (c == "..")
                {
                    fs.pop_back();
                }
                else
                {
                    fs.push_back(c);
                }
            }
        }
        else
        {
            if (a != "dir")
            {
                size_t s = std::stol(a);
                std::list<std::string> d(fs);

                while (!d.empty())
                {
                    directories[path(d)] += s;
                    d.pop_back();
                }

                directories["/"] += s;
            }
        }
    }

    size_t neededSpace = 30000000 - (70000000 - directories["/"]);
    size_t sum = 0, smallest = 0;

    for (auto d : directories)
    {
        if (d.second < 100000)
        {
            sum += d.second;
        }

        if ((d.second > neededSpace)
                && ((smallest == 0) || (d.second < smallest)))
        {
            smallest = d.second;
        }
    }

    std::cout << sum << "\n" << smallest << std::endl;
    return 0;
}
