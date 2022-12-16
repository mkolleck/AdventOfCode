// https://adventofcode.com/2022/day/10

#include <iostream>
#include <sstream>

int main(void)
{
    std::string line, instr, output;
    int v, x = 1, cycles = 0, signal = 0;

    while (!std::getline(std::cin, line).eof())
    {
        std::istringstream(line) >> instr >> v;
        int c = 1;

        if (instr == "addx")
        {
            c = 2;
        }

        for (int i = 0; i < c; i++)
        {
            int pos = cycles % 40;
            cycles++;

            if ((cycles >= 20) && ((cycles - 20) % 40 == 0))
            {
                signal += cycles * x;
            }

            if ((x - 1 <= pos) && (pos <= x + 1))
            {
                output += '#';
            }
            else
            {
                output += ' ';
            }

            if (pos == 39)
            {
                output += '\n';
            }
        }

        if (instr == "addx")
        {
            x += v;
        }
    }

    output.pop_back();
    std::cout << signal << "\n" << output << std::endl;
    return 0;
}
