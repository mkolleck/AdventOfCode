// https://adventofcode.com/2021/day/8

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

struct Symbol
{
    std::set<char> s;

    Symbol(const std::string& s = "") : s()
    {
        for (const auto& c : s)
        {
            this->s.insert(c);
        }
    }

    std::set<char>& operator()(void) { return s; }

    bool operator==(const Symbol& s) const { return this->s == s.s; }
    bool operator!=(const Symbol& s) const { return !(*this == s); }

    std::set<char>::const_iterator begin(void) const { return s.begin(); }
    std::set<char>::const_iterator end(void) const { return s.end(); }

    void clear() { s.clear(); }

    size_t size(void) const { return s.size(); }

    int simple(void) const
    {
        switch (s.size())
        {
            case 2: // 1: cf
            case 3: // 7: acf
            case 4: // 4: bcdf
            case 7: // 8: abcdefg
                return 1;

            case 5: // 2: acdeg, 3: acdfg, 5: abdfg
            case 6: // 0: abcefg, 6: abdefg, 9: abcdfg
                return 0;

            default:
                break;
        }

        return 0;
    }
};

typedef std::vector<Symbol> Symbols;

struct Digits
{
    Symbols s;

    Digits(const Symbols& syms) : s()
    {
        if (syms.size() != 10) throw 0;
        s.resize(10);

        Symbol A, B, D, G, S;

        // Assign known digits.
        for (int i = 0; i < 10; i++)
        {
            switch (syms[i].size())
            {
                case 2: // 1: cf
                    s[1] = syms[i];
                    break;

                case 3: // 7: acf
                    s[7] = syms[i];
                    break;

                case 4: // 4: bcdf
                    s[4] = syms[i];
                    break;

                case 7: // 8: abcdefg
                    s[8] = syms[i];
                    break;

                default:
                    break;
            }
        }

        // A: The letter in '7', but not in '1'.
        std::set_difference(s[7].begin(), s[7].end(), s[1].begin(), s[1].end(),
                std::inserter(A(), A.begin()));

        // G: The letter in '9', but not in '4' + '7'.
        // 9: The symbol with six letters containing 'G'.
        S.clear();
        std::set_union(s[4].begin(), s[4].end(), s[7].begin(), s[7].end(),
                std::inserter(S(), S.begin()));

        for (int i = 0; i < 10; i++)
        {
            if (syms[i].size() == 6)
            {
                std::set_difference(syms[i].begin(), syms[i].end(),
                        S.begin(), S.end(), std::inserter(G(), G.begin()));

                if (G.size() == 1)
                {
                    s[9] = syms[i];
                    break;
                }
            }

            G.clear();
        }

        // D: the letter in '3', but not in '1' + 'A' + 'G'
        S = s[1];
        S().insert(*A.begin());
        S().insert(*G.begin());

        for (int i = 0; i < 10; i++)
        {
            if (syms[i].size() == 5)
            {
                std::set_difference(syms[i].begin(), syms[i].end(),
                        S.begin(), S.end(), std::inserter(D(), D.begin()));

                if (D.size() == 1)
                {
                    s[3] = syms[i];
                    break;
                }
            }

            D.clear();
        }

        // 'B': '9' - '7' - 'D' - 'G'
        S.clear();
        std::set_difference(s[9].begin(), s[9].end(), s[7].begin(), s[7].end(),
                std::inserter(S(), S.begin()));
        B = S;

        S.clear();
        std::set_difference(B.begin(), B.end(), D.begin(), D.end(),
                std::inserter(S(), S.begin()));
        B = S;

        S.clear();
        std::set_difference(B.begin(), B.end(), G.begin(), G.end(),
                std::inserter(S(), S.begin()));
        B = S;

        // 0: '8' without 'D'
        S.clear();
        std::set_difference(s[8].begin(), s[8].end(), D.begin(), D.end(),
                std::inserter(S(), S.begin()));
        s[0] = S;

        // 6: 6 letters which are not '0' or '9'
        for (int i = 0; i < 10; i++)
        {
            if ((syms[i].size() == 6)
                    && (syms[i] != s[0])
                    && (syms[i] != s[9]))
            {
                s[6] = syms[i];
                break;
            }
        }

        // 5: 5 letter which contains 'B'
        // 2: 5 letters which is neither '3' nor '5'.
        for (int i = 0; i < 10; i++)
        {
            if ((syms[i].size() != 5) || (syms[i] == s[3]))
            {
                continue;
            }

            S.clear();
            std::set_difference(syms[i].begin(), syms[i].end(),
                    B.begin(), B.end(), std::inserter(S(), S.begin()));

            if (S.size() == 4)
            {
                s[5] = syms[i];
            }
            else
            {
                s[2] = syms[i];
            }
        }
    }

    int operator()(const Symbols& syms)
    {
        int result = 0;

        for (const auto& sym : syms)
        {
            for (int i = 0; i < 10; i++)
            {
                if (sym == s[i])
                {
                    result += i;
                    break;
                }
            }

            result *= 10;
        }

        return result / 10;
    }
};

int countSimple(const Symbols& syms)
{
    int result = 0;

    for (const auto& s : syms)
    {
        result += s.simple();
    }

    return result;
}

int main(void)
{
    std::string entry;
    Symbols digits, output;
    int i = 0, digits1478 = 0, sum = 0;

    while (!(std::cin >> entry).eof())
    {
        if (i < 10)
        {
            digits.push_back(entry);
        }
        else if (i == 10)
        {
            // separator '|'
        }
        else if (i > 10)
        {
            output.push_back(entry);
        }

        if (i == 14)
        {
            digits1478 += countSimple(output);
            sum += Digits(digits)(output);
            digits.clear();
            output.clear();
            i = 0;
        }
        else
        {
            i++;
        }
    }

    std::cout << digits1478 << "\n" << sum << std::endl;
    return 0;
}
