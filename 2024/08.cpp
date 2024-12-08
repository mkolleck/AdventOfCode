// https://adventofcode.com/2024/day/8

#include <iostream>
#include <limits>
#include <map>
#include <set>
#include <vector>

typedef std::pair<int, int> Point;

static void findAntinodes(std::set<Point>& antinodes, Point p, int dx, int dy,
        int maxX, int maxY, size_t limit)
{
    for (size_t i = 0; i < limit; i++)
    {
        if ((p.first + dx >= 0) && (p.first + dx < maxX)
                && (p.second + dy >= 0) && (p.second + dy < maxY))
        {
            p = Point(p.first + dx, p.second + dy);
            antinodes.insert(p);
        }
        else
        {
            break;
        }
    }
}

static void findAntinodes(std::set<Point>& antinodes,
        Point p1, Point p2, int maxX, int maxY, size_t limit)
{
    int dx = p2.first - p1.first;
    int dy = p2.second - p1.second;

    findAntinodes(antinodes, p1, -dx, -dy, maxX, maxY, limit);
    findAntinodes(antinodes, p2, dx, dy, maxX, maxY, limit);
}

int main(void)
{
    std::map<char, std::vector<Point>> antennas;
    int maxX = 0, maxY = 0;

    std::string line;

    while (!std::getline(std::cin, line).eof())
    {
        for (int x = 0; (size_t)(x) < line.length(); x++)
        {
            if (line[x] != '.')
            {
                antennas[line[x]].push_back(std::make_pair(x, maxY));
            }
        }

        maxX = line.length();
        maxY++;
    }

    std::set<Point> antinodes1;
    std::set<Point> antinodes2;

    for (const auto& a : antennas)
    {
        for (size_t i = 0 ; i < a.second.size() - 1; i++)
        {
            for (size_t j = i + 1; j < a.second.size(); j++)
            {
                findAntinodes(antinodes1, a.second[i], a.second[j],
                        maxX, maxY, 1);

                antinodes2.insert(a.second[i]);
                antinodes2.insert(a.second[j]);
                findAntinodes(antinodes2, a.second[i], a.second[j],
                        maxX, maxY, std::numeric_limits<size_t>::max());
            }
        }
    }

    std::cout << antinodes1.size() << std::endl
        << antinodes2.size() << std::endl;
    return 0;
}
