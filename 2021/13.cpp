// https://adventofcode.com/2021/day/13

#include <iostream>
#include <set>
#include <sstream>
#include <vector>

struct Point
{
    int x;
    int y;

    bool operator<(const Point& p) const
    {
        return (p.y < y) || ((p.y == y) && (p.x < x));
    }

    int& operator[](char dim)
    {
        if (dim == 'x') return x;
        return y;
    }
};

void fold(Point& dim, std::set<Point>& dots, char dir, int amount)
{
    if (dim[dir] != 2 * amount + 1)
    {
        dim[dir] = 2 * amount + 1;
    }

    Point start = { 0, 0 }, m = { 1, 1 }, n = { 0, 0 };
    start[dir] = amount;
    m[dir] = -1;
    n[dir] = dim[dir] - 1;

    for (int y = start.y; y < dim.y; y++)
    {
        for (int x = start.x; x < dim.x; x++)
        {
            std::set<Point>::iterator d = dots.find({x, y});

            if (d != dots.end())
            {
                int x = m.x * d->x + n.x;
                int y = m.y * d->y + n.y;
                dots.erase(d);
                dots.insert({ x , y });
            }
        }
    }

    dim[dir] = amount;
}

int main(void)
{
    std::string line;
    std::set<Point> dots;
    Point dim = { 0, 0 };
    bool once = true;

    while (!std::getline(std::cin, line).eof())
    {
        if (line.empty())
        {
            break;
        }

        line[line.find(',')] = ' ';

        int x, y;
        std::istringstream(line) >> x >> y;
        dots.insert({ x, y });

        if (x + 1 > dim.x)
        {
            dim.x = x + 1;
        }

        if (y + 1 > dim.y)
        {
            dim.y = y + 1;
        }
    }

    while (!std::getline(std::cin, line).eof())
    {
        line = line.substr(11);
        line[line.find('=')] = ' ';

        char dir;
        int amount;
        std::istringstream(line) >> dir >> amount;
        fold(dim, dots, dir, amount);

        if (once)
        {
            std::cout << "Dots after first fold: " << dots.size() << std::endl;
            once = false;
        }
    }

    for (int y = 0; y < dim.y; y++)
    {
        for (int x = 0; x < dim.x; x++)
        {
            if (dots.find({x, y}) == dots.end())
            {
                std::cout << " ";
            }
            else
            {
                std::cout << "#";
            }
        }

        std::cout << std::endl;
    }

    return 0;
}
