// https://adventofcode.com/2023/day/1

#include <cmath>
#include <iostream>
#include <vector>

struct Race
{
    size_t time;
    size_t distance;

    size_t waysToWin(void) const
    {
        double pz = std::sqrt(time * time - 4 * distance);
        double z1 = std::ceil(0.5 * (time - pz));
        double z2 = std::floor(0.5 * (time + pz));

        if (z1 * (time - z1) == distance)
        {
            return (size_t)(z2 - z1 - 1);
        }

        return (size_t)(z2 - z1 + 1);
    }
};

static void shift(size_t& a, size_t b)
{
    a *= std::pow(10, (size_t)(std::log(b) / std::log(10) + 1));
    a += b;
}

int main(void)
{
    size_t result1 = 1;
    std::vector<Race> races;
    Race longRace({ 0, 0 });

    std::string dummy;
    std::cin >> dummy /* Time: */;

    while (std::cin.good())
    {
        Race race;
        std::cin >> race.time;

        if (std::cin.good())
        {
            races.push_back(race);
            shift(longRace.time, race.time);
        }
    }

    std::cin.clear();
    std::cin >> dummy /* Distance: */;

    for (auto& race : races)
    {
        std::cin >> race.distance;
        result1 *= race.waysToWin();
        shift(longRace.distance, race.distance);
    }

    std::cout << result1 << std::endl << longRace.waysToWin() << std::endl;
    return 0;
}
