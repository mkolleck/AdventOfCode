// https://adventofcode.com/2023/day/2

#include <iostream>
#include <sstream>

int main(void)
{
    size_t result1 = 0, result2 = 0;
    std::string line;

    while (!std::getline(std::cin, line).eof())
    {
        std::istringstream in(line);
        std::string color;
        size_t number = 0;
        char sep;

        size_t game = 0;
        bool possible = true;

        size_t red = 0;
        size_t green = 0;
        size_t blue = 0;

        size_t maxRed = 0;
        size_t maxGreen = 0;
        size_t maxBlue = 0;

        in >> color /* "Game" */ >> game >> sep /* ':' */;

        while (!in.eof())
        {
            in >> number >> color;
            sep = color[color.length() - 1];

            if ((sep != ',') && (sep != ';'))
            {
                sep = ';';
            }
            else
            {
                color.erase(color.length() - 1);
            }

            if (color == "red")
            {
                red = number;
            }
            else if (color == "green")
            {
                green = number;
            }
            else if (color == "blue")
            {
                blue = number;
            }

            if (sep == ';')
            {
                if ((red > 12) || (green > 13) || (blue > 14))
                {
                    possible = false;
                }

                if (red > maxRed)
                {
                    maxRed = red;
                }

                if (green > maxGreen)
                {
                    maxGreen = green;
                }

                if (blue > maxBlue)
                {
                    maxBlue = blue;
                }
            }
        }

        if (possible)
        {
            result1 += game;
        }

        result2 += maxRed * maxGreen * maxBlue;
    }

    std::cout << result1 << "\n" << result2 << std::endl;
    return 0;
}
