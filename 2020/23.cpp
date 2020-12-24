// https://adventofcode.com/2020/day/23

#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

typedef std::vector<int> Cups;

static inline int at(const Cups& cups, int i)
{
    return cups[i % cups.size()];
}

static inline int at(Cups& cups, int i, int n)
{
    int o = i % cups.size();
    int r = cups[o];
    cups[o] = n;
    return r;
}

static int offset(Cups& cups, int i)
{
    for (int p = 0; p < cups.size(); ++p)
    {
        if (cups[p] == i) return p;
    }

    std::cout << "OFFSET for " << i << " not found" << std::endl;
    exit(1);
}

static int destination(Cups& cups, int i, int p1, int p2, int p3)
{
    i--;

    while (true)
    {
        if (i == 0) i = *(std::max_element(cups.begin(), cups.end()));

        if ((i == p1) || (i == p2) || (i == p3))
        {
            i--;
            continue;
        }

        break;
    }

    return offset(cups, i);
}

inline void move(Cups& cups, int from, int to, int count)
{
    std::memmove(cups.data() + to, cups.data() + from, count * sizeof(Cups::value_type));
}

void play(Cups& cups, int iterations)
{
    for (int m = 0, o1 = 0; m < iterations; m++)
    {
        o1 = o1 % cups.size();

        int p1 = at(cups, o1 + 1, 0);
        int p2 = at(cups, o1 + 2, 0);
        int p3 = at(cups, o1 + 3, 0);
        int o2 = destination(cups, cups[o1], p1, p2, p3);

        if (o2 > o1)
        {
            move(cups, o1 + 4, o1 + 1, o2 - o1 - 1);
            cups[o2 - 2] = p1;
            cups[o2 - 1] = p2;
            cups[o2] = p3;
            o1++;
        }
        else
        {
            cups.resize(cups.size() + 4);

            move(cups, o2 + 1, o2 + 4, o1 - o2);
            cups.data()[o2 + 1] = p1;
            cups.data()[o2 + 2] = p2;
            cups.data()[o2 + 3] = p3;
            for (int i = 0; cups[i] == 0; i++) cups[i] = cups[i + cups.size() - 4];
            o1 = o2 + 4 + o1 - o2;

            cups.resize(cups.size() - 4);
        }
    }
}

void play1(const Cups& c)
{
    Cups cups = c;
    play(cups, 100);

    int o = offset(cups, 1);
    for (int i = o + 1; i < cups.size() + o; i++) std::cout << at(cups, i);
    std::cout << std::endl;
}

void play2(const Cups& c)
{
    Cups cups = c;
    for (int i = c.size() + 1; i <= 1000000; i++) cups.push_back(i);
    play(cups, 10000000);

    int o = offset(cups, 1);
    std::cout << at(cups, o + 1) << " * " << at(cups, o + 2) << " = "
        << (long long int)(at(cups, o + 1)) * at(cups, o + 2) << std::endl;
}

int main(int argc, char** argv)
{
    if (argc != 2) return 1;

    Cups cups;
    for (int i = 0; argv[1][i] != 0; i++) cups.push_back(argv[1][i] - '0');

    play1(cups);
    play2(cups);
    return 0;
}
