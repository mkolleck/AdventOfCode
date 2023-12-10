// https://adventofcode.com/2023/day/9

#include <iostream>
#include <sstream>
#include <vector>

std::pair<int64_t, int64_t> predict(const std::vector<int64_t>& v)
{
    std::vector<int64_t> differences;
    bool allZeros = true;

    for (size_t i = 1; i < v.size(); i++)
    {
        differences.push_back(v[i] - v[i - 1]);

        if (differences.back() != 0)
        {
            allZeros = false;
        }
    }

    if (allZeros)
    {
        // Without adding zero, there is a strange compiler error.
        return std::make_pair(v.front(), v.back());
    }

    std::pair<int64_t, int64_t> p = predict(differences);
    return std::make_pair(v.front() - p.first, v.back() + p.second);
}

int main(void)
{
    int64_t result1 = 0, result2 = 0;
    std::string line;

    while (!std::getline(std::cin, line).eof())
    {
        std::istringstream in(line);
        std::vector<int64_t> readings;

        while (in.good())
        {
            int64_t reading;
            in >> reading;
            readings.push_back(reading);
        }

        std::pair<int64_t, int64_t> p = predict(readings);
        result1 += p.second;
        result2 += p.first;
    }

    std::cout << result1 << std::endl << result2 << std::endl;
    return 0;
}
