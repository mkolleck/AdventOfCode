// https://adventofcode.com/2020/day/12

#include <iostream>

struct Ship
{
    int x = 0;
    int y = 0;
    int dx = 0;
    int dy = 0;

    void move(char a, int v)
    {
        switch (a)
        {
            case 'N':
                y += v;
                break;

            case 'S':
                y -= v;
                break;

            case 'E':
                x += v;
                break;

            case 'W':
                x -= v;
                break;

            case 'L':
                turn(v);
                break;

            case 'R':
                turn(360 - v);
                break;

            case 'F':
                x += dx * v;
                y += dy * v;
                break;
        };
    };

    void wmove(char a, int v)
    {
        switch (a)
        {
            case 'N':
                dy += v;
                break;

            case 'S':
                dy -= v;
                break;

            case 'E':
                dx += v;
                break;

            case 'W':
                dx -= v;
                break;

            case 'L':
                turn(v);
                break;

            case 'R':
                turn(360 - v);
                break;

            case 'F':
                x += dx * v;
                y += dy * v;
                break;
        };
    }

    void turn(int d)
    {
        for (; d > 0; d -= 90)
        {
            int t = dy;
            dy = dx;
            dx = -t;
        }
    };

    void print(void) const
    {
        std::cout << x << "|" << y << " -> " << abs(x) + abs(y) << std::endl;
    }
};

int main(void)
{
    std::string line;
    Ship ship1({ 0, 0, 1, 0 });
    Ship ship2({ 0, 0, 10, 1 });

    while (!(std::getline(std::cin, line)).eof())
    {
        char a = line[0];
        int v = std::stol(line.substr(1));

        ship1.move(a, v);
        ship2.wmove(a, v);
    }

    ship1.print();
    ship2.print();
    return 0;
}
