// https://adventofcode.com/2021/day/14

#include <iostream>
#include <map>

static std::string polymer;
static std::map<char, std::map<char, char>> rules;

typedef std::tuple<char, char, int> Key;
typedef std::map<char, size_t> Counts;
typedef std::map<Key, Counts> Cache;
static Cache cache;

static void count(Counts& totals, const Counts& counts)
{
    for (auto c : counts)
    {
        totals[c.first] += c.second;
    }
}

static void count(char c1, char c2, int iterations, Counts& counts)
{
    if (iterations == 0)
    {
        return;
    }

    Cache::const_iterator i = cache.find({ c1, c2, iterations });

    if (i != cache.end())
    {
        count(counts, i->second);
        return;
    }

    Counts c;
    c[rules[c1][c2]]++;

    count(c1, rules[c1][c2], iterations - 1, c);
    count(rules[c1][c2], c2, iterations - 1, c);
    count(counts, c);

    cache[{ c1, c2, iterations }] = c;
}

void exec(int iterations)
{
    size_t maxCount = 0, minCount = 0;
    Counts counts;

    for (int i = 0; i < polymer.length() - 1; i++)
    {
        counts[polymer[i]]++;
        count(polymer[i], polymer[i + 1], iterations, counts);
    }

    counts[polymer[polymer.length() - 1]]++;

    for (auto c : counts)
    {
        if ((c.second < minCount) || (minCount == 0))
        {
            minCount = c.second;
        }

        if (c.second > maxCount)
        {
            maxCount = c.second;
        }
    }

    std::cout << maxCount - minCount << std::endl;
}

int main(int argc, char** argv)
{
    std::string from, to;

    std::getline(std::cin, polymer);
    std::getline(std::cin, from); // skip empty line

    while (!(std::cin >> from >> to >> to).eof())
    {
        rules[from[0]][from[1]] = to[0];
    }

    exec(10);
    exec(40);
    return 0;
}
