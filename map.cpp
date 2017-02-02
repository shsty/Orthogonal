#include <exception>
#include <stdexcept>
#include <cstdio> 
#include <cstring> 
#include <SDL2/SDL.h> 
#include "map.h"
#include "player.h"
#include "renderer.h"

const struct blocktype Map::blockTypes[16] = {
    {1, 0},
    {0, 1},
    {0, 1},
    {0, 1},
    {0, 1},
    {0, 1},
    {0, 1},
    {0, 1},
    {0, 1},
    {0, 1},
    {0, 1},
    {0, 1},
    {0, 1},
    {0, 1},
    {0, 1},
    {0, 1}
};

Map::Map(int _size){
    size = _size;
    bsize = size * size * size * size;
    version = 1;
    blocks = new int[bsize];
    memset(blocks, 0, bsize*sizeof(int));
}

Map::~Map(){
    delete[] blocks;
}

void Map::clear(){
    memset(blocks, 0, bsize*sizeof(int));
}

void Map::load(const std::string & filename){
    FILE* f = fopen(filename.c_str(), "r");
    if (f == nullptr) throw std::runtime_error("I/O error: " + filename + " : " + strerror(errno));
    if (!fscanf(f, "%d", &version)) {
        fclose(f);
        throw std::runtime_error("I/O error: " + filename + " : malformed data");
    }

    for (int i = 0; i < bsize; ++i){
        if (!fscanf(f, "%d", &blocks[i])){
            fclose(f);
            throw std::runtime_error("I/O error: " + filename + " : malformed data");
        }
    }

    fclose(f);
}

void Map::save(const std::string & filename){
    FILE* f = fopen(filename.c_str(), "w");
    if (f == nullptr) throw std::runtime_error("I/O error: " + filename + " : " + strerror(errno));

    fprintf(f, "%d\n", version);
    for (int i = 0; i < bsize; ++i){
        fprintf(f, "%d ", blocks[i]);
    }
    fclose(f);
}

int Map::get(int x, int y, int z, int w){
    if ((x < 0) || (x >= size) ||
            (y < 0) || (y >= size) ||
            (z < 0) || (z >= size) ||
            (w < 0) || (w >= size))
        throw std::runtime_error("Runtime Error: map out of bound!");
    return blocks[((x*size + y)*size + z)*size + w];
}

int Map::getspritenum(int x, int y, int z, int w){
    return blockTypes[get(x, y, z, w)].spritenum;
}

void Map::set(int block, int x, int y, int z, int w){
    blocks[((x*size + y)*size + z)*size + w] = block;
}

inline void swap(int & x, int & y){
    int temp = x; x = y; y = temp;
}

void Map::fill(int block, int x1, int x2, int y1, int y2, int z1, int z2, int w1, int w2){
    if (x1 > x2) swap(x1, x2);
    if (y1 > y2) swap(y1, y2);
    if (z1 > z2) swap(z1, z2);
    if (w1 > w2) swap(w1, w2);
    for (int i = x1; i <= x2; ++i)
    for (int j = y1; j <= y2; ++j)
    for (int k = z1; k <= z2; ++k)
    for (int l = w1; l <= w2; ++l)
        set(block, i, j, k, l);
}

inline double min(double a, double b){return (a>b)?b:a;}
inline double max(double a, double b){return (a>b)?a:b;}

void Map::render(Player * player, Renderer * ren){
    double x1 = player->x1(), x2 = player->x2();
    double y1 = player->y1(), y2 = player->y2();
    double z1 = player->z1(), z2 = player->z2();
    double w1 = player->w1(), w2 = player->w2();
    double s1, ssum = 0;
    for (int z = (int)floor(z1); z < (int)ceil(z2); ++z)
        for (int w = (int)floor(w1); w < (int)ceil(w2); ++w){
            s1 = (min(z+1, z2) - max(z, z1)) * (min(w+1, w2) - max(w, w1));
            ssum += s1;
            for (int x = 0; x < size; ++x)
                for (int y = 0; y < size; ++y)
                    ren->blocktex->draw(ren->lfieldrect, x, y, 1, 1, getspritenum(x, y, z, w), s1/ssum);
        }
    ssum = 0;
    for (int x = (int)floor(x1); x < (int)ceil(x2); ++x)
        for (int y = (int)floor(y1); y < (int)ceil(y2); ++y){
            s1 = (min(x+1, x2) - max(x, x1)) * (min(y+1, y2) - max(y, y1));
            ssum += s1;
            for (int z = 0; z < size; ++z)
                for (int w = 0; w < size; ++w)
                    ren->blocktex->draw(ren->rfieldrect, z, w, 1, 1, getspritenum(x, y, z, w), s1/ssum);
        }
}
