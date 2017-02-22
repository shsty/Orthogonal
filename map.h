#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <json/json.h>
#include "declaration.h"
#include "base.h"

class Map{
public:
    typedef std::vector<BlockType *> BlockArray;
    BlockArray blockTypes;

    int size;
    int bsize;
    std::vector<int> blocks;
    int version;
    bool update;

    vec4double initpos;

    Map(int _size);
    ~Map();

    void clear();
    int get(int x, int y, int z, int w);
    int get(vec4int v){return get(v.x, v.y, v.z, v.w);}
    BlockType * getBlockType(int x, int y, int z, int w){return blockTypes[get(x, y, z, w)];}
    void set(int block, int x, int y, int z, int w);
    void set(int block, vec4int v){set(block, v.x, v.y, v.z, v.w);}

    Json::Value toJson();
    void fromJson(Json::Value json);
    void load(const std::string & filename);
    void save(const std::string & filename);

    void fill(int block, int x1, int x2, int y1, int y2, int z1, int z2, int w1, int w2);

    void render(Player * player, Renderer * ren);
    void initBlockTypes();
    void clearBlockTypes();
};

#endif
