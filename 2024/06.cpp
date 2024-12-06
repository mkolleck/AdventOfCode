// https://adventofcode.com/2024/day/6

#include <iostream>
#include <set>
#include <vector>

typedef std::vector<std::string> Map;
typedef std::pair<size_t, size_t> Guard;
enum Direction { North, East, South, West };

typedef std::set<std::pair<Guard, Direction>> Visited;

bool iterate(Map& map, Guard& guard, Direction dir, Visited& visited)
{
    if (!visited.insert(std::make_pair(guard, dir)).second)
    {
        return true;
    }

    switch (dir)
    {
        case North:
            if (guard.first == 0)
            {
                return false;
            }
            else if (map[guard.first - 1][guard.second] == '#')
            {
                dir = East;
            }
            else
            {
                guard.first--;
            }
            break;

        case East:
            if (guard.second == map.size() - 1)
            {
                return false;
            }
            else if (map[guard.first][guard.second + 1] == '#')
            {
                dir = South;
            }
            else
            {
                guard.second++;
            }
            break;

        case South:
            if (guard.first == map.size() - 1)
            {
                return false;
            }
            else if (map[guard.first + 1][guard.second] == '#')
            {
                dir = West;
            }
            else
            {
                guard.first++;
            }
            break;

        case West:
            if (guard.second == 0)
            {
                return false;
            }
            else if (map[guard.first][guard.second - 1] == '#')
            {
                dir = North;
            }
            else
            {
                guard.second--;
            }
            break;
    }

    map[guard.first][guard.second] = 'x';
    return iterate(map, guard, dir, visited);
}

int main(void)
{
    size_t result1 = 0, result2 = 0;
    std::string line;

    Map map;
    Guard guard = std::make_pair(0, std::string::npos);

    while (!std::getline(std::cin, line).eof())
    {
        map.push_back(line);

        size_t g = line.find('^');

        if (g == std::string::npos)
        {
            if (guard.second == std::string::npos)
            {
                guard.first++;
            }
        }
        else
        {
            guard.second = g;
        }
    }

    Map map1 = map;
    Guard guard1 = guard;
    Visited visited;
    iterate(map1, guard1, North, visited);

    for (const auto& m : map1)
    {
        for (const auto& p : m)
        {
            if ((p != '.') && (p != '#'))
            {
                result1++;
            }
        }
    }

    for (size_t first = 0; first < map.size(); first++)
    {
        for (size_t second = 0; second < map.size(); second++)
        {
            Map map2 = map;
            Guard guard2 = guard;
            visited.clear();

            if (map2[first][second] == '.')
            {
                map2[first][second] = '#';

                if (iterate(map2, guard2, North, visited))
                {
                    result2++;
                }
            }
        }
    }

    std::cout << result1 << std::endl << result2 << std::endl;
    return 0;
}
