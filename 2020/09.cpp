// https://adventofcode.com/2020/day/9

#include <iostream>
#include <vector>

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        return 1;
    }

    int p = std::stol(argv[1]);
    std::vector<int> numbers;
    int n = 0;

    while (!(std::cin >> n).eof())
    {
        if (numbers.size() >= p)
        {
            bool valid = false;

            for (int i = numbers.size() - p; (i < numbers.size()) && !valid; i++)
            {
                for (int j = i + 1; (j < numbers.size()) && !valid; j++)
                {
                    if (numbers[i] + numbers[j] == n)
                    {
                        valid = true;
                    }
                }
            }

            if (!valid)
            {
                std::cout << n << std::endl;

                int sum = 0;

                for (int i = 0; (i < numbers.size()) && (sum != n); i++)
                {
                    sum = numbers[i];

                    for (int j = i + 1; (j < numbers.size()) && (sum < n); j++)
                    {
                        sum += numbers[j];

                        if (sum == n)
                        {
                            int min = numbers[i], max = numbers[i];

                            for (int k = i; k <= j; k++)
                            {
                                if (numbers[k] < min)
                                {
                                    min = numbers[k];
                                }

                                if (numbers[k] > max)
                                {
                                    max = numbers[k];
                                }
                            }

                            std::cout << min + max << std::endl;
                        }
                    }
                }

                break;
            }
        }

        numbers.push_back(n);
    }

    return 0;
}
