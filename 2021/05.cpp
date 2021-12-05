// https://adventofcode.com/2021/day/5

#include <cstring>
#include <iostream>
#include <regex>
#include <vector>

#define SIZE 1000

int main(void)
{
    int sea1[SIZE][SIZE];
    int sea2[SIZE][SIZE];
    std::memset(sea1, 0, sizeof(sea1));
    std::memset(sea2, 0, sizeof(sea2));

    std::string line;

    while (!std::getline(std::cin, line).eof())
    {
        std::istringstream s(std::regex_replace(line, std::regex(","), " "));
        int x1, y1, x2, y2;
        std::string arrow;

        s >> x1 >> y1 >> arrow >> x2 >> y2;

        if (x1 == x2)
        {
            for (int i = std::min(y1, y2); i <= std::max(y1, y2); i++)
            {
                sea1[x1][i]++;
                sea2[x1][i]++;
            }
        }
        else if (y1 == y2)
        {
            for (int i = std::min(x1, x2); i <= std::max(x1, x2); i++)
            {
                sea1[i][y1]++;
                sea2[i][y1]++;
            }
        }
        else
        {
            if (x1 > x2)
            {
                std::swap(x1, x2);
                std::swap(y1, y2);
            }

            for (int i = x1, j = y1; i <= x2; i++)
            {
                sea2[i][j]++;

                if (y2 > y1)
                {
                    j++;
                }
                else
                {
                    j--;
                }
            }
        }
    }

    int danger1 = 0, danger2 = 0;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (sea1[i][j] > 1)
            {
                danger1++;
            }

            if (sea2[i][j] > 1)
            {
                danger2++;
            }
        }
    }

    std::cout << danger1 << "\n" << danger2 << std::endl;
    return 0;
}
