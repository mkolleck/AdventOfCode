// https://adventofcode.com/2020/day/13

#include <iostream>
#include <regex>
#include <sstream>

typedef intmax_t T;
typedef std::vector<T> B;

static void nearest(const B& busses, T now)
{
    T bus = 0, depart = -1;

    for (const T& b : busses)
    {
        if (b == 0) continue;

        T leaves = (now / b) * b + b;

        if ((depart == -1) || (leaves < depart))
        {
            depart = leaves;
            bus = b;
        }
    }

    std::cout << bus << " at " << depart << " -> "
        << bus * (depart - now) << std::endl;
}

static void contest(const B& busses)
{
    T start = 0;
    T delta = busses[0];

    for (int i = 1; i < busses.size(); i++)
    {
        if (busses[i] == 0) continue;

        while ((start + i) % busses[i] != 0)
        {
            start += delta;
        }

        delta *= busses[i];
    }

    std::cout << start << std::endl;
}

int main(void)
{
    intmax_t now = 0;
    std::string line;
    std::cin >> now >> line;

    std::istringstream s(std::regex_replace(line, std::regex(","), " ") + " ");
    B busses;

    while (!(s >> line).eof())
    {
        if (line != "x")
        {
            busses.push_back(std::stol(line));
        }
        else
        {
            busses.push_back(0);
        }
    }

    nearest(busses, now);
    contest(busses);
    return 0;
}
