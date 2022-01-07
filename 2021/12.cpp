// https://adventofcode.com/2021/day/12

#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <set>

typedef std::list<std::string> Visited;

static std::map<std::string, std::set<std::string>> map;
static std::set<Visited> taken;

static int backtrack1(const std::string& start, Visited visited)
{
    int paths = 0;
    visited.push_back(start);

    for (const auto& d : map.at(start))
    {
        if (d == "end")
        {
            paths++;
        }
        else if ((isupper(d[0]))
                || (std::find(visited.begin(), visited.end(), d) == visited.end()))
        {
            paths += backtrack1(d, visited);
        }
    }

    return paths;
}

static int backtrack2(const std::string& start, Visited visited,
        const std::string& small, bool twice)
{
    visited.push_back(start);

    for (const auto& d : map.at(start))
    {
        if (d == "start")
        {
            // continue;
        }
        else if (d == "end")
        {
            taken.insert(visited);
        }
        else if (isupper(d[0]))
        {
            backtrack2(d, visited, small, twice);
        }
        else if (std::find(visited.begin(), visited.end(), d) == visited.end())
        {
            backtrack2(d, visited, small, twice);

            if (small.empty())
            {
                backtrack2(d, visited, d, twice);
            }
        }
        else if ((d == small) && !twice)
        {
            backtrack2(d, visited, small, true);
        }
    }

    return taken.size();
}

int main(void)
{
    std::string start, end;

    for (;;)
    {
        std::getline(std::cin, start, '-');
        std::getline(std::cin, end);

        if (std::cin.eof())
        {
            break;
        }

        map[start].insert(end);
        map[end].insert(start);
    }

    std::cout << backtrack1("start", Visited()) << std::endl;
    std::cout << backtrack2("start", Visited(), "", false) << std::endl;
    return 0;
}
