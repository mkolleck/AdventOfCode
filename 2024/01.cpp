#include <cstdlib>

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

int main(void)
{
    int distance = 0, similarity = 0;
    std::vector<int> listA, listB;
    std::map<int, int> similarities;

    while (!std::cin.eof())
    {
        int a = 0, b = 0;
        std::cin >> a >> b;

        listA.push_back(a);
        listB.push_back(b);
        similarities[b]++;
    }

    std::sort(listA.begin(), listA.end());
    std::sort(listB.begin(), listB.end());

    for (size_t i = 0; i < listA.size(); i++)
    {
        distance += abs(listA[i] - listB[i]);
        similarity += listA[i] * similarities[listA[i]];
    }

    std::cout << distance << std::endl;
    std::cout << similarity << std::endl;
    return 0;
}
