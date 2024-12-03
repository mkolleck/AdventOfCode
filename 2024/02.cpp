#include <cstdlib>

#include <iostream>
#include <sstream>
#include <vector>

typedef std::vector<int> Report;

bool isSafe(const Report& r)
{
    int direction = 0;

    for (size_t i = 0; i < r.size() - 1; i++)
    {
        int delta = r[i] - r[i + 1];

        if ((delta == 0) || (abs(delta) > 3))
        {
            return false;
        }

        if (direction == 0)
        {
            direction = delta;
            continue;
        }

        if (((direction < 0) && (delta > 0))
                || ((direction > 0) && (delta < 0)))
        {
            return false;
        }
    }

    return true;
}

int main(void)
{
    int safeReports = 0;
    int safeWhenDampened = 0;

    std::string line;

    while (!std::getline(std::cin, line).eof())
    {
        Report r;

        std::istringstream s(line);
        int a;

        while (s.good())
        {
            s >> a;
            r.push_back(a);
        }

        if (isSafe(r))
        {
            safeReports++;
            safeWhenDampened++;
            continue;
        }

        for (size_t i = 0; i < r.size(); i++)
        {
            Report dampened = r;
            dampened.erase(dampened.begin() + i);

            if (isSafe(dampened))
            {
                safeWhenDampened++;
                break;
            }
        }
    }

    std::cout << safeReports << std::endl;
    std::cout << safeWhenDampened << std::endl;
    return 0;
}
