// https://adventofcode.com/2022/day/5

#include <iostream>
#include <list>
#include <vector>

static std::ostream& operator<<(std::ostream& os,
        const std::vector<std::list<char>>& stacks)
{
    for (auto s : stacks)
    {
        std::cout << s.front();
    }

    return os;
}

int main(void)
{
    std::string line;
    std::vector<std::list<char>> stacks1, stacks2;

    while (!std::getline(std::cin, line).eof())
    {
        if (line.empty())
        {
            break;
        }

        for (size_t i = 0; 4 * i < line.length(); i++)
        {
            if (line[4 * i] == '[')
            {
                if (stacks1.size() < i + 1)
                {
                    stacks1.resize(i + 1);
                }

                stacks1[i].push_back(line[4 * i + 1]);
            }
        }
    }

    stacks2 = stacks1;

    std::string move, from, to;
    int n, src, dst;

    while (!(std::cin >> move >> n >> from >> src >> to >> dst).eof())
    {
        std::list<char> t;

        for (int i = 0; i < n; i++)
        {
            stacks1[dst - 1].push_front(stacks1[src - 1].front());
            stacks1[src - 1].pop_front();

            t.push_back(stacks2[src - 1].front());
            stacks2[src - 1].pop_front();
        }

        while (t.size() > 0)
        {
            stacks2[dst - 1].push_front(t.back());
            t.pop_back();
        }
    }

    std::cout << stacks1 << "\n" << stacks2 << std::endl;
    return 0;
}
