// https://adventofcode.com/2023/day/7

#include <algorithm>
#include <iostream>
#include <list>
#include <map>

typedef std::map<char, int> CardRank;

const CardRank cardRank1 =
{
    { '2', 0 }, { '3', 1 }, { '4', 2 }, { '5', 3 }, { '6', 4 },
    { '7', 5 }, { '8', 6 }, { '9', 7 }, { 'T', 8 }, { 'J', 9 },
    { 'Q', 10 }, { 'K', 11 }, { 'A', 12 },
};

const CardRank cardRank2 =
{
    { '2', 0 }, { '3', 1 }, { '4', 2 }, { '5', 3 }, { '6', 4 },
    { '7', 5 }, { '8', 6 }, { '9', 7 }, { 'T', 8 }, { 'J', -1 },
    { 'Q', 10 }, { 'K', 11 }, { 'A', 12 },
};

struct CardCompare
{
    const CardRank& cardRank;

    CardCompare(const CardRank& cardRank) :
        cardRank(cardRank)
    {
    }

    bool operator()(char a, char b) const
    {
        return cardRank.at(a) < cardRank.at(b);
    }
};

struct Hand
{
    std::string cards;
    size_t bid;

    int type(const CardRank& cardRank) const
    {
        std::string s(cards);
        std::sort(s.begin(), s.end(), CardCompare(cardRank));

        int joker = 0;

        for (auto& c : s)
        {
            if (cardRank.at(c) == -1)
            {
                joker++;
            }
        }

        switch (joker)
        {
            case 1:
                return type4(s);

            case 2:
                return type3(s);

            case 3:
                return type2(s);

            case 4:
            case 5:
                return 6;
        }

        return type5(s);
    }

    int type2(const std::string& s) const
    {
        if (s[3] == s[4])
        {
            return 6;
        }

        return 5;
    }

    int type3(const std::string& s) const
    {
        if ((s[2] == s[3]) && (s[3] == s[4]))
        {
            return 6;
        }

        if ((s[2] == s[3]) || (s[3] == s[4]))
        {
            return 5;
        }

        return 3;
    }

    int type4(const std::string& s) const
    {
        if ((s[1] == s[2]) && (s[2] == s[3]) && (s[3] == s[4]))
        {
            return 6;
        }

        if (((s[1] == s[2]) && (s[2] == s[3]))
                || ((s[2] == s[3]) && (s[3] == s[4])))
        {
            return 5;
        }

        if ((s[1] == s[2]) && (s[3] == s[4]))
        {
            return 4;
        }

        if ((s[1] == s[2]) || (s[2] == s[3]) || (s[3] == s[4]))
        {
            return 3;
        }

        return 1;
    }

    int type5(const std::string& s) const
    {
        if ((s[0] == s[1]) && (s[1] == s[2])
                && (s[2] == s[3]) && (s[3] == s[4]))
        {
            return 6;
        }

        if (((s[0] == s[1]) && (s[1] == s[2]) && (s[2] == s[3]))
                || ((s[1] == s[2]) && (s[2] == s[3]) && (s[3] == s[4])))
        {
            return 5;
        }

        if (((s[0] == s[1]) && (s[1] == s[2]) && (s[3] == s[4]))
                || ((s[0] == s[1]) && (s[2] == s[3]) && (s[3] == s[4])))
        {
            return 4;
        }

        if (((s[0] == s[1]) && (s[1] == s[2]))
                || ((s[1] == s[2]) && (s[2] == s[3]))
                || ((s[2] == s[3]) && (s[3] == s[4])))
        {
            return 3;
        }

        if (((s[0] == s[1]) && (s[2] == s[3]))
                || ((s[0] == s[1]) && (s[3] == s[4]))
                || ((s[1] == s[2]) && (s[3] == s[4])))
        {
            return 2;
        }

        if ((s[0] == s[1]) || (s[1] == s[2])
                || (s[2] == s[3]) || (s[3] == s[4]))
        {
            return 1;
        }

        return 0;
    }
};

struct HandCompare
{
    const CardRank& cardRank;

    HandCompare(const CardRank& cardRank) :
        cardRank(cardRank)
    {
    }

    bool operator()(const Hand& a, const Hand& b) const
    {
        if (a.type(cardRank) < b.type(cardRank))
        {
            return true;
        }

        if (a.type(cardRank) == b.type(cardRank))
        {
            for (size_t i = 0; i < 5; i++)
            {
                if (cardRank.at(a.cards[i]) < cardRank.at(b.cards[i]))
                {
                    return true;
                }

                if (cardRank.at(a.cards[i]) > cardRank.at(b.cards[i]))
                {
                    return false;
                }
            }
        }

        return false;
    }
};

void evaluate(std::list<Hand>& hands, const CardRank& cardRank)
{
    hands.sort(HandCompare(cardRank));

    size_t result = 0;
    size_t rank = 1;

    for (auto& h : hands)
    {
        result += h.bid * rank;
        rank++;
    }

    std::cout << result << std::endl;
}

int main(void)
{
    std::list<Hand> hands;
    std::string line;

    while (std::cin.good())
    {
        Hand hand;
        std::cin >> hand.cards >> hand.bid;

        if (std::cin.good())
        {
            hands.push_back(hand);
        }
    }

    evaluate(hands, cardRank1);
    evaluate(hands, cardRank2);
    return 0;
}
