// https://adventofcode.com/2023/day/3

#include <iostream>
#include <set>
#include <vector>

struct Part
{
    const size_t row;
    const size_t col;
    const char type;
    mutable std::vector<size_t> numbers;

    Part(size_t r, size_t c, char type = 0) :
        row(r),
        col(c),
        type(type),
        numbers()
    {
    }

    bool operator<(const Part& p) const
    {
        if (p.row < row)
        {
            return true;
        }

        return (p.row == row) && (p.col < col);
    }
};

struct Schematic
{
    typedef std::set<Part> Parts;

    std::vector<char> data;
    size_t rows;
    size_t cols;
    Parts parts;

    Schematic(void) :
        data(),
        rows(0),
        cols(0)
    {
        std::string line;

        while (!std::getline(std::cin, line).eof())
        {
            for (size_t c = 0; c < line.length(); c++)
            {
                data.push_back(line[c]);

                if ((line[c] != '.') && !isdigit(line[c]))
                {
                    parts.emplace(rows, c, line[c]);
                }
            }

            rows++;
            cols = line.length();
        }
    }

    char at(size_t r, size_t c)
    {
        return data[r * rows + c];
    }

    Schematic::Parts::iterator partForNumber(size_t r, size_t c)
    {
        for (int Δr = -1; Δr <= 1; Δr++)
        {
            for (int Δc = -1; Δc <= 1; Δc++)
            {
                Schematic::Parts::iterator result
                    = parts.find(Part(r + Δr, c + Δc));

                if (result != parts.end())
                {
                    return result;
                }
            }
        }

        return parts.end();
    }
};

int main(void)
{
    size_t result1 = 0, result2 = 0;
    Schematic schematic;

    size_t number = 0;
    Schematic::Parts::iterator part = schematic.parts.end();

    for (size_t r = 0; r < schematic.rows; r++)
    {
        for (size_t c = 0; c < schematic.cols; c++)
        {
            if (isdigit(schematic.at(r, c)))
            {
                number *= 10;
                number += schematic.at(r, c) - '0';

                if (part == schematic.parts.end())
                {
                    part = schematic.partForNumber(r, c);
                }
            }
            else
            {
                if (number != 0)
                {
                    if (part != schematic.parts.end())
                    {
                        part->numbers.push_back(number);
                        result1 += number;
                    }

                    number = 0;
                }

                part = schematic.parts.end();
            }
        }
    }

    for (auto& p : schematic.parts)
    {
        if ((p.type == '*') && (p.numbers.size() == 2))
        {
            result2 += p.numbers[0] * p.numbers[1];
        }
    }

    std::cout << result1 << "\n" << result2 << std::endl;
    return 0;
}
