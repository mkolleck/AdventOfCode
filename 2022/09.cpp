// https://adventofcode.com/2022/day/9

#include <iostream>
#include <set>

#define ROPE 10

static const std::pair<int, int> move[5][5] =
{
    { { 1,  1 }, { 1,  1 }, { 0,  1 }, { -1,  1 }, { -1,  1 } },
    { { 1,  1 }, { 0,  0 }, { 0,  0 }, {  0,  0 }, { -1,  1 } },
    { { 1,  0 }, { 0,  0 }, { 0,  0 }, {  0,  0 }, { -1,  0 } },
    { { 1, -1 }, { 0,  0 }, { 0,  0 }, {  0,  0 }, { -1, -1 } },
    { { 1, -1 }, { 1, -1 }, { 0, -1 }, { -1, -1 }, { -1, -1 } }
};

int main(void)
{
    char direction;
    int amount;
    std::pair<int, int> rope[ROPE];
    std::set<std::pair<int, int>> visited[ROPE];

    while (!(std::cin >> direction >> amount).eof())
    {
        for (int i = 0; i < amount; i++)
        {
            switch (direction)
            {
                case 'U':
                    rope[0].second++;
                    break;

                case 'D':
                    rope[0].second--;
                    break;

                case 'R':
                    rope[0].first++;
                    break;

                case 'L':
                    rope[0].first--;
                    break;
            }

            for (int i = 1; i < ROPE; i++)
            {
                int dx = rope[i].first -  rope[i - 1].first;
                int dy = rope[i].second - rope[i - 1].second;

                rope[i].first += move[2 + dy][2 + dx].first;
                rope[i].second += move[2 + dy][2 + dx].second;
                visited[i].insert(rope[i]);
            }
        }
    }

    std::cout << visited[1].size() << " "
        << visited[ROPE - 1].size() << std::endl;
    return 0;
}
