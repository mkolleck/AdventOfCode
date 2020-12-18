// https://adventofcode.com/2020/day/17

#include <iostream>
#include <vector>

typedef std::vector<int> Point;

static Point& operator++(Point& p)
{
    for (auto& i : p) i++;
    return p;
}

static Point operator+(const Point& p, int i)
{
    Point r = p;
    return ++r;
}

static Point& operator--(Point& p)
{
    for (auto& i : p) i--;
    return p;
}

static Point operator-(const Point& p, int i)
{
    Point r = p;
    return --r;
}

static void nextPoint(Point& i, const Point& p1, const Point& p2)
{
    i[0]++;

    for (int d = 0; d < i.size() - 1; d++)
    {
        if (i[d] <= p2[d]) break;
        i[d] = p1[d];
        i[d + 1]++;
    }
}

static void prevPoint(Point& i, const Point& p1, const Point& p2)
{
    i[0]--;

    for (int d = 0; d < i.size() - 1; d++)
    {
        if (i[d] >= p1[d]) break;
        i[d] = p2[d];
        i[d + 1]--;
    }
}

static int offset(const Point& p, const Point& p1, const Point& p2)
{
    int o = 0;
    int f = 1;

    for (int d = 0; d < p.size(); d++)
    {
        o += (p[d] - p1[d]) * f;
        f *= p2[d] - p1[d] + 1;
    }

    return o;
}

struct Hyperqube
{
    std::vector<char> q; Point s1; Point s2;

    Hyperqube(int s) : q(), s1(), s2() { resize(Point(s), Point(s)); }

    void grow(void) { resize(s1 - 1, s2 + 1); }

    void resize(const Point& p) { resize(s1, p); }

    void resize(const Point& p1, const Point& p2)
    {
        int s = 1;

        for (int i = 0; i < p1.size(); i++)
        {
            s *= p2.at(i) - p1.at(i) + 1;
        }

        q.resize(s, '.');

        for (Point i = s2; (i.size() > 0) && (i.back() >= s1.back()); )
        {
            int o1 = offset(i, s1, s2), o2 = offset(i, p1, p2);

            if (o2 != o1)
            {
                q[o2] = q[o1];
                q[o1] = '.';
            }

            prevPoint(i, s1, s2);
        }

        s1 = p1; s2 = p2;
    }

    int contains(const Point& p) const
    {
        for (int d = 0; d < p.size(); d++)
        {
            if ((p[d] < s1[d]) || (p[d] > s2[d]))
            {
                return false;
            }
        }

        return true;
    }

    char at(const Point& p) const { return q.at(offset(p, s1, s2)); }

    char& at(const Point& p) { return q.at(offset(p, s1, s2)); }
};

static char active(Hyperqube& q, const Point& p)
{
    Point p1 = p - 1, p2 = p + 1;
    int active = 0;     

    for (Point i = p1; i.back() <= p2.back();)
    {
        if (q.contains(i) && (i != p))
        {
            if (q.at(i) == '#')
            {
                active++;
            }
        }

        nextPoint(i, p1, p2);
    }

    if (((q.at(p) == '#') && ((active == 2) || (active == 3)))
            || ((q.at(p) == '.') && (active == 3)))
    {
        return '#';
    }

    return '.';
}

static void iterate(Hyperqube& q)
{
    Hyperqube next = q;

    for (Point i = q.s1; i.back() <= q.s2.back();)
    {
        next.at(i) = active(q, i);
        nextPoint(i, q.s1, q.s2);
    }

    q = next;
}

int main(int argc, char** argv)
{
    if (argc < 3) return 1;

    Hyperqube h(std::stoi(argv[1]));
    int cycles = std::stoi(argv[2]);

    std::string line;
    Point i(std::stoi(argv[1]));

    while (!(std::getline(std::cin, line)).eof())
    {
        i[0] = line.length() - 1;
        h.resize(i);

        for (i[0] = 0; i[0] < line.length(); i[0]++)
        {
            h.at(i) = line[i[0]];
        }

        i[1]++;
    }

    for (int c = 0; c < cycles; c++)
    {
        h.grow();
        iterate(h);
    }

    int active = 0;

    for (const auto& c : h.q)
    {
        if (c == '#') active++;
    }

    std::cout << active << std::endl;
    return 0;
}
