// https://adventofcode.com/2020/day/2

#include <iostream>
#include <regex>

int count(const std::string& password, const std::string& c)
{
    int result = 0;

    for (char p : password)
    {
        if (p == c[0])
        {
            result++;
        }
    }

    return result;
}

int isAt(const std::string& password, const std::string& c, int position)
{
    return password[position - 1] == c[0];
}

int main(void)
{
    std::string line;

    int valid1 = 0, valid2 = 0;
    int invalid1 = 0, invalid2 = 0;
    int fails = 0;

    while (!(std::getline(std::cin, line)).eof())
    {
        std::smatch match;

        if (std::regex_match(line, match,
                    std::regex("([0-9]+)-([0-9]+) ([a-z]): ([a-z]+)")))
        {
            int found = count(match[4], match[3]);

            if ((found < std::stol(match[1]))
                    || (found > std::stol(match[2])))
            {
                invalid1++;
            }
            else
            {
                valid1++;
            }

            if (isAt(match[4], match[3], std::stol(match[1]))
                    == isAt(match[4], match[3], std::stol(match[2])))
            {
                invalid2++;
            }
            else
            {
                valid2++;
            }
        }
        else
        {
            std::cerr << "No match: " << line << std::endl;
            fails++;
        }
    }

    std::cout
        << "Policy 1: valid = " << valid1 << ", invalid = " << invalid1
        << "\nPolicy 2: valid = " << valid2 << ", invalid = " << invalid2
        << "\nFails = " << fails << ". Total: " << valid1 + invalid1 + fails
        << std::endl;
    return 0;
}
