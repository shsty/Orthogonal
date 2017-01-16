#ifndef PLAYER_H
#define PLAYER_H

class Player{
public:
    float x, y, z, w;
    float vx, vy, vz, vw;
    float speed;
    float boxx, boxy;
    float height, width;
    int spritenum1, spritenum2;
    Player();

    float x1(){return x + boxx;}
    void x1_set(float v){x = v - boxx;}
    float x2(){return x + boxx + width;}
    void x2_set(float v){x = v - boxx - width;}

    float y1(){return y + boxy;}
    void y1_set(float v){y = v - boxy;}
    float y2(){return y + boxy + height;}
    void y2_set(float v){y = v - boxy - height;}

    float z1(){return z + boxx;}
    void z1_set(float v){z = v - boxx;}
    float z2(){return z + boxx + width;}
    void z2_set(float v){z = v - boxx - width;}

    float w1(){return w + boxy;}
    void w1_set(float v){w = v - boxy;}
    float w2(){return w + boxy + height;}
    void w2_set(float v){w = v - boxy - height;}

};

#endif
