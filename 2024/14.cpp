// https://adventofcode.com/2024/day/14

#include <iostream>
#include <list>
#include <regex>

struct Robot
{
    std::pair<int, int> position;
    std::pair<int, int> velocity;
};

static std::list<Robot> robots;
static int maxX = 101;
static int maxY = 103;

void iterate(Robot& r)
{
    r.position.first += r.velocity.first;
    r.position.second += r.velocity.second;

    if (r.position.first < 0)
    {
        r.position.first += maxX;
    }

    if (r.position.first >= maxX)
    {
        r.position.first -= maxX;
    }

    if (r.position.second < 0)
    {
        r.position.second += maxY;
    }

    if (r.position.second >= maxY)
    {
        r.position.second -= maxY;
    }
}

int main(int argc, char** argv)
{
    if (argc == 3)
    {
        maxX = std::stol(argv[1]);
        maxY = std::stol(argv[2]);
    }

    size_t result1 = 0, result2 = 0;
    std::string line;

    while (!std::getline(std::cin, line).eof())
    {
        std::smatch match;

        if (std::regex_match(line, match,
                    std::regex("p=([0-9]+),([0-9]+) v=([0-9-]+),([0-9-]+)")))
        {
            robots.push_back({
                    std::make_pair(std::stol(match[1]), std::stol(match[2])),
                    std::make_pair(std::stol(match[3]), std::stol(match[4])) });
        }
    }

    for (int i = 0; i < 100; i++)
    {
        for (auto& r : robots)
        {
            iterate(r);
        }
    }

    size_t q1 = 0, q2 = 0, q3 = 0, q4 = 0;

    for (const auto& r : robots)
    {
        if ((r.position.first < maxX / 2)
                && (r.position.second < maxY / 2))
        {
            q1++;
        }
        else if ((r.position.first > maxX / 2)
                && (r.position.second < maxY / 2))
        {
            q2++;
        }
        else if ((r.position.first < maxX / 2)
                && (r.position.second > maxY / 2))
        {
            q3++;
        }
        else if ((r.position.first > maxX / 2)
                && (r.position.second > maxY / 2))
        {
            q4++;
        }
    }

    result1 = q1 * q2 * q3 * q4;
    std::cout << result1 << std::endl << result2 << std::endl;
    return 0;
}
