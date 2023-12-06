// https://adventofcode.com/2023/day/4

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

static size_t getValue(const std::string& line)
{
    size_t result = 0;

    std::vector<size_t> numbers;
    std::string dummy;
    size_t number;

    std::istringstream in(line);
    in >> dummy /* Card */ >> dummy /* digit: */;

    while (in.good())
    {
        in >> number;

        if (in.good())
        {
            numbers.push_back(number);
        }
    }

    in.clear();
    in >> dummy /* | */;

    while (!in.eof())
    {
        in >> number;

        if (in.good() || in.eof())
        {
            if (std::find(numbers.begin(), numbers.end(), number)
                    != numbers.end())
            {
                result++;
            }
        }
    }

    return result;
}

static void add(std::vector<size_t>& vec, size_t i, size_t val)
{
    if (vec.size() <= i)
    {
        vec.resize(i + 1);
    }

    vec[i] += val;
}

int main(void)
{
    size_t result1 = 0, result2 = 0;

    std::string line;
    size_t index = 0;
    std::vector<size_t> nextCards;

    while (!std::getline(std::cin, line).eof())
    {
        size_t value = getValue(line);

        add(nextCards, index, 1); // this card

        size_t factor = nextCards[index];
        result2 += factor; // all 'this' cards

        if (value > 0)
        {
            result1 += 1 << (value - 1);

            for (size_t c = index + 1; c < index + value + 1; c++)
            {
                add(nextCards, c, factor);
            }
        }

        index++;
    }

    std::cout << result1 << "\n" << result2 << std::endl;
    return 0;
}
