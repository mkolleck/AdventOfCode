// https://adventofcode.com/2020/day/5

#include <iostream>
#include <set>

int main(void)
{
    std::set<int> seats;
    std::string line;

    while (!(std::cin >> line).eof())
    {
        int seat = 0;

        for (const auto& c : line)
        {
            switch (c)
            {
                case 'F':
                case 'L':
                    break;

                case 'B':
                case 'R':
                    seat += 1;
                    break;

                default:
                    std::cerr << "Invalid seat: " << line << std::endl;
                    return 1;
            }

            seat <<= 1;
        }

        seats.insert(seat >> 1);
    }

    std::cout << "Max: " << *(--seats.end()) << std::endl;

    int prev = *(seats.begin());

    for (const auto& seat: seats)
    {
        if (seat - prev > 1)
        {
            std::cout << "My Seat: " << prev + 1 << std::endl;
            break;
        }

        prev = seat;
    }
    
    return 0;
}
