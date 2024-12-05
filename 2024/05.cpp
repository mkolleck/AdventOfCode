// https://adventofcode.com/2024/day/5

#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

static std::set<std::pair<int, int>> rules;

struct Page
{
    int p;

    Page(int p) : p(p) { }

    bool operator<(const Page& o) const
    {
        if (rules.find(std::make_pair(p, o.p)) != rules.end())
        {
            return true;
        }

        return false;
    }
};

int main(void)
{
    size_t result1 = 0, result2 = 0;

    std::string line;
    int a, b;
    char sep;

    do
    {
        std::getline(std::cin, line);
        std::istringstream s(line);
        s >> a >> sep >> b;
        rules.insert(std::make_pair(a, b));
    }
    while (!line.empty());

    while (!std::getline(std::cin, line).eof())
    {
        std::istringstream s(line);
        std::vector<Page> pages;
        bool sorted = true;

        s >> a;
        pages.push_back(a);

        while (s.good())
        {
            s >> sep >> b;
            pages.push_back(b);

            if (!(Page(a) < Page(b)))
            {
                sorted = false;
            }

            a = b;
        }

        if (sorted)
        {
            result1 += pages[pages.size() / 2].p;
        }
        else
        {
            std::sort(pages.begin(), pages.end());
            result2 += pages[pages.size() / 2].p;
        }
    }

    std::cout << result1 << std::endl << result2 << std::endl;
    return 0;
}
