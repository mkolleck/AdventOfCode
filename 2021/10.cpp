// https://adventofcode.com/2021/day/10

#include <algorithm>
#include <iostream>
#include <vector>

static int process(const std::string& line, long int& complete)
{
    std::vector<char> stack;
    complete = 0;

    for (auto& c : line)
    {
        switch (c)
        {
            case '(':
            case '[':
            case '{':
            case '<':
                stack.push_back(c);
                break;

            case ')':
                if ((stack.size() == 0) || (stack.back() != '('))
                {
                    return 3;
                }

                stack.pop_back();
                break;

            case ']':
                if ((stack.size() == 0) || (stack.back() != '['))
                {
                    return 57;
                }

                stack.pop_back();
                break;

            case '}':
                if ((stack.size() == 0) || (stack.back() != '{'))
                {
                    return 1197;
                }

                stack.pop_back();
                break;

            case '>':
                if ((stack.size() == 0) || (stack.back() != '<'))
                {
                    return 25137;
                }

                stack.pop_back();
                break;

            default:
                break;
        }
    }

    while (stack.size() > 0)
    {
        complete *= 5;

        switch (stack.back())
        {
            case '(':
                complete += 1;
                break;

            case '[':
                complete += 2;
                break;

            case '{':
                complete += 3;
                break;

            case '<':
                complete += 4;
                break;
        }

        stack.pop_back();
    }

    return 0;
}

int main(void)
{
    int score = 0;
    long int complete = 0;
    std::vector<long int> autocomplete;
    std::string line;

    while (!(std::getline(std::cin, line)).eof())
    {
        score += process(line, complete);

        if (complete != 0)
        {
            autocomplete.push_back(complete);
        }
    }

    std::sort(autocomplete.begin(), autocomplete.end());
    std::cout << score << "\n"
        << autocomplete[autocomplete.size() / 2] << std::endl;
    return 0;
}
