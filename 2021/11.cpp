// https://adventofcode.com/2021/day/11

#include <iostream>
#include <vector>

struct Map
{
    void inc(int r, int c)
    {
        if ((r < 0) || (r >= rows) || (c < 0) || (c >= cols))
        {
            return;
        }

        m[r * cols + c]++;

        if (m[r * cols + c] == 10)
        {
            inc(r - 1, c - 1);
            inc(r - 1, c);
            inc(r - 1, c + 1);
            inc(r, c - 1);
            inc(r, c + 1);
            inc(r + 1, c - 1);
            inc(r + 1, c);
            inc(r + 1, c + 1);
        }
    }

    int iterate(void)
    {
        int flashes = 0;

        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {
                inc(r, c);
            }
        }

        for (auto& i : m) if (i > 9) { i = 0; flashes++; }

        this->flashes += flashes;
        return flashes;
    }

    std::vector<int> m;
    int rows = 0;
    int cols = 0;
    int flashes = 0;
};

int main(void)
{
    Map m;
    std::string line;

    while (!std::getline(std::cin, line).eof())
    {
        for (const auto& c : line)
        {
            m.m.push_back(c - '0');
        }

        if (m.cols == 0)
        {
            m.cols = line.size();
        }

        m.rows++;
    }

    for (int i = 0; ; i++)
    {
        if (m.iterate() == 100)
        {
            std::cout << i + 1 << std::endl;
            break;
        }

        if (i == 99)
        {
            std::cout << m.flashes << std::endl;
        }
    }

    return 0;
}
