// https://adventofcode.com/2023/day/8

#include <functional>
#include <iostream>
#include <map>
#include <vector>

struct Node
{
    std::string left;
    std::string right;
};

size_t iterate(const std::map<std::string, Node>& map,
        const std::string& steps, const std::string& first,
        bool (last)(const std::string&))
{
    size_t result = 0, step = 0;
    std::string node = first;

    while (!last(node))
    {
        if (steps[step] == 'R')
        {
            node = map.at(node).right;
        }
        else
        {
            node = map.at(node).left;
        }

        if (step + 1 == steps.length())
        {
            step = 0;
        }
        else
        {
            step++;
        }

        result++;
    }

    return result;
}

int main(void)
{
    size_t result1 = 0, result2 = 1;

    std::map<std::string, Node> map;
    std::string steps, node;
    std::cin >> steps;

    while (std::cin.good())
    {
        Node n;
        std::cin >> node >> n.left /* = */ >> n.left >> n.right;
        
        if (std::cin.good())
        {
            n.left = n.left.substr(1, 3);
            n.right = n.right.substr(0, 3);
            map[node] = n;
        }
    }

    if (map.find("ZZZ") != map.end())
    {
        result1 = iterate(map, steps, "AAA",
                [](const std::string& s) { return s == "ZZZ"; });
    }

    std::vector<std::string> nodes;
    std::vector<size_t> counts;

    for (const auto& n : map)
    {
        if (n.first[2] == 'A')
        {
            nodes.push_back(n.first);
            counts.push_back(0);
        }
    }

    for (size_t n = 0; n < nodes.size(); n++)
    {
        counts[n] = iterate(map, steps, nodes[n],
                [](const std::string& s) { return s[2] == 'Z'; });
    }

    std::map<size_t, size_t> allFactors;

    for (size_t n = 0; n < counts.size(); n++)
    {
        std::map<size_t, size_t> factors;
        size_t remainder = counts[n];

        while (remainder != 1)
        {
            for (size_t a = 2; a <= remainder; a++)
            {
                if ((remainder / a) * a == remainder)
                {
                    factors[a]++;
                    remainder /= a;
                    break;
                }
            }
        }

        for (const auto& f : factors)
        {
            if (allFactors[f.first] < f.second)
            {
                allFactors[f.first] = f.second;
            }
        }
    }

    for (const auto& f : allFactors)
    {
        for (size_t i = 0; i < f.second; i++)
        {
            result2 *= f.first;
        }
    }

    std::cout << result1 << std::endl << result2 << std::endl;
    return 0;
}
