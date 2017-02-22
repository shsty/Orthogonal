#ifndef PLAYER_H
#define PLAYER_H

#include "declaration.h"
#include "object.h"

class Player:public Object{
public:
    //things about jumping
    double multg;
    double jumpspeed;
    bool jumpflag1, jumpflag2;
    double speed;
    double acc;

    Player();

    void init(Map * map);
    void react(const unsigned char * keystate, double dt);
};

#endif
