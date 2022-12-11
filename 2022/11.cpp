// https://adventofcode.com/2022/day/11

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

struct Operation
{
    virtual unsigned long operator()(unsigned long old) = 0;
};

struct Add : public Operation
{
    virtual unsigned long operator()(unsigned long old)
    {
        return old + value;
    }

    unsigned long value;
};

struct Multiply : public Operation
{
    virtual unsigned long operator()(unsigned long old)
    {
        return old * value;
    }

    unsigned long value;
};

struct Square : public Operation
{
    virtual unsigned long operator()(unsigned long old)
    {
        return old * old;
    }
};

typedef unsigned long Relief(unsigned long);

struct Monkey
{
    std::vector<unsigned long> items;
    Operation* op;
    unsigned long check = 0;
    int trueTarget = 0;
    int falseTarget = 0;

    unsigned long activity = 0;

    void operator()(std::vector<Monkey>& monkeys, Relief relief)
    {
        for (auto i : items)
        {
            unsigned long v = relief((*op)(i));

            if ((v % check) == 0)
            {
                monkeys[trueTarget].items.push_back(v);
            }
            else
            {
                monkeys[falseTarget].items.push_back(v);
            }

            activity++;
        }

        items.clear();
    }
};

void iterate(std::vector<Monkey> monkeys, int iterations, Relief relief)
{
    for (int i = 0; i < iterations; i++)
    {
        for (auto& m : monkeys)
        {
            m(monkeys, relief);
        }
    }

    std::sort(monkeys.begin(), monkeys.end(),
            [](Monkey& m1, Monkey& m2) { return m1.activity > m2.activity; });
    std::cout << monkeys[0].activity * monkeys[1].activity << std::endl;
}

static unsigned long modulus = 1;

int main(int argc, char** argv)
{
    std::vector<Monkey> monkeys;
    std::string line;

    while (!std::getline(std::cin, line).eof())
    {
        if (line.find("Monkey") == 0)
        {
            monkeys.push_back(Monkey());
            continue;
        }

        if (line.find("Starting items:") != std::string::npos)
        {
            unsigned long i;
            line = line.substr(17);
            std::replace(line.begin(), line.end(), ',', ' ');
            std::istringstream v(line + " ");

            while (!(v >> i).eof())
            {
                monkeys.back().items.push_back(i);
            }

            continue;
        }

        if (line.find("Operation:") != std::string::npos)
        {
            char op;
            std::string value;
            std::istringstream(line.substr(23)) >> op >> value;

            switch (op)
            {
                case '+':
                {
                    Add* op = new Add;
                    op->value = std::stol(value);
                    monkeys.back().op = op;
                    break;
                }

                case '*':
                {
                    if (value == "old")
                    {
                        monkeys.back().op = new Square;
                    }
                    else
                    {
                        Multiply* op = new Multiply;
                        op->value = std::stol(value);
                        monkeys.back().op = op;
                    }

                    break;
                }
            }

            continue;
        }

        if (line.find("Test:") != std::string::npos)
        {
            std::istringstream(line.substr(21)) >> monkeys.back().check;
            ::modulus *= monkeys.back().check;
        }

        if (line.find("If true:") != std::string::npos)
        {
            std::istringstream(line.substr(29)) >> monkeys.back().trueTarget;
        }

        if (line.find("If false:") != std::string::npos)
        {
            std::istringstream(line.substr(30)) >> monkeys.back().falseTarget;
        }
    }

    iterate(monkeys, 20, [](unsigned long i) { return i / 3; });
    iterate(monkeys, 10000, [](unsigned long i) { return i % ::modulus; });
    return 0;
}
