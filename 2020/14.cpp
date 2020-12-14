// https://adventofcode.com/2020/day/14

#include <iostream>
#include <map>
#include <set>

struct Machine
{
    uint64_t aMask;
    uint64_t oMask;
    uint64_t xMask;
    std::set<uint64_t> xMasks;
    std::map<uint64_t, uint64_t> m1;
    std::map<uint64_t, uint64_t> m2;

    void setMask(const std::string& m)
    {
        aMask = oMask = xMask = 0;
        xMasks.clear();
        xMasks.insert(0);

        int i = 0;

        for (const auto& c : m)
        {
            switch (c)
            {
                case '1':
                    aMask += 1;
                    oMask += 1;
                    break;

                case '0':
                    break;

                case 'X':
                    if (xMasks.size() < (1<<10))
                    {
                        for (auto& m : xMasks)
                        {
                            xMasks.insert(m | (1ULL << (35 - i)));
                        }
                    }

                    aMask += 1;
                    xMask += 1;
                    break;
            }

            aMask <<= 1;
            oMask <<= 1;
            xMask <<= 1;
            i++;
        }

        aMask >>= 1;
        oMask >>= 1;
        xMask >>= 1;
    }

    void set(uint64_t a, uint64_t v)
    {
        m1[a] = (v & aMask) | oMask;

        for (const auto& mask : xMasks)
        {
            m2[((a | oMask) & ~xMask) | mask] = v;
        }
    }
};

int main(void)
{
    std::string line;
    Machine m;
    uint64_t s1 = 0, s2 = 0;

    while (!(std::getline(std::cin, line)).eof())
    {
        std::string command = line.substr(0, line.find(" = "));

        if (command == "mask")
        {
            m.setMask(line.substr(command.size() + 3));
        }
        else if (command.find("mem") == 0)
        {
            m.set(std::stol(line.substr(4, line.find("]") - 4)),
                    std::stol(line.substr(command.size() + 3)));
        }
    }

    for (const auto& m : m.m1)
    {
        s1 += m.second;
    }

    for (const auto& m : m.m2)
    {
        s2 += m.second;
    }

    std::cout << s1 << std::endl;
    std::cout << s2 << std::endl;
    return 0;
}
