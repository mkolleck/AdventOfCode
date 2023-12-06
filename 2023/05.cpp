// https://adventofcode.com/2023/day/5

#include <algorithm>
#include <iostream>
#include <list>
#include <sstream>

struct Seed
{
    size_t seed;
    size_t range;

    size_t first(void) const
    {
        return seed;
    }

    size_t last(void) const
    {
        return seed + range - 1;
    }

    bool operator<(const struct Seed& s) const
    {
        return seed < s.seed;
    }
};

struct Entry
{
    size_t source;
    size_t destination;
    size_t range;

    size_t first(void) const
    {
        return source;
    }

    size_t last(void) const
    {
        return source + range - 1;
    }

    size_t map(size_t s) const
    {
        return destination + (s - source);
    }

    bool operator<(const struct Entry& e) const
    {
        return source < e.source;
    }
};

typedef std::list<Seed> Seeds;
typedef std::list<Entry> Map;

static Seeds map(Seeds& seeds, Map& map)
{
    seeds.sort();
    map.sort();

    Seeds result;
    Map::const_iterator mi = map.begin();

    while (seeds.size() > 0)
    {
        Seed& s = seeds.front();

        if (mi == map.end())
        {
            result.push_back(s);
            seeds.pop_front();
        }
        else if (mi->last() < s.first())
        {
            // |-- map --|
            //            |-- seed --|
            mi++;
        }
        else if (s.last() < mi->first())
        {
            //             |-- map --|
            // |-- seed --|
            result.push_back(s);
            seeds.pop_front();
        }
        else if ((mi->first() <= s.first()) && (s.last() <= mi->last()))
        {
            // |-- map ---|
            // |-- seed --|
            result.push_back(Seed({mi->map(s.seed), s.range}));
            seeds.pop_front();
        }
        else if ((mi->first() <= s.first()) && (mi->last() < s.last()))
        {
            // |-- map --|
            // |--- seed ---|
            size_t outside = s.last() - mi->last();
            result.push_back(Seed({mi->map(s.seed), s.range - outside}));
            seeds.pop_front();
            seeds.push_front(Seed({s.seed + s.range - outside, outside}));
        }
        else if (s.first() < mi->first())
        {
            // seed range overlaps beginning of map range
            //    |-- map --|
            // |--- seed -----|
            size_t outside = mi->first() - s.first();
            result.push_back(Seed({s.seed, outside}));
            seeds.pop_front();
            seeds.push_front(Seed({s.seed + outside, s.range - outside}));
        }
    }

    return result;
}

int main(void)
{
    Seeds seeds1, seeds2;
    Map map;
    std::string dummy, line;

    std::cin >> dummy /* seeds: */;

    while (true)
    {
        size_t seed1, seed2;
        std::cin >> seed1 >> seed2;

        if (std::cin.good())
        {
            seeds1.push_back(Seed({seed1, 1}));
            seeds1.push_back(Seed({seed2, 1}));
            seeds2.push_back(Seed({seed1, seed2}));
        }
        else
        {
            break;
        }
    }

    std::cin.clear();

    while (!std::getline(std::cin, line).eof())
    {
        if (line.empty())
        {
            seeds1 = ::map(seeds1, map);
            seeds2 = ::map(seeds2, map);
            continue;
        }
        else if (line.back() == ':')
        {
            map.clear();
            continue;
        }

        std::istringstream in(line);
        Entry e;
        in >> e.destination >> e.source >> e.range;
        map.push_back(e);
    }

    seeds1 = ::map(seeds1, map);
    seeds2 = ::map(seeds2, map);
    seeds1.sort();
    seeds2.sort();
    std::cout << seeds1.front().seed << std::endl;
    std::cout << seeds2.front().seed << std::endl;
    return 0;
}
