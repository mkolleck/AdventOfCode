// https://adventofcode.com/2020/day/3

#include <iostream>
#include <vector>

typedef std::vector<std::vector<bool>> Map;

int findTrees(const Map& map, int dx, int dy)
{
    int x = 0;
    int trees = 0;

    for (int y = 0; y < map.size(); y += dy)
    {
        auto& row = map[y];

        if (row[x])
        {
            trees++;
        }

        x = (x + dx) % row.size();
    }

    return trees;
}

int main(void)
{
    std::string line = "";
    std::vector<std::vector<bool>> map;

    while (!(std::getline(std::cin, line)).eof())
    {
        std::vector<bool> row;

        for (auto c : line)
        {
            switch (c)
            {
                case '.':
                    row.push_back(false);
                    break;

                case '#':
                    row.push_back(true);
                    break;

                default:
                    std::cerr << "Invalid character: " << (int)(c)
                        << std::endl;
                    return 1;
            }
        }

        map.push_back(row);
    }

    int product = findTrees(map, 3, 1);

    std::cout << "Total (part 1): " << product << std::endl;

    product *= findTrees(map, 1, 1);
    product *= findTrees(map, 5, 1);
    product *= findTrees(map, 7, 1);
    product *= findTrees(map, 1, 2);

    std::cout << "Product (part 2): " << product << std::endl;

    return 0;
}
