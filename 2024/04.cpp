#include <iostream>

static const char xmas[4] = { 'X', 'M', 'A', 'S' };

static std::string puzzle;
static int xmax = 0, ymax = 0;

static int findXMAS1(int x, int y, int dx, int dy, int n)
{
    if (puzzle[y * xmax + x] == xmas[n])
    {
        if (n == sizeof(xmas) - 1)
        {
            return 1;
        }

        if ((x + dx < 0) || (x + dx >= xmax)
                || (y + dy < 0) || (y + dy >= ymax))
        {
            return 0;
        }

        return findXMAS1(x + dx, y + dy, dx, dy, n + 1);
    }

    return 0;
}

static int findXMAS2(int x, int y)
{
    if (puzzle[y * xmax + x] != 'A')
    {
        return 0;
    }

    if ((x == 0) || (x == xmax - 1)
            || (y == 0) || (y == ymax - 1))
    {
        return 0;
    }

    if ((((puzzle[(y - 1) * xmax + x - 1] == 'M')
                    && (puzzle[(y + 1) * xmax + x + 1] == 'S'))
                || ((puzzle[(y - 1) * xmax + x - 1] == 'S')
                    && (puzzle[(y + 1) * xmax + x + 1] == 'M')))
            && (((puzzle[(y - 1) * xmax + x + 1] == 'M')
                    && (puzzle[(y + 1) * xmax + x - 1] == 'S'))
                || ((puzzle[(y - 1) * xmax + x + 1] == 'S')
                    && (puzzle[(y + 1) * xmax + x - 1] == 'M'))))
    {
        return 1;
    }

    return 0;
}

int main(void)
{
    int xmasses1 = 0;
    int xmasses2 = 0;

    std::string line;

    while (!std::getline(std::cin, line).eof())
    {
        puzzle += line;
        xmax = line.length();
        ymax++;
    }

    for (int y = 0; y < ymax; y++)
    {
        for (int x = 0; x < xmax; x++)
        {
            xmasses1 += findXMAS1(x, y, -1, -1, 0);
            xmasses1 += findXMAS1(x, y,  0, -1, 0);
            xmasses1 += findXMAS1(x, y,  1, -1, 0);
            xmasses1 += findXMAS1(x, y, -1,  0, 0);
            xmasses1 += findXMAS1(x, y,  1,  0, 0);
            xmasses1 += findXMAS1(x, y, -1,  1, 0);
            xmasses1 += findXMAS1(x, y,  0,  1, 0);
            xmasses1 += findXMAS1(x, y,  1,  1, 0);

            xmasses2 += findXMAS2(x, y);
        }
    }

    std::cout << xmasses1 << std::endl;
    std::cout << xmasses2 << std::endl;
    return 0;
}
