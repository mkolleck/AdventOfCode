// https://adventofcode.com/2020/day/17

#include <iostream>
#include <vector>

typedef long long int T;
typedef void (Rules)(std::vector<T>& values, std::vector<char>& ops);

static void op(std::vector<T>& values, std::vector<char>& ops)
{
    T b = values.back(); values.pop_back();
    T a = values.back(); values.pop_back();

    switch (ops.back())
    {
        case '+':
            values.push_back(a + b);
            break;

        case '*':
            values.push_back(a * b);
            break;
    }

    ops.pop_back();
}

void rules1(std::vector<T>& values, std::vector<char>& ops)
{
    int closeBrace = 0;

    while (!ops.empty() && !values.empty())
    {
        switch (ops.back())
        {
            case '(':
                if (closeBrace == 0) return;
                ops.pop_back();
                closeBrace--;
                break;

            case '+':
            case '*':
                op(values, ops);
                break;

            case ')':
                ops.pop_back();
                closeBrace++;
                break;
        }
    }
}

void rules2(std::vector<T>& values, std::vector<char>& ops)
{
    int closeBrace = 0;

    while (!ops.empty() && !values.empty())
    {
        switch (ops.back())
        {
            case '(':
                if (closeBrace == 0) return;
                ops.pop_back();
                closeBrace--;
                break;

            case '+':
                op(values, ops);
                break;

            case '*':
                if (closeBrace == 0) return;
                op(values, ops);
                break;

            case ')':
                ops.pop_back();
                closeBrace++;
                break;
        }
    }
}

static T eval(const std::string& e, Rules rules)
{
    std::vector<T> values;
    std::vector<char> ops;

    for (int i = 0; i < e.size(); i++)
    {
        if (e[i] == ' ') continue;

        switch (e[i])
        {
            case '0' ... '9':
                values.push_back(e[i] - '0');
                rules(values, ops);
                break;

            case '+':
            case '*':
            case '(':
                ops.push_back(e[i]);
                break;

            case ')':
                ops.push_back(e[i]);
                rules(values, ops);
                break;
        }
    }

    return values.back();
}

int main(void)
{
    std::string line;
    T sum1 = 0, sum2 = 0;

    while (!(std::getline(std::cin, line)).eof())
    {
        sum1 += eval(line, rules1);
        sum2 += eval("(" + line + ")", rules2);
    }

    std::cout << sum1 << std::endl;
    std::cout << sum2 << std::endl;
    return 0;
}
