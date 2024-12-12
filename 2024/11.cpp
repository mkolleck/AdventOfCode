// https://adventofcode.com/2024/day/11

#include <cmath>
#include <iostream>
#include <map>

static std::map<std::pair<long long int, int>, long long int> cache;

static long long int blink(long long int stone, int iterations)
{
    if (iterations == 0)
    {
        return 1;
    }

    auto i = cache.find(std::make_pair(stone, iterations));

    if (i != cache.end())
    {
        return i->second;
    }

    long long int digits = (long long int)(log(stone) / log(10)) + 1;
    long long int result = 0;

    if (stone == 0)
    {
        result = blink(1, iterations - 1);
    }
    else if (digits % 2 == 0)
    {
        long long int halfDigits = pow(10, digits / 2);
        result = blink(stone / halfDigits, iterations - 1)
            + blink(stone % halfDigits, iterations - 1);
    }
    else
    {
        result = blink(stone * 2024, iterations - 1);
    }

    cache[std::make_pair(stone, iterations)] = result;
    return result;
}

int main(void)
{
    size_t result1 = 0, result2 = 0;

    while (std::cin.good())
    {
        long long int stone;
        std::cin >> stone;

        if (std::cin.good())
        {
            result1 += blink(stone, 25);
            result2 += blink(stone, 75);
        }
    }

    std::cout << result1 << std::endl << result2 << std::endl;
    return 0;
}
