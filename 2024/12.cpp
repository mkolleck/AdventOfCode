// https://adventofcode.com/2024/day/12

#include <iostream>
#include <limits>
#include <map>
#include <set>

enum Direction { North, East, South, West };

typedef std::pair<size_t, size_t> Location;

static Location nowhere(size_t(-1), size_t(-1));
static Location end(0, 0);

static Location go(const Location& l, Direction d)
{
    if (l == nowhere)
    {
        return nowhere;
    }

    switch (d)
    {
        case North:
            if (l.second > 0)
            {
                return Location(l.first, l.second - 1);
            }
            break;

        case East:
            if (l.first < end.first - 1)
            {
                return Location(l.first + 1, l.second);
            }
            break;

        case South:
            if (l.second < end.second - 1)
            {
                return Location(l.first, l.second + 1);
            }
            break;

        case West:
            if (l.first > 0)
            {
                return Location(l.first - 1, l.second);
            }
            break;
    }

    return nowhere;
}

struct Plot
{
    Plot(char plant = 0) :
        plant(plant),
        fence(),
        origin(Location(nowhere))
    {
    }

    char plant;
    std::set<Direction> fence;
    Location origin;
};

typedef std::map<Location, Plot> Garden;

static Garden garden;

struct Region
{
    size_t area;
    size_t fence;
    size_t sides;
};

typedef std::map<Location, Region> Regions;

static Regions regions;

static void getFence(const Location& l)
{
    Plot& p = garden[l];

    for (int d = North; d <= West; d++)
    {
        Location n = go(l, (Direction)(d));

        if ((n == nowhere) || (garden[n].plant != p.plant))
        {
            p.fence.insert((Direction)(d));
        }
    }
}

static void findOrigin(const Location& l);

static void checkNeighbor(Plot& p, const Location& l)
{
    Plot& o = garden[l];

    if (o.origin == nowhere)
    {
        o.origin = p.origin;
        findOrigin(l);
    }
}

static void findOrigin(const Location& l)
{
    Plot& p = garden[l];

    if (p.origin == nowhere)
    {
        p.origin = l;
    }

    for (int d = North; d <= West; d++)
    {
        Location n = go(l, (Direction)(d));

        if ((n != nowhere) && (garden[n].plant == p.plant))
        {
            checkNeighbor(p, n);
        }
    }
}

int main(void)
{
    size_t result1 = 0, result2 = 0;
    std::string line;

    while (!std::getline(std::cin, line).eof())
    {
        end.first = 0;

        for (const auto& plant : line)
        {
            garden[end] = Plot(plant);
            end.first++;
        }

        end.second++;
    }

    for (size_t y = 0; y < end.second; y++)
    {
        for (size_t x = 0; x < end.first; x++)
        {
            getFence(Location(x, y));
        }
    }

    for (size_t y = 0; y < end.first; y++)
    {
        for (size_t x = 0; x < end.first; x++)
        {
            findOrigin(Location(x, y));
        }
    }

    for (size_t y = 0; y < end.second; y++)
    {
        for (size_t x = 0; x < end.first; x++)
        {
            Plot& p = garden[Location(x, y)];
            Region& r = regions[p.origin];
            r.area++;
            r.fence += p.fence.size();
        }
    }

    for (const auto& r : regions)
    {
        result1 += r.second.area * r.second.fence;
    }

    std::cout << result1 << std::endl << result2 << std::endl;
    return 0;
}
