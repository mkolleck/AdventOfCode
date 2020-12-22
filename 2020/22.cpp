// https://adventofcode.com/2020/day/22

#include <algorithm>
#include <iostream>
#include <list>

typedef std::list<int> Deck;

static bool play(Deck& d1, Deck& d2, bool recursive)
{
    bool result = false;
    std::list<Deck> h1, h2;

    while (!d1.empty() && !d2.empty())
    {
        if (recursive)
        {
            if ((std::find(h1.begin(), h1.end(), d1) != h1.end())
                    || (std::find(h2.begin(), h2.end(), d2) != h2.end()))
            {
                result = true;
                break;
            }

            h1.push_back(d1);
            h2.push_back(d2);
        }

        int c1 = d1.front(); d1.pop_front();
        int c2 = d2.front(); d2.pop_front();
        bool c1wins = c1 > c2;

        if (recursive && (d1.size() >= c1) && (d2.size() >= c2))
        {
            Deck sub1, sub2;
            std::copy_n(d1.begin(), c1, std::back_inserter(sub1));
            std::copy_n(d2.begin(), c2, std::back_inserter(sub2));
            c1wins = play(sub1, sub2, recursive);
        }

        if (c1wins)
        {
            d1.push_back(c1);
            d1.push_back(c2);
        }
        else
        {
            d2.push_back(c2);
            d2.push_back(c1);
        }

        result = d1.size() > d2.size();
    }

    return result;
}

static int score(const Deck& d)
{
    int m = d.size();
    int result = 0;

    for (const auto& c : d)
    {
        result += c * m;
        m--;
    }

    return result;
}

static void score(const Deck& d1, const Deck&d2)
{
    std::cout << "Player 1: " << score(d1) << ". Player 2: " << score(d2) << "." << std::endl;
}

int main(void)
{
    std::string line;
    Deck deck1, deck2, d1, d2;
    Deck* d = 0;

    while (!(std::getline(std::cin, line)).eof())
    {
        if (line.empty()) continue;

        if (line == "Player 1:")
        {
            d = &deck1;
        }
        else if (line == "Player 2:")
        {
            d = &deck2;
        }
        else if (d != 0)
        {
            d->push_back(std::stoi(line));
        }
    }

    play(d1 = deck1, d2 = deck2, false); score(d1, d2);
    play(d1 = deck1, d2 = deck2, true); score(d1, d2);
    return 0;
}
