#include <exception>
#include <stdexcept>
#include <fstream>
#include <cstring> 
#include <cmath>
#include <SDL2/SDL.h> 
#include <json/json.h>

#include "map.h"
#include "player.h"
#include "renderer.h"
#include "block.h"

using std::min;
using std::max;

Map::Map(){
    version = 1;
    updateVersion = false;
    initBlockTypes();

    dt = 18/1000.0;

    fixEntrance = true;
}

Map::~Map(){
}

void Map::addBlockType(BlockType::BlockType * blocktype){
    blocktype->map = this;
    blockTypes.push_back(blocktype);
}

void Map::initBlockTypes(){
    clearBlockTypes();
    addBlockType(new BlockType::StarsBG);
    addBlockType(new BlockType::Solid);
    addBlockType(new BlockType::Spike);
}

void Map::clearBlockTypes(){
    for (BlockArray::iterator i = blockTypes.begin(); i != blockTypes.end(); ++i)
        if ((*i) != nullptr) delete (*i);
    blockTypes.clear();
}

void Map::clear(){
    blocks.resize(bsize, 0);
}

void Map::load(const std::string & filename){
    std::ifstream f;
    f.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    f.open(filename);

    int fileversion = 0;
    Json::Value json;
    f >> fileversion;
    switch (fileversion){
        case 1:
            size = 16;
            bsize = size * size * size * size;
            blocks.resize(bsize, 0);
            initpos.x = 0.5;
            initpos.y = size - 1;
            initpos.z = 0.5;
            initpos.w = size - 1;

            for (int i = 0; i < bsize; ++i) f >> blocks[i];
            break;
        case 2:
            f >> json;
            fromJson(json);
            break;
        default:
            throw std::runtime_error("I/O error: " + filename + " : cannot identify file format");
            break;
    }

    if (!updateVersion && (fileversion < version)) version = fileversion;

    f.close();
}

void Map::save(const std::string & filename){
    std::ofstream f;
    f.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    f.open(filename);

    f << version << std::endl;
    switch (version){
        case 1:
            for (int i = 0; i < bsize; ++i) f << blocks[i] << " ";
            f << std::endl;
            break;
        case 2:
            f << toJson();
            f << std::endl;
            break;
        default:
            throw std::runtime_error("Invalid map version number");
            break;
    }

    f.close();
    SDL_Log("map saved to %s" , filename.c_str());
}

Json::Value Map::toJson(){
    Json::Value json;
    return json;
}

void Map::fromJson(Json::Value json){
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

void Map::update(){
    ++ticks;
}

void Map::render(Player * player, Renderer * ren){
    camerapos = player->pos;

    double x1 = player->x1(), x2 = player->x2();
    double y1 = player->y1(), y2 = player->y2();
    double z1 = player->z1(), z2 = player->z2();
    double w1 = player->w1(), w2 = player->w2();
    double s1, ssum = 0;
    for (int z = (int)floor(z1); z < (int)ceil(z2); ++z)
        for (int w = (int)floor(w1); w < (int)ceil(w2); ++w){
            s1 = (min((double)z+1, z2) - max((double)z, z1)) * (min((double)w+1, w2) - max((double)w, w1));
            ssum += s1;
            for (int x = 0; x < size; ++x)
                for (int y = 0; y < size; ++y)
                    getBlockType(x, y, z, w)->renderLeft(ren, x, y, s1/ssum);
        }
    ssum = 0;
    for (int x = (int)floor(x1); x < (int)ceil(x2); ++x)
        for (int y = (int)floor(y1); y < (int)ceil(y2); ++y){
            s1 = (min((double)x+1, x2) - max((double)x, x1)) * (min((double)y+1, y2) - max((double)y, y1));
            ssum += s1;
            for (int z = 0; z < size; ++z)
                for (int w = 0; w < size; ++w)
                    getBlockType(x, y, z, w)->renderRight(ren, z, w, s1/ssum);
        }
}
