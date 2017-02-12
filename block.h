#ifndef BLOCK_H
#define BLOCK_H

#include <string>

class Player;
class Renderer;

class BlockType{
public:
    int x, y, z, w;
    int passable;
    int leftSpriteNum;
    int rightSpriteNum;

    virtual void renderLeft(Renderer * ren, double alpha = 1.0);
    virtual void renderRight(Renderer * ren, double alpha = 1.0);

    virtual void collide(Player * player, int dir);
    virtual void overlay(Player * player);
};

class B_Air:BlockType{
};

class B_Solid:BlockType{
};

class B_Spike:B_Air{
};

BlockType * decode(){
}

std::string encode(BlockType *){
}

#endif
