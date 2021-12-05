// https://adventofcode.com/2021/day/4

#include <iostream>
#include <regex>
#include <vector>

struct Board
{
    union
    {
        int array[25];
        int number[5][5];
    };

    bool marked[5][5];
    bool won;

    Board() :
        won(false)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                number[i][j] = 0;
                marked[i][j] = false;
            }
        }
    }

    operator bool() const
    {
        for (int i = 0; i < 5; i++)
        {
            if ((marked[i][0] && marked[i][1] && marked[i][2]
                    && marked[i][3] && marked[i][4])
                || (marked[0][i] && marked[1][i] && marked[2][i]
                        && marked[3][i] && marked[4][i]))
            {
                return true;
            }
        }

        return false;
    }

    operator int() const
    {
        int result = 0;

        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (!marked[i][j])
                {
                    result += number[i][j];
                }
            }
        }

        return result;
    }

    void mark(int n)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (number[i][j] == n)
                {
                    marked[i][j] = true;
                }
            }
        }
    }
};

int main(void)
{
    std::string numbers;
    std::cin >> numbers;

    std::vector<Board> boards;
    Board board;
    int b, c = 0;

    while (!(std::cin >> b).eof())
    {
        board.array[c] = b;
        c++;

        if (c == 25)
        {
            boards.push_back(board);
            c = 0;
        }
    }

    std::istringstream s(
            std::regex_replace(numbers, std::regex(","), " ") + " ");
    int winner = 0, draw;

    while (!(s >> draw).eof())
    {
        for (auto& b : boards)
        {
            if (!b.won)
            {
                b.mark(draw);
            }
        }

        for (auto& b : boards)
        {
            if (!b.won && b)
            {
                if ((winner == 0) || (winner == boards.size() - 1))
                {
                    std::cout << (int)(b) * draw << std::endl;
                }

                b.won = true;
                winner++;
            }
        }
    }

    return 0;
}
