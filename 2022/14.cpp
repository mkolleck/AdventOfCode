// https://adventofcode.com/2022/day/14

#include <iostream>
#include <map>
#include <sstream>

int main(void)
{
    std::map<std::pair<int, int>, char> map;
    int bottom = 0, grains = 0;
    bool stage1 = true;

    std::string line;
    std::pair<int, int> p1, p2;
    char comma;

    while (!std::getline(std::cin, line).eof())
    {
        std::istringstream s(line);

        while (true)
        {
            s >> p2.first >> comma >> p2.second;

            if (p2.second > bottom)
            {
                bottom = p2.second;
            }

            if (p1 != std::pair<int, int>({ 0, 0 }))
            {
                if (p1.first == p2.first)
                {
                    if (p1.second < p2.second)
                    {
                        for (int y = p1.second; y <= p2.second; y++)
                        {
                            map[{p1.first, y}] = '#';
                        }
                    }
                    else
                    {
                        for (int y = p2.second; y <= p1.second; y++)
                        {
                            map[{p1.first, y}] = '#';
                        }
                    }
                }

                if (p1.second == p2.second)
                {
                    if (p1.first < p2.first)
                    {
                        for (int x = p1.first; x <= p2.first; x++)
                        {
                            map[{x, p1.second}] = '#';
                        }
                    }
                    else
                    {
                        for (int x = p2.first; x <= p1.first; x++)
                        {
                            map[{x, p1.second}] = '#';
                        }
                    }
                }
            }

            if (s.eof())
            {
                p1 = { 0, 0 };
                break;
            }

            s >> line;
            p1 = p2;
        }
    }

    while (true)
    {
        std::pair<int, int> sand = { 500, 0 };

        while (true)
        {
            bool dropped = false;

            if (map.find({sand.first, sand.second + 1}) == map.end())
            {
                sand.second++;
                dropped = true;
            }
            else if (map.find({sand.first - 1, sand.second + 1}) == map.end())
            {
                sand.first--;
                sand.second++;
                dropped = true;
            }
            else if (map.find({sand.first + 1, sand.second + 1}) == map.end())
            {
                sand.first++;
                sand.second++;
                dropped = true;
            }

            if (dropped && stage1 && (sand.second == bottom))
            {
                std::cout << grains << std::endl;
                stage1 = false;
            }

            if (!dropped || (sand.second == bottom + 1))
            {
                map[sand] = 'o';
                grains++;

                if (sand == std::pair<int, int>({500, 0}))
                {
                    std::cout << grains << std::endl;
                }

                break;
            }
        }

        if (sand == std::pair<int, int>({500, 0}))
        {
            break;
        }
    }

    return 0;
}
