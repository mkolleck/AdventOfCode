// https://adventofcode.com/2020/day/24

#include <iostream>
#include <set>

typedef std::pair<int, int> Tile;
typedef std::set<Tile> Tiles;

Tiles neighbors(const Tile& t)
{
    Tiles result;
    result.insert(std::make_pair(t.first - 1, t.second));
    result.insert(std::make_pair(t.first + 1, t.second));
    result.insert(std::make_pair(t.first, t.second + 1));
    result.insert(std::make_pair(t.first, t.second - 1));
    result.insert(std::make_pair(t.first - 1, t.second + 1));
    result.insert(std::make_pair(t.first + 1, t.second - 1));
    return result;
}

inline bool isBlack(const Tiles& tiles, const Tile& t)
{
    return tiles.find(t) != tiles.end();
}

int main(void)
{
    Tiles tiles;
    std::string line;

    while (!(std::getline(std::cin, line)).eof())
    {
        Tile t;

        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == 'e')
            {
                t.first++;
            }
            else if (line[i] == 'w')
            {
                t.first--;
            }
            else if ((line[i] == 'n') && (line[i + 1] == 'e'))
            {
                t.second++; i++;
            }
            else if ((line[i] == 's') && (line[i + 1] == 'w'))
            {
                t.second--; i++;
            }
            else if ((line[i] == 'n') && (line[i + 1] == 'w'))
            {
                t.first--; t.second++; i++;
            }
            else if ((line[i] == 's') && (line[i + 1] == 'e'))
            {
                t.first++, t.second--, i++;
            }
        }

        if (tiles.find(t) == tiles.end()) tiles.insert(t);
        else tiles.erase(t);
    }

    std::cout << tiles.size() << std::endl;

    for (int i = 0; i < 100; i++)
    {
        Tiles toErase;
        Tiles toInsert;

        for (const auto& t : tiles)
        {
            int b1 = 0;

            for (const auto& n1 : neighbors(t))
            {
                if (isBlack(tiles, n1)) b1++;
                else
                {
                    int b2 = 0;
                    for (const auto& n2 : neighbors(n1)) if (isBlack(tiles, n2)) b2++;
                    if (b2 == 2) toInsert.insert(n1);
                }
            }

            if ((b1 == 0) || (b1 > 2)) toErase.insert(t);
        }

        for (const auto& p : toErase) tiles.erase(p);
        for (const auto& p : toInsert) tiles.insert(p);
    }

    std::cout << tiles.size() << std::endl;
    return 0;
}
