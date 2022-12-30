// https://adventofcode.com/2022/day/15

#include <climits>
#include <iostream>
#include <list>
#include <map>
#include <thread>

struct M
{
    char c = 0;
    int d = 0;
};

std::map<std::pair<int, int>, M> map;
int row = 2000000, maxXY = 4000000;
bool beaconFound = false;

static inline int Δ(const std::pair<int, int>& a, const std::pair<int, int>& b)
{
    return abs(b.first - a.first) + abs(b.second - a.second);
}

void checkBeacons(int a, int b)
{
    for (int y = a; y <= b ; y++)
    {
        for (int x = 0; x <= maxXY; x++)
        {
            bool beaconPossible = true;

            for (const auto& m : map)
            {
                if ((m.second.c == 'S') && (Δ({x, y}, m.first) <= m.second.d))
                {
                    beaconPossible = false;
                    break;
                }
            }

            if (beaconPossible)
            {
                std::cout << x * 4000000 + y << std::endl;
                beaconFound = true;
            }

            if (beaconFound)
            {
                return;
            }
        }
    }
}

int main(void)
{
    std::string fluff;
    char fluffy;

    std::pair<int, int> s, b, min = { INT_MAX, INT_MAX }, max = { INT_MIN, INT_MIN };
    int noBeacon = 0;

    while (!std::cin.eof())
    {
        std::cin >> fluff >> fluff >> fluffy >> fluffy >> s.first
            >> fluff >> fluffy >> fluffy >> s.second
            >> fluffy >> fluff >> fluff >> fluff >> fluff >> fluffy >> fluffy >> b.first
            >> fluff >> fluffy >> fluffy >> b.second;

        int d = Δ(s, b);
        map[s] = { 'S', d };
        map[b] = { 'B', 0 };

        if (s.first - d < min.first) min.first = s.first - d;
        if (b.first - d < min.first) min.first = b.first - d;
        if (s.first + d > max.first) max.first = s.first + d;
        if (b.first + d > max.first) max.first = b.first + d;
        if (s.second - d < min.second) min.second = s.second - d;
        if (b.second - d < min.second) min.second = b.second - d;
        if (s.second + d > max.second) max.second = s.second + d;
        if (b.second + d > max.second) max.second = b.second + d;
    }

    if (max.second < 100)
    {
        row = 10;
        maxXY = 20;
    }

    for (int x = min.first; x <= max.first; x++)
    {
        for (const auto& m : map)
        {
            if (Δ({x, row}, m.first) <= m.second.d)
            {
                if (map.find({x, row}) == map.end())
                {
                    noBeacon++;
                }

                break;
            }
        }
    }

    std::cout << noBeacon << std::endl;

    std::list<std::thread> threads;
    int nproc = std::thread::hardware_concurrency();
    int  a = 0, slice = maxXY / nproc;

    if (slice == 0)
    {
        slice = 1;
        nproc = maxXY;
    }

    for (int i = 0; i < nproc; i++)
    {
        threads.push_back(std::thread(checkBeacons, a, a + slice - 1));
        a += slice;
    }

    for (auto& t : threads)
    {
        t.join();
    }

    return 0;
}
