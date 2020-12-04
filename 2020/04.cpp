// https://adventofcode.com/2020/day/4

#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <sstream>

typedef std::map<std::string, std::string> Passport;

struct Validator
{
    virtual bool isValid(const std::string& value) const = 0;
};

struct Year : public Validator
{
    const int min;
    const int max;

    Year(int min, int max) : min(min), max(max) { }

    virtual bool isValid(const std::string& value) const
    {
        int year = std::stol(value);
        return (min <= year) && (year <= max);
    }
};

struct BirthYear : public Year
{
    BirthYear() : Year(1920, 2002) { }
};

struct IssueYear : public Year
{
    IssueYear() : Year(2010, 2020) { }
};

struct ExpirationYear : public Year
{
    ExpirationYear() : Year(2020, 2030) { }
};

struct Height: public Validator
{
    virtual bool isValid(const std::string& value) const
    {
        return isValid(value, "cm", 150, 193) || isValid(value, "in", 59, 76);
    }

    static bool isValid(const std::string& value, const std::string& unit,
        int min, int max)
    {
        size_t u = value.find(unit);

        if (u != std::string::npos)
        {
            int height = std::stol(value.substr(0, u));

            if ((min <= height) && (height <= max))
            {
                return true;
            }
        }

        return false;
    }
};

struct HairColor: public Validator
{
    virtual bool isValid(const std::string& value) const
    {
        return std::regex_match(value, std::regex("^#[0-9a-f]\{6}$"));
    }
};

struct EyeColor: public Validator
{
    virtual bool isValid(const std::string& value) const
    {
        static const std::set<std::string> colors =
        {
            "amb", "blu", "brn", "gry", "grn", "hzl", "oth"
        };

        return colors.find(value) != colors.end();
    }
};

struct PassportID : public Validator
{
    virtual bool isValid(const std::string& value) const
    {
        return std::regex_match(value, std::regex("^[0-9]\{9}$"));
    }
};

static void validate(int&valid1, int& invalid1, int&valid2, int& invalid2,
        const Passport& passport)
{
    static const std::map<std::string, const Validator* const> validators =
    {
        { "byr", new BirthYear },
        { "iyr", new IssueYear },
        { "eyr", new ExpirationYear },
        { "hgt", new Height },
        { "hcl", new HairColor },
        { "ecl", new EyeColor },
        { "pid", new PassportID }
    };

    for (auto& v : validators)
    {
        Passport::const_iterator value = passport.find(v.first);

        if (value == passport.end())
        {
            invalid1++;
            invalid2++;
            return;
        }

        if (!v.second->isValid(value->second))
        {
            valid1++;
            invalid2++;
            return;
        }
    }

    valid1++;
    valid2++;
}

int main(void)
{
    int valid1 = 0, invalid1 = 0;
    int valid2 = 0, invalid2 = 0;
    Passport passport;
    std::string line;

    while (!(std::getline(std::cin, line)).eof())
    {
        if (line.empty())
        {
            validate(valid1, invalid1, valid2, invalid2, passport);
            passport.clear();
            continue;
        }

        std::istringstream parser(line + "\n");
        std::string entry;

        while (!(parser >> entry).eof())
        {
            size_t colon = entry.find(":");

            if (colon == std::string::npos)
            {
                std::cerr << "Invalid input: " << entry << std::endl;
            }

            passport[entry.substr(0, colon)] = entry.substr(colon + 1);
        }
    }

    // Handle the last entry, if there was no empty line at the end.
    if (!passport.empty())
    {
        validate(valid1, invalid1, valid2, invalid2, passport);
    }

    std::cout << "Part 1: valid = " << valid1 << ", invalid = " << invalid1
        << "\nPart 2: valid " << valid2 << ", invalid = " << invalid2
        << "\nTotal: " << valid1 + invalid1 << " - " << valid2 + invalid2
        << std::endl;
    return 0;
}
