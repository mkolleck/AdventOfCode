#include <iostream>
#include <string>

static std::string instruction;
static bool enabled = true;
static int a, b;

static void reset(void)
{
    a = b = 0;
    instruction.clear();
}

int main(void)
{
    int multiplications1 = 0;
    int multiplications2 = 0;

    while (!std::cin.eof())
    {
        char c;
        std::cin >> c;

        if ((c == 'm') || (c == 'd'))
        {
            reset();
            instruction += c;
        }
        else if (std::string("ulon't(,").find(c) != std::string::npos)
        {
            instruction += c;
        }
        else if ((instruction == "mul(") && (c >= '0') && (c <= '9'))
        {
            a = a * 10 + c - '0';
        }
        else if ((instruction == "mul(,") && (c >= '0') && (c <= '9'))
        {
            b = b * 10 + c - '0';
        }
        else if (c == ')')
        {
            if (instruction == "do(")
            {
                enabled = true;
            }
            else if (instruction == "don't(")
            {
                enabled = false;
            }
            else if (instruction == "mul(,")
            {
                multiplications1 += a * b;

                if (enabled)
                {
                    multiplications2 += a * b;
                }
            }

            reset();
        }
        else
        {
            reset();
        }
    }

    std::cout << multiplications1 << std::endl;
    std::cout << multiplications2 << std::endl;
}
