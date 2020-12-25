// https://adventofcode.com/2020/day/25

#include <iostream>

inline long long int step(long long int v, long long int s)
{
    return (v * s) % 20201227;
}

int main(void)
{
    long long int pk1, pk2, t = 1, ek1 = 1, ek2 = 1, ek = 0;
    std::cin >> pk1 >> pk2;

    int found = 0;

    for (long long int i = 1; ek == 0; i++)
    {
        t = step(t, 7);
        ek1 = step(ek1, pk2);
        ek2 = step(ek2, pk1);

        if (t == pk1) ek = ek1;
        if (t == pk2) ek = ek2;
    }

    std::cout << ek << std::endl;
    return 0;
}
