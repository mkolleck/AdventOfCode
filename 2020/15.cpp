// https://adventofcode.com/2020/day/15

#include <iostream>
#include <regex>
#include <sstream>
#include <vector>

typedef std::vector<int> Numbers;

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        return 1;
    }
    
    int limit = std::stol(argv[1]);
    std::string line;
    std::cin >> line;

    std::istringstream s(std::regex_replace(line, std::regex(","), " ") + " ");
    int i = 0, n = 0, last = 0;
    Numbers numbers;
    numbers.resize(limit);

    while (!(s >> n).eof())
    {
        if (i > 0)
        {
            numbers[last] = i;
        }

        last = n;
        i++;
    }

    while (i < limit)
    {
        int t = 0;

        if (numbers[last] != 0)
        {
            t = i - numbers[last];
        }

        numbers[last] = i;
        last = t;
        i++;
    }

    std::cout << i << " " << last << std::endl;
    return 0;
}
