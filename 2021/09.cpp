// https://adventofcode.com/2021/day/9

#include <algorithm>
#include <iostream>
#include <vector>

struct Map
{
    int operator()(int r, int c) const
    {
        if ((r < 0) || (r >= rows) || (c < 0) || (c >= cols))
        {
            return 10;
        }

        return m[r * cols + c];
    }

    int& operator()(int r, int c) 
    {
        if ((r < 0) || (r >= rows) || (c < 0) || (c >= cols))
        {
            return oob;
        }

        return m[r * cols + c];
    }

    void add(const std::string& l)
    {
        for (const auto& c : l)
        {
            m.push_back(c - '0');

            if (cols == 0)
            {
                cols = l.length();
            }
        }

        rows++;
    }

    std::vector<int> m;
    int rows = 0;
    int cols = 0;
    int oob = 10;
};

void explore(const Map& m, Map& b, std::vector<int>& basins, int r, int c)
{
    if (m(r, c) >= 9)
    {
        return;
    }

    if (b(r, c) == 0)
    {
        basins.push_back(0);
        b(r, c) = basins.size();
    }

    if ((m(r - 1, c) < 9) && (b(r - 1, c) == 0))
    {
        b(r - 1, c) = basins.size();
        explore(m, b, basins, r - 1, c);
    }

    if ((m(r, c - 1) < 9) && (b(r, c - 1) == 0))
    {
        b(r, c - 1) = basins.size();
        explore(m, b, basins, r, c - 1);
    }

    if ((m(r, c + 1) < 9) && (b(r, c + 1) == 0))
    {
        b(r, c + 1) = basins.size();
        explore(m, b, basins, r, c + 1);
    }

    if ((m(r + 1, c) < 9) && (b(r + 1, c) == 0))
    {
        b(r + 1, c) = basins.size();
        explore(m, b, basins, r + 1, c);
    }
}

int main(void)
{
    Map m, b;
    std::vector<int> basins;
    int risk = 0;
    std::string line;

    while (!std::getline(std::cin, line).eof())
    {
        m.add(line);
    }

    b.m.resize(m.rows * m.cols, 0);
    b.rows = m.rows;
    b.cols = m.cols;

    for (int r = 0; r < m.rows; r++)
    {
        for (int c = 0; c < m.cols; c++)
        {
            if (m(r, c) == 9)
            {
                continue;
            }

            if ((m(r - 1, c) > m(r, c))
                    && (m(r, c - 1) > m(r, c))
                    && (m(r, c + 1) > m(r, c))
                    && (m(r + 1, c) > m(r, c)))
            {
                risk += m(r, c) + 1;
            }

            explore(m, b, basins, r, c);
        }
    }

    for (int r = 0; r < m.rows; r++)
    {
        for (int c = 0; c < m.cols; c++)
        {
            if (b(r, c) > 0)
            {
                basins[b(r, c) - 1]++;
            }
        }
    }

    std::sort(basins.begin(), basins.end(), std::greater<int>());
    std::cout << risk << "\n"
        << basins[0] * basins[1] * basins[2] << std::endl;
    return 0;
}
