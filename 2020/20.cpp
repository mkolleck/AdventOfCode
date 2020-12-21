// https://adventofcode.com/2020/day/20

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

enum Side { North, South, West, East };

struct Tile
{
    long long int id;
    int dim;
    std::string t;

    void flip(int f)
    {
        if (f == 0) return;

        for (int i = 0; i < dim / 2; i++)
        {
            for (int j = 0; j < dim; j++)
            {
                std::swap(t[i * dim + j], t[(dim - 1 - i) * dim + j]);
            }
        }
    }

    void rotate(int degrees)
    {
        for ( ; degrees > 0; degrees -= 90)
        {
            for (int i = 0; i < dim / 2; i++)
            {
                for (int j = 0; j < dim / 2; j++)
                {
                    char c = t[i * dim + j];
                    t[i * dim + j] = t[j * dim + dim - 1 - i];
                    t[j * dim + dim - 1 - i] = t[(dim - 1 - i) * dim + dim - 1 - j];
                    t[(dim - 1 - i) * dim + dim - 1 - j] = t[(dim - 1 - j) * dim + i];
                    t[(dim - 1 - j) * dim + i] = c;
                }
            }
        }
    }

    std::string border(Side side) const
    {
        std::string result;

        switch (side)
        {
            case North:
                result = t.substr(0, dim);
                break;

            case South:
                result = t.substr(dim * (dim - 1));
                break;

            case West:
                for (int i = 0; i < dim; i++) result += t[i * dim];
                break;

            case East:
                for (int i = 0; i < dim; i++) result += t[i * dim + dim - 1];
                break;
        }

        return result;
    }
};

struct Border
{
    int id, f, r;
    std::string n, s, w, e;

    Border(void) : id(0), f(0), r(0), n(), s(), w(), e() { }
    Border(const Tile& t, int f, int r) : id(t.id), f(f), r(r), n(), s(), w(), e()
    {
        n = t.border(North);
        s = t.border(South);
        w = t.border(West);
        e = t.border(East);
    }
};

struct ByBorder
{
    int id;
    ByBorder(const Border& b) : id(b.id) { }
    bool operator()(const Tile& t) const { return (id == t.id); }
};

typedef std::vector<Tile> Tiles;
typedef std::vector<Border> Borders;

static void assemble(Tiles& tiles, const Border& b, int i)
{
    Tiles::iterator t = std::find_if(tiles.begin() + i, tiles.end(), ByBorder(b));
    t->flip(b.f);
    t->rotate(b.r);
    std::swap(*(tiles.begin() + i), *t);
}

static void monsters(Tile& image)
{
    for (int i = 0; i < image.dim - 2; i++)
    {
        for (int j = 0; j < image.dim - 20; j++)
        {
            if ((image.t[i * image.dim + j + 18] == '#')
                    && (image.t[(i + 1) * image.dim + j] == '#')
                    && (image.t[(i + 1) * image.dim + j + 5] == '#')
                    && (image.t[(i + 1) * image.dim + j + 6] == '#')
                    && (image.t[(i + 1) * image.dim + j + 11] == '#')
                    && (image.t[(i + 1) * image.dim + j + 12] == '#')
                    && (image.t[(i + 1) * image.dim + j + 17] == '#')
                    && (image.t[(i + 1) * image.dim + j + 18] == '#')
                    && (image.t[(i + 1) * image.dim + j + 19] == '#')
                    && (image.t[(i + 2) * image.dim + j + 1] == '#')
                    && (image.t[(i + 2) * image.dim + j + 4] == '#')
                    && (image.t[(i + 2) * image.dim + j + 7] == '#')
                    && (image.t[(i + 2) * image.dim + j + 10] == '#')
                    && (image.t[(i + 2) * image.dim + j + 13] == '#')
                    && (image.t[(i + 2) * image.dim + j + 16] == '#'))
            {
                image.t[i * image.dim + j + 18] = 'O';
                image.t[(i + 1) * image.dim + j] = 'O';
                image.t[(i + 1) * image.dim + j + 5] = 'O';
                image.t[(i + 1) * image.dim + j + 6] = 'O';
                image.t[(i + 1) * image.dim + j + 11] = 'O';
                image.t[(i + 1) * image.dim + j + 12] = 'O';
                image.t[(i + 1) * image.dim + j + 17] = 'O';
                image.t[(i + 1) * image.dim + j + 18] = 'O';
                image.t[(i + 1) * image.dim + j + 19] = 'O';
                image.t[(i + 2) * image.dim + j + 1] = 'O';
                image.t[(i + 2) * image.dim + j + 4] = 'O';
                image.t[(i + 2) * image.dim + j + 7] = 'O';
                image.t[(i + 2) * image.dim + j + 10] = 'O';
                image.t[(i + 2) * image.dim + j + 13] = 'O';
                image.t[(i + 2) * image.dim + j + 16] = 'O';
            }
        }
    }
}

