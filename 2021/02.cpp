// https://adventofcode.com/2021/day/2

#include <iostream>
#include <vector>

int main(void)
{
    int position = 0, depth1 = 0, depth2 = 0, aim = 0;
    std::string command;
    int value;

    while (!(std::cin >> command >> value).eof())
    {
        if (command == "forward")
        {
            position += value;
            depth2 += aim * value;
        }
        else if (command == "down")
        {
            depth1 += value;
            aim += value;
        }
        else if (command == "up")
        {
            depth1 -= value;
            aim -= value;
        }
    }

    std::cout << position << " * " << depth1 << " = " << position * depth1
        << std::endl;
    std::cout << position << " * " << depth2 << " = " << position * depth2
        << std::endl;
    return 0;
}
