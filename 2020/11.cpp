// https://adventofcode.com/2020/day/11

#include <iostream>
#include <vector>

struct Board
{
    std::string b;
    int h;
    int w;

    char at(int x, int y) const
    {
        if ((0 <= x) && (x < w) && (0 <= y) && (y < h))
        {
            return b[y * w + x];
        }

        return '_';
    }
};

int occupied(const Board& b, int x, int y, int limit)
{
    static const char xo[] = { -1,  0,  1, -1, 1, -1, 0, 1 };
    static const char yo[] = { -1, -1, -1,  0, 0,  1, 1, 1 };
    int o = 0;

    for (int i = 0; i < sizeof(xo); i++)
    {
        for (int d = 1; d <= limit; d++)
        {
            char c = b.at(x + d * xo[i], y + d * yo[i]);

            if (c == '.')
            {
                continue;
            }
            else if (c == '#')
            {
                o++;
            }

            break;
        }
    }
    
    return o;
}

Board iterate(const Board& board, int limit, int tolerance)
{
    Board next;
    next.w = board.w;
    next.h = board.h;

    for (int y = 0; y < board.h; y++)
    {
        for (int x = 0; x < board.w; x++)
        {
            char c = board.b[y * board.w + x];

            if (c == '.')
            {
                next.b += c;
                continue;
            }

            int o = occupied(board, x, y, limit);

            if ((c == 'L') && (o == 0))
            {
                next.b += '#';
            }
            else if ((c == '#') && (o >= tolerance))
            {
                next.b += 'L';
            }
            else
            {
                next.b += c;
            }
        }
    }

    return next;
}

static int analyze(const Board& board, int limit, int tolerance)
{
    int occupied = 0;
    Board a, b = board;

    do
    {
        a = b;
        b = iterate(a, limit, tolerance);
    }
    while (a.b != b.b);

    for (const auto& c : b.b)
    {
        if (c == '#')
        {
            occupied++;
        }
    }

    return occupied;
}

int main(void)
{
    std::string line;
    Board board;

    while (!(std::getline(std::cin, line)).eof())
    {
        if (board.w == 0)
        {
            board.w = line.length();
        }

        board.b += line;
        board.h++;
    }

    std::cout << analyze(board, 1, 4) << std::endl;
    std::cout << analyze(board, board.w, 5) << std::endl;
    return 0;
}