int main(void)
{
    Tile image; image.id = 0;
    Tiles tiles;
    Borders borders;
    std::string line;

    while (!(std::getline(std::cin, line)).eof())
    {
        Tile t;
        t.id = std::stoi(line.substr(5));

        do
        {
            std::getline(std::cin, line);
            t.t += line;
        } while (!line.empty());

        t.dim = sqrt(t.t.length());
        tiles.push_back(t);
    }

    for (auto& t : tiles)
    {
        for (int f = 0; f < 2; ++f)
        {
            for (int r = 0; r < 4; r++)
            {
                borders.push_back(Border(t, f, r * 90));
                t.rotate(90);
            }

            t.flip(1);
        }
    }

    for (const auto& b : borders)
    {
        Borders::const_iterator n = std::find_if(borders.begin(), borders.end(),
                [&b](const Border& o) { return (b.id != o.id) && (b.n == o.s); });
        Borders::const_iterator w = std::find_if(borders.begin(), borders.end(),
                [&b](const Border& o) { return (b.id != o.id) && (b.w == o.e); });

        if ((n == borders.end()) && (w == borders.end()))
        {
            assemble(tiles, b, 0);
            break;
        }
    }

    int dim = sqrt(tiles.size());
    int tileDim = tiles.front().dim;
    image.dim = dim * (tileDim - 2);

    for (int i = 0; i < dim; i++)
    {
        std::string s = tiles[i * dim].border(South);

        for (int j = 1; j < dim; j++)
        {
            std::string e = tiles[i * dim + j - 1].border(East);

            for (Borders::const_iterator b = borders.begin(); b != borders.end(); b++)
            {
                if ((e == b->w) && (std::find_if(tiles.begin() + i * dim + j,
                                tiles.end(), ByBorder(*b)) != tiles.end()))
                {
                    assemble(tiles, *b, i * dim + j);
                    break;
                }
            }
        }

        for (Borders::const_iterator b = borders.begin(); b != borders.end(); b++)
        {
            if ((s == b->n) && (std::find_if(tiles.begin() + (i + 1) * dim,
                            tiles.end(), ByBorder(*b)) != tiles.end()))
            {
                assemble(tiles, *b, (i + 1) * dim);
                break;
            }
        }
    }

    for (int i = 0; i < dim; i++)
    {
        for (int l = 1; l < tileDim - 1; l++)
        {
            for (int j = 0; j < dim; j++)
            {
                image.t += tiles[i * dim + j].t.substr(l * tileDim + 1, tileDim - 2);
            }
        }
    }

    for (int f = 0; f < 2; ++f)
    {
        for (int r = 0; r < 4; r++)
        {
            monsters(image);
            image.rotate(90);
        }

        image.flip(1);
    }

    std::cout << tiles[0].id * tiles[dim - 1].id
        * tiles[dim * (dim - 1)].id * tiles[dim * dim - 1].id << std::endl;
    std::cout << std::count_if(image.t.cbegin(), image.t.cend(),
            [](char c) { return c == '#'; }) << std::endl;
    return 0;
}
