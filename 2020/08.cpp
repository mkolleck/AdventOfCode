// https://adventofcode.com/2020/day/8

#include <iostream>
#include <vector>

struct Instruction
{
    enum { NOP, ACC, JMP } op;
    int arg;
    bool executed;
};

typedef std::vector<Instruction> Program;

static bool execute(const Program& p, int& acc)
{
    Program program(p);
    size_t pc = 0;
    acc = 0;

    while (pc < program.size())
    {
        if (program[pc].executed)
        {
            return false;
        }

        program[pc].executed = true;

        switch (program[pc].op)
        {
            case Instruction::NOP:
                pc++;
                break;

            case Instruction::ACC:
                acc += program[pc].arg;
                pc++;
                break;

            case Instruction::JMP:
                pc += program[pc].arg;
                break;
        }
    }

    return pc == program.size();
}

int main(void)
{
    Program program;
    std::string op;
    int arg;

    while (!(std::cin >> op >> arg).eof())
    {
        if (op == "nop")
        {
            program.push_back(Instruction({Instruction::NOP, arg, false}));
        }
        else if (op == "acc")
        {
            program.push_back(Instruction({Instruction::ACC, arg, false}));
        }
        else if (op == "jmp")
        {
            program.push_back(Instruction({Instruction::JMP, arg, false}));
        }
    }

    int acc = 0;

    execute(program, acc);
    std::cout << acc << std::endl;

    for (int pc = 0; pc < program.size(); pc++)
    {
        bool normalTermination = false;

        switch (program[pc].op)
        {
            case Instruction::NOP:
                program[pc].op = Instruction::JMP;
                normalTermination = execute(program, acc);
                program[pc].op = Instruction::NOP;
                break;

            case Instruction::ACC:
                continue;

            case Instruction::JMP:
                program[pc].op = Instruction::NOP;
                normalTermination = execute(program, acc);
                program[pc].op = Instruction::JMP;
                break;
        }

        if (normalTermination)
        {
            std::cout << acc << std::endl;
            break;
        }
    }

    return 0;
}
