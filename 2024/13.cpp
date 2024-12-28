// https://adventofcode.com/2024/day/13

#include <iostream>
#include <regex>

struct Machine
{
    std::pair<size_t, size_t> a;
    std::pair<size_t, size_t> b;
    std::pair<size_t, size_t> prize;

    size_t play(const std::string& line);
    size_t play(void);
};

size_t Machine::play(const std::string& line)
{
    std::smatch ma, mb, mprize;

    if (std::regex_match(line, ma,
                std::regex("Button A: X\\+([0-9]+), Y\\+([0-9]+)")))
    {
        a.first = std::stoul(ma[1]);
        a.second = std::stoul(ma[2]);
        return 0;
    }

    if (std::regex_match(line, mb,
                std::regex("Button B: X\\+([0-9]+), Y\\+([0-9]+)")))
    {
        b.first = std::stoul(mb[1]);
        b.second = std::stoul(mb[2]);
        return 0;
    }

    if (std::regex_match(line, mprize,
                std::regex("Prize: X=([0-9]+), Y=([0-9]+)")))
    {
        prize.first = std::stoul(mprize[1]);
        prize.second = std::stoul(mprize[2]);
        return play();
    }

    return 0;
}

size_t Machine::play(void)
{
    size_t cost = (size_t)(-1);
    std::pair<size_t, size_t> best;

    for (size_t pa = 0; pa < 101; pa++)
    {
        for (size_t pb = 0 ; pb < 101; pb++)
        {
            if ((pa * a.first + pb * b.first == prize.first)
                    && (pa * a.second + pb * b.second == prize.second))
            {
                size_t tokens = 3 * pa + pb;

                if (tokens < cost)
                {
                    cost = tokens;
                    best = std::make_pair(pa, pb);
                }
            }
        }
    }

    return 3 * best.first + best.second;
}

int main(void)
{
    size_t result1 = 0, result2 = 0;
    std::string line;
    Machine m;

    while (!std::getline(std::cin, line).eof())
    {
        result1 += m.play(line);
    }

    std::cout << result1 << std::endl << result2 << std::endl;
    return 0;
}
