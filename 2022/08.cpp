// https://adventofcode.com/2022/day/8

#include <iostream>
#include <vector>

struct Tree
{
    int height;
    bool visible;
};

int main(void)
{
    std::string line;
    static std::vector<std::vector<Tree>> map;
    int visible = 0, maxScore = 0;

    while (!std::getline(std::cin, line).eof())
    {
        std::vector<Tree> row;

        for (auto c : line)
        {
            row.push_back({ c - '0', false });
        }

        map.push_back(row);
    }

    int dim = map.size();

    for (int r1 = 0; r1 < dim; r1++)
    {
        int r1max = 0, r2max = 0, c1max = 0, c2max = 0;

        for (int c1 = 0; c1 < dim; c1++)
        {
            int score = 1, sc1 = 0, sc2 = 0, sr1 = 0, sr2 = 0;
            int c2 = dim - c1 - 1;

            if ((c1 == 0) || (map.at(r1).at(c1).height > c1max))
            {
                map.at(r1).at(c1).visible = true;
                c1max = map.at(r1).at(c1).height;
            }

            if ((c1 == 0) || (map.at(r1).at(c2).height > c2max))
            {
                map.at(r1).at(c2).visible = true;
                c2max = map.at(r1).at(c2).height;
            }

            if ((c1 == 0) || (map.at(c1).at(r1).height > r1max))
            {
                map.at(c1).at(r1).visible = true;
                r1max = map.at(c1).at(r1).height;
            }

            if ((c1 == 0) || (map.at(c2).at(r1).height > r2max))
            {
                map.at(c2).at(r1).visible = true;
                r2max = map.at(c2).at(r1).height;
            }

            for (int c = c1 - 1; c >= 0; c--)
            {
                if ((map.at(r1).at(c1).height <= map.at(r1).at(c).height)
                        || (c == 0))
                {
                    sc1 = c1 - c;
                    break;
                }
            }

            for (int c = c1 + 1; c < dim; c++)
            {
                if ((map.at(r1).at(c1).height <= map.at(r1).at(c).height)
                        || (c == dim - 1))
                {
                    sc2 = c - c1;
                    break;
                }
            }

            for (int r = r1 - 1; r >= 0; r--)
            {
                if ((map.at(r1).at(c1).height <= map.at(r).at(c1).height)
                        || (r == 0))
                {
                    sr1 = r1 - r;
                    break;
                }
            }

            for (int r = r1 + 1; r < dim; r++)
            {
                if ((map.at(r1).at(c1).height <= map.at(r).at(c1).height)
                        || (r == dim - 1))
                {
                    sr2 = r - r1;
                    break;
                }
            }

            score = sc1 * sc2 * sr1 * sr2;

            if (score > maxScore)
            {
                maxScore = score;
            }
        }
    }

    for (int r = 0; r < dim; r++)
    {
        for (int c = 0; c < dim; c++)
        {
            if (map.at(r).at(c).visible)
            {
                visible++;
            }
        }
    }

    std::cout << visible << "\n" << maxScore << std::endl;
    return 0;
}
