// https://adventofcode.com/YYYY/day/DD

#include <iostream>
#include <set>
#include <vector>

typedef std::vector<std::string> Map;
typedef std::set<std::pair<size_t, size_t>> Visited;

static int findTrail(const Map& map, Visited& visited, size_t x, size_t y)
{
    int result = 0;

    if (map[y][x] == '9')
    {
        visited.insert(std::make_pair(x, y)).second;
        return 1;
    }

    if ((x > 0) && (map[y][x - 1] == map[y][x] + 1))
    {
        result += findTrail(map, visited, x - 1, y);
    }

    if ((y > 0) && (map[y - 1][x] == map[y][x] + 1))
    {
        result += findTrail(map, visited, x, y - 1);
    }

    if ((x < map.size() - 1)
            && (map[y][x + 1] == map[y][x] + 1))
    {
        result += findTrail(map, visited, x + 1, y);
    }

    if ((y < map.size() - 1)
            && (map[y + 1][x] == map[y][x] + 1))
    {
        result += findTrail(map, visited, x, y + 1);
    }

    return result;
}

int main(void)
{
    size_t result1 = 0, result2 = 0;
    Map map;

    std::string line;

    while (!std::getline(std::cin, line).eof())
    {
        map.push_back(line);
    }

    for (size_t y = 0; y < map.size(); y++)
    {
        for (size_t x = 0; x < map.size(); x++)
        {
            if (map[y][x] == '0')
            {
                Visited visited;
                result2 += findTrail(map, visited, x, y);
                result1 += visited.size();
            }
        }
    }

    std::cout << result1 << std::endl << result2 << std::endl;
    return 0;
}
