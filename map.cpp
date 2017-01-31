#include <exception>
#include <stdexcept>
#include <cstdio>
#include <cstring>
#include <SDL2/SDL.h>
#include "map.h"
#include "player.h"
#include "renderer.h"

const struct blocktype Map::blockTypes[2] = {
    {1, 0},
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

void Map::render(Player * player, Renderer * ren){
    int x = int(player->x);
    int y = int(player->y);
    int z = int(player->z);
    int w = int(player->w);
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j){
            int b = get(i, j, z, w);
            ren->blocktex->draw(ren->lfieldrect, i, j, 1, 1, b);
        }
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j){
            int b = get(x, y, i, j);
            ren->blocktex->draw(ren->rfieldrect, i, j, 1, 1, b);
        }
}
