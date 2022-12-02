// https://adventofcode.com/2022/day/2

#include <iostream>

int main(void)
{
    char them, mine;
    int score1 = 0, score2 = 0;

    while (!(std::cin >> them >> mine).eof())
    {
        them -= 'A';
        mine -= 'X';

        if (them == mine)
        {
            score1 += 3;
        }
        else if (((them == 0) && (mine == 1))
                || ((them == 1)  && (mine == 2))
                || ((them == 2) && (mine == 0)))
        {
            score1 += 6;
        }

        switch (mine)
        {
            case 0:
                score2 += ((them + 2) % 3) + 1;
                break;

            case 1:
                score2 += (them % 3) + 1;
                break;

            case 2:
                score2 += ((them + 1) % 3) + 1;
                break;
        }

        score1 += mine + 1;
        score2 += 3 * mine;
    }

    std::cout << score1 << "\n" << score2 << std::endl;
    return 0;
}
