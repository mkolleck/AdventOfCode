// https://adventofcode.com/2021/day/6

#include <iostream>
#include <valarray>

int main(void)
{
    std::valarray<size_t> population;
    population.resize(9);

    while (!std::cin.eof())
    {
        int age; char comma;
        std::cin >> age >> comma;
        population[age]++;
    }

    for (int i = 0; i < 256; i++)
    {
        size_t born = population[0];

        for (int j = 0; j < 8; j++)
        {
            population[j] = population[j + 1];
        }

        population[6] += born;
        population[8] = born;

        if (i == 79)
        {
            std::cout << population.sum() << std::endl;
        }
    }

    std::cout << population.sum() << std::endl;
    return 0;
}
