// https://adventofcode.com/2020/day/7

#include <iostream>
#include <map>
#include <sstream>
#include <set>

typedef std::map<std::string, int> Contains;
typedef std::set<std::string> ContainedIn;

typedef std::map<std::string, Contains> BagContains;
typedef std::map<std::string, ContainedIn> BagsContainedIn;

static std::string name(const std::string& adjective, const std::string& color)
{
    return adjective + " " + color;
}

static void countContainedIn(ContainedIn& containedIn, const std::string& bag,
        const BagsContainedIn& bagsContainedIn)
{
    BagsContainedIn::const_iterator b = bagsContainedIn.find(bag);

    if (b == bagsContainedIn.end())
    {
        return;
    }

    for (const auto& c : b->second)
    {
        containedIn.insert(c);
        countContainedIn(containedIn, c, bagsContainedIn);
    }
}

static int countContains(const std::string& bag,
        const BagContains& bagContains)
{
    int sum = 1;
    BagContains::const_iterator b = bagContains.find(bag);

    if (b != bagContains.end())
    {
        for (const auto& c : b->second)
        {
            sum += countContains(c.first, bagContains) * c.second;
        }
    }

    return sum;
}

int main(void)
{
    std::string line;
    BagContains bagContains;
    BagsContainedIn bagsContainedIn;

    while (!(std::getline(std::cin, line)).eof())
    {
        std::istringstream s(line);
        std::string adjective, color, literalBags, literalContain;

        s >> adjective >> color >> literalBags >> literalContain;

        if ((literalBags != "bags") || (literalContain != "contain"))
        {
            std::cerr << "Invalid rule: " << line << std::endl;
            return 1;
        }

        Contains contains;

        if (line.find("contain no other bags.") == std::string::npos)
        {
            while (true)
            {
                int num = 0;
                std::string adj, col;

                s >> num >> adj >> col >> literalBags;

                if (literalBags.find("bag") != 0)
                {
                    std::cerr << "Invalid rule: " << line << std::endl;
                    return 2;
                }

                contains[name(adj, col)] = num;

                if (literalBags.find(",") != std::string::npos)
                {
                    continue;
                }
                else if (literalBags.find(".") != std::string::npos)
                {
                    break;
                }

                std::cerr << "Invalid rule: " << line << std::endl;
                return 3;
            }
        }

        bagContains[name(adjective, color)] = contains;
    }

    for (const auto& b : bagContains)
    {
        for (const auto& c : b.second)
        {
            bagsContainedIn[c.first].insert(b.first);
        }
    }

    ContainedIn containedIn;
    countContainedIn(containedIn, "shiny gold", bagsContainedIn);
    std::cout << "shiny gold contained in " << containedIn.size() << std::endl;

    std::cout << "shiny gold contains "
        << countContains("shiny gold", bagContains) - 1 << std::endl;

    return 0;
}
