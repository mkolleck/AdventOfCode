// https://adventofcode.com/2020/day/19

#include <iostream>
#include <map>
#include <vector>

struct Rule;
typedef std::map<std::string, Rule*> Rules;

struct Rule
{
    virtual ~Rule() { }
    virtual int match(const Rules& rules, const std::string& m, int o) const = 0;
};

struct Character : public Rule
{
    char c;

    Character(char c) : c(c) { }
    virtual ~Character() { }

    virtual int match(const Rules& rules, const std::string& m, int o) const
    {
        return m[o] == c ? 1 : 0;
    }
};

struct Sequence : public Rule
{
    std::vector<std::string> s;

    Sequence(const std::string& rule) : s()
    {
        size_t o = 0;

        while (true)
        {
            size_t space = rule.find(" ", o);

            if (rule.substr(o, space - o).size() > 0)
            {
                s.push_back("r" + rule.substr(o, space - o));
            }

            if (space == std::string::npos) break;
            o = space + 1;
        }
    }

    virtual ~Sequence() { }

    virtual int match(const Rules& rules, const std::string& m, int o) const
    {
        int total = 0;

        for (const auto& r : s)
        {
            int match = rules.at(r)->match(rules, m, o + total);

            if (match == 0)
            {
                return 0;
            }

            total += match;
        }

        return total;
    }
};

struct Alternative : public Rule
{
    std::vector<std::string> a;

    Alternative(const std::string& rule, const std::string& num, Rules& rules) : a()
    {
        size_t o = 0;

        while (true)
        {
            size_t pipe = rule.find("|", o);
            a.push_back(num + "a" + std::to_string(o));
            rules[a.back()] = new Sequence(rule.substr(o, pipe - o));

            if (pipe == std::string::npos) break;
            o = pipe + 2;
        }
    }

    virtual ~Alternative() { }

    virtual int match(const Rules& rules, const std::string& m, int o) const
    {
        for (const auto& r : a)
        {
            int match = rules.at(r)->match(rules, m, o);

            if (match > 0)
            {
                return match;
            }
        }

        return 0;
    }
};

int main(void)
{
    Rules rules;
    std::vector<std::string> messages;
    std::string line;
    int matches1 = 0, matches2 = 0;

    while (!(std::getline(std::cin, line)).eof())
    {
        if (line.empty()) break;

        size_t colon = line.find(":");
        size_t pipe = line.find("|");
        size_t quote = line.find("\"");

        std::string rule = "r" + line.substr(0, colon);

        if (pipe != std::string::npos)
        {
            rules[rule] = new Alternative(line.substr(colon + 2), rule, rules);
        }
        else if (quote != std::string::npos)
        {
            rules[rule] = new Character(line[quote + 1]);
        }
        else
        {
            rules[rule] = new Sequence(line.substr(colon + 2));
        }
    }

    while (!(std::getline(std::cin, line)).eof())
    {
        if (rules.at("r0")->match(rules, line, 0) == line.length())
        {
            matches1++;
        }

        if (rules.find("r8") == rules.end()) continue;

        int r8matched = 0, r31matched = 0;
        int r8offset = 0, r31offset = 0;
        int r8match = 0, r31match = 0;

        while (true)
        {
            r8match = rules.at("r8")->match(rules, line, r8offset);

            if (r8match == 0) break;

            r8matched++;
            r8offset += r8match;

            r31matched = 0;
            r31offset = r8offset;

            for (int r31 = 0; r31 < r8matched; r31++)
            {
                r31match = rules.at("r31")->match(rules, line, r31offset);

                if (r31match == 0) break;

                r31matched++;
                r31offset += r31match;
            }

            if ((r31offset == line.length())
                    && (r8matched > 0) && (r31matched > 0)
                    && (r8matched > r31matched) )
            {
                matches2++;
                break;
            }
        }
    }

    std::cout << matches1 << std::endl;
    std::cout << matches2 << std::endl;
    return 0;
}
