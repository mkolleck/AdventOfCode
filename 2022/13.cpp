// https://adventofcode.com/2022/day/13

#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

struct Packet
{
    Packet(void) : type(LIST), i(0), l()
    {
    }

    Packet(int i) : type(INT), i(i), l()
    {
    }

    Packet(const std::string& s) : Packet()
    {
        size_t p = 1, b;

        while (p < s.length() - 1)
        {
            if (s[p] == '[')
            {
                size_t nesting = 0;
                b = p + 1;

                for (; b < s.length(); b++)
                {
                    if (s[b] == ']')
                    {
                        if (nesting == 0)
                        {
                            break;
                        }
                        else
                        {
                            nesting--;
                        }
                    }
                    else if (s[b] == '[')
                    {
                        nesting++;
                    }
                }

                l.push_back(Packet(s.substr(p, b - p + 1)));
                p = b + 1;
            }
            else if (s[p] == ',')
            {
                p++;
            }
            else
            {
                b = s.find_first_of(",]", p);

                if (b != std::string::npos)
                {
                    l.push_back(std::stoi(s.substr(p, b - p)));
                }

                p = b + 1;
            }
        }
    }

    enum { INT, LIST } type;
    int i;
    std::list<Packet> l;
};

static std::strong_ordering operator<=>(const Packet& a, const Packet& b);

static std::strong_ordering operator<=>(const std::list<Packet>& a,
        const std::list<Packet>& b)
{
    std::list<Packet>::const_iterator ai = a.begin();
    std::list<Packet>::const_iterator bi = b.begin();

    while (true)
    {
        if ((ai == a.end()) && (bi == b.end()))
        {
            return std::strong_ordering::equal;
        }

        if (ai == a.end())
        {
            return std::strong_ordering::less;
        }

        if (bi == b.end())
        {
            return std::strong_ordering::greater;
        }

        if (*ai < *bi)
        {
            return std::strong_ordering::less;
        }

        if (*ai > *bi)
        {
            return std::strong_ordering::greater;
        }

        ai++;
        bi++;
    }
}

static std::strong_ordering operator<=>(const Packet& a, const Packet& b)
{
    if ((a.type == Packet::INT) && (b.type == Packet::INT))
    {
        return a.i <=> b.i;
    }

    if ((a.type == Packet::LIST) && (b.type == Packet::LIST))
    {
        return a.l <=> b.l;
    }

    if (a.type == Packet::INT)
    {
        return std::list<Packet>{ a } <=> b.l;
    }

    if (b.type == Packet::INT)
    {
        return a.l <=> std::list<Packet>{ b };
    }

    return std::strong_ordering::equivalent;
}

static bool operator==(const Packet& a, const char* b)
{
    return a <=> Packet(b) == std::strong_ordering::equal;
}

int main(void)
{
    std::string line;
    std::vector<Packet> packets;
    int sum = 0, prod = 1;

    while (!std::getline(std::cin, line).eof())
    {
        if (line.empty())
        {
            continue;
        }

        packets.push_back(Packet(line)); 

        if ((packets.size() % 2) == 0)
        {
            if (packets[packets.size() - 2] <= packets[packets.size() - 1])
            {
                sum += packets.size() / 2;
            }
        }
    }

    packets.push_back(Packet("[[2]]"));
    packets.push_back(Packet("[[6]]"));

    std::sort(packets.begin(), packets.end());

    for (size_t index = 0; index < packets.size(); index++)
    {
        if ((packets[index] == "[[2]]") || (packets[index] == "[[6]]"))
        {
            prod *= index + 1;
        }
    }

    std::cout << sum << "\n" << prod << std::endl;
    return 0;
}
