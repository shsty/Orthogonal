#ifndef MAP_H
#define MAP_H

#include <string>

struct blocktype{
    int passable;
    int spritenum;
};

class Map{
public:
    int size;
    int bsize;
    int * blocks;
    int version;

    Map(int _size);
    ~Map();

    void clear();
    int get(int x, int y, int z, int w);
    void set(int block, int x, int y, int z, int w);
    void load(const std::string & filename);
    void save(const std::string & filename);

    void fill(int block, int x1, int x2, int y1, int y2, int z1, int z2, int w1, int w2);
};

struct Cursor{
    int x1, x2, y1, y2, z1, z2, w1, w2;
    int xprev, yprev, zprev, wprev;
    bool active1, active2;
    enum Cfields {C_None, C_Field1, C_Field2} focus;
};

#endif
