// https://adventofcode.com/2020/day/15

#include <iostream>
#include <limits>
#include <regex>
#include <sstream>

struct Rule
{
    int position;
    std::string field;
    std::pair<int, int> range1;
    std::pair<int, int> range2;
    std::vector<int> matched;

    bool operator<(const Rule& o) const
    {
        return position < o.position;
    }

    bool operator()(int value) const
    {
        return ((range1.first <= value) && (value <= range1.second))
            || ((range2.first <= value) && (value <= range2.second));
    };
};

typedef std::vector<Rule> Rules;
typedef std::vector<int> Ticket;

static bool valid(const Rules& rules, int value)
{
    for (const auto& r : rules)
    {
        if (r(value)) return true;
    }

    return false;
}

int main(void)
{
    Rules rules;
    Ticket ticket;
    int tickets = 0, errors = 0;
    std::string line;
    int v;

    while (!(std::getline(std::cin, line)).eof())
    {
        if (line.empty()) break;

        std::smatch match;
        std::regex_match(line, match,
                std::regex("([a-z ]+): ([0-9]+)-([0-9]+) or ([0-9]+)-([0-9]+)"));
        rules.push_back(Rule({ std::numeric_limits<int>::max(), match[1],
                    std::make_pair(std::stoi(match[2]), std::stoi(match[3])),
                    std::make_pair(std::stoi(match[4]), std::stoi(match[5])) }));
    }

    for (auto& r : rules) r.matched.resize(rules.size());

    std::getline(std::cin, line);
    std::getline(std::cin, line);
    std::istringstream s(std::regex_replace(line, std::regex(","), " ") + " ");

    while (!(s >> v).eof())
    {
        ticket.push_back(v);
    }

    while (!(std::getline(std::cin, line)).eof())
    {
        if (line.empty() || (line.back() == ':')) continue;

        std::istringstream s(std::regex_replace(line, std::regex(","), " ") + " ");
        int e = 0;
        Ticket t;

        while (!(s >> v).eof())
        {
            t.push_back(v);

            if (!valid(rules, v))
            {
                e += v;
            }
        }

        if (e == 0)
        {
            tickets++;

            for (int i = 0; i < t.size(); i++)
            {
                for (auto& r : rules)
                {
                    if (r(t[i])) r.matched[i]++;
                }
            }
        }
        else
        {
            errors += e;
        }
    }

    std::cout << errors << std::endl;

    for (auto& r : rules)
    {
        for (const auto& m : r.matched)
        {
            if (m == tickets) r.position++;
        }
    }

    std::sort(rules.begin(), rules.end());
    std::vector<int> taken;

    for (auto& r : rules)
    {
        for (int i = 0; i < r.matched.size(); i++)
        {
            if ((r.matched[i] == tickets)
                    && (std::find(taken.begin(), taken.end(), i) == taken.end()))
            {
                r.position = i;
                taken.push_back(i);
                break;
            }
        }
    }

    std::sort(rules.begin(), rules.end());
    long long int departure = 1;

    for (const auto& r : rules)
    {
        if (r.field.find("departure") == 0)
        {
            departure *= (long long int)(ticket[r.position]);
        }
    }

    std::cout << departure << std::endl;
    return 0;
}
