// https://adventofcode.com/2024/day/9

#include <iostream>
#include <vector>

struct File
{
    int id;
    size_t offset;
    size_t size;
};

struct FreeSpace
{
    size_t offset;
    size_t size;
};

static long long int checksum(const std::vector<int>& fs)
{
    long long int result = 0;

    for (long long int i = 0; (size_t)(i) < fs.size(); i++)
    {
        if (fs[i] != -1)
        {
            result += i * fs[i];
        }
    }

    return result;
}

static long long int defrag1(std::vector<int> fs)
{
    for (size_t i = 0; i < fs.size(); i++)
    {
        if (fs[i] != -1)
        {
            continue;
        }

        while (fs.back() == -1)
        {
            fs.pop_back();
        }

        if (i < fs.size())
        {
            fs[i] = fs.back();
            fs.pop_back();
        }
    }

    return checksum(fs);
}

static long long int defrag2(std::vector<int> fs, std::vector<File>& files,
        std::vector<FreeSpace>& freeSpace)
{
    for (std::vector<File>::reverse_iterator f = files.rbegin();
            f != files.rend(); f++)
    {
        for (size_t i = 0; i < freeSpace.size(); i++)
        {
            if ((freeSpace[i].offset < f->offset)
                    && (freeSpace[i].size >= f->size))
            {
                for (size_t j = 0; j < f->size; j++)
                {
                    fs[freeSpace[i].offset] = f->id;
                    fs[f->offset + j] = -1;
                    freeSpace[i].offset++;
                    freeSpace[i].size--;
                }

                break;
            }
        }
    }

    return checksum(fs);
}

int main(void)
{
    std::vector<int> fs;
    std::vector<File> files;
    std::vector<FreeSpace> freeSpace;

    int fid = 0;
    bool empty = false;

    while (true)
    {
        char c;
        int f = -1;
        std::cin >> c;

        if (!std::cin.good())
        {
            break;
        }

        if (!empty)
        {
            files.push_back(File({ fid, fs.size(), (size_t)(c - '0') }));
            f = fid;
            fid++;
        }
        else
        {
            freeSpace.push_back(FreeSpace({ fs.size(), (size_t)(c - '0') }));
        }

        for (char i = '0'; i < c; i++)
        {
            fs.push_back(f);
        }

        empty = !empty;
    }

    std::cout << defrag1(fs) << std::endl
        << defrag2(fs, files, freeSpace) << std::endl;
    return 0;
}
