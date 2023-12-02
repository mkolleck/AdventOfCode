// https://adventofcode.com/2023/day/1

#include <iostream>

void update(char c, size_t& n, size_t& l)
{
    if (n == 0)
    {
        n = c - '0';
        n *= 10;
    }

    l = c - '0';
}

int main(void)
{
    size_t sum1 = 0, sum2 = 0;
    std::string line;

    while (!std::getline(std::cin, line).eof())
    {
        size_t n1 = 0, l1 = 0;
        size_t n2 = 0, l2 = 0;

        for (size_t i = 0; i < line.length(); i++)
        {
            if (isdigit(line[i]))
            {
                update(line[i], n1, l1);
                update(line[i], n2, l2);
            }
            else if (line.find("one", i) == i)
            {
                update('1', n2, l2);
            }
            else if (line.find("two", i) == i)
            {
                update('2', n2, l2);
            }
            else if (line.find("three", i) == i)
            {
                update('3', n2, l2);
            }
            else if (line.find("four", i) == i)
            {
                update('4', n2, l2);
            }
            else if (line.find("five", i) == i)
            {
                update('5', n2, l2);
            }
            else if (line.find("six", i) == i)
            {
                update('6', n2, l2);
            }
            else if (line.find("seven", i) == i)
            {
                update('7', n2, l2);
            }
            else if (line.find("eight", i) == i)
            {
                update('8', n2, l2);
            }
            else if (line.find("nine", i) == i)
            {
                update('9', n2, l2);
            }
        }

        sum1 += n1 + l1;
        sum2 += n2 + l2;
    }

    std::cout << sum1 << std::endl << sum2 << std::endl;
    return 0;
}
