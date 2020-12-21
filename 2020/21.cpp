// https://adventofcode.com/2020/day/21

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>

typedef std::set<std::string> Ingredients;

struct Food
{
    Ingredients i;
    Ingredients a;

    Food(const std::string& line) : i(), a()
    {
        std::istringstream s(line);
        std::string token;
        bool ingredients = true;

        do
        {
            s >> token;

            if (token == "(contains")
            {
                ingredients = false;
            }
            else if (ingredients)
            {
                i.insert(token);
            }
            else
            {
                token.pop_back();
                a.insert(token);
            }
        } while (!s.eof());
    }
};

int main(void)
{
    std::string line;
    std::vector<Food> foods;

    Ingredients ingredients;
    Ingredients allergens;
    std::map<std::string, Ingredients> mapping;

    int count = 0;
    std::string canon;

    while (!(std::getline(std::cin, line)).eof())
    {
        foods.push_back(Food(line));
        ingredients.insert(foods.back().i.begin(), foods.back().i.end());
        allergens.insert(foods.back().a.begin(), foods.back().a.end());
    }

    for (const auto& a : allergens)
    {
        Ingredients ai;

        for (const auto& f : foods)
        {
            if (f.a.find(a) != f.a.end())
            {
                if (ai.empty())
                {
                    ai = f.i;
                }
                else
                {
                    Ingredients ci;
                    std::set_intersection(f.i.begin(), f.i.end(), ai.begin(), ai.end(),
                            std::inserter(ci, ci.begin()));
                    ai = ci;
                }
            }
        }

        mapping[a] = ai;

        for (const auto& i : ai)
        {
            ingredients.erase(i);
        }
    }

    for (bool removed = true; removed;)
    {
        removed = false;

        for (const auto& a : allergens)
        {
            if (mapping[a].size() == 1)
            {
                for (auto& m : mapping)
                {
                    if ((m.first != a) && (m.second.size() > 1))
                    {
                        m.second.erase(*(mapping[a].begin()));
                        removed = true;
                    }
                }
            }
        }
    }

    for (const auto& i : ingredients)
    {
        for (const auto& f : foods)
        {
            if (f.i.find(i) != f.i.end())
            {
                count++;
            }
        }
    }

    for (auto& m : mapping)
    {
        canon += *(m.second.begin()) + ",";
    }

    canon.pop_back();
    std::cout << count << "\n" << canon << std::endl;
    return 0;
}
