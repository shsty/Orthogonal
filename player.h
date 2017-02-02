#ifndef PLAYER_H
#define PLAYER_H

class Renderer;
class Map;

class Player{
public:
    double x, y, z, w;
    double vx, vy, vz, vw;
    double boxx, boxy;
    double height, width;
    int spritenum1, spritenum2;

    //things about jumping
    double jumpheight, jumptime, jumpdistance, multg;
    double g, jumpspeed, speed;
    bool hasgravity;
    bool jumpflag1, jumpflag2;
    bool ground1, ground2;

    Player();

    double x1(){return x + boxx;}
    void x1_set(double v){x = v - boxx;}
    double x2(){return x + boxx + width;}
    void x2_set(double v){x = v - boxx - width;}

    double y1(){return y + boxy;}
    void y1_set(double v){y = v - boxy;}
    double y2(){return y + boxy + height;}
    void y2_set(double v){y = v - boxy - height;}

    double z1(){return z + boxx;}
    void z1_set(double v){z = v - boxx;}
    double z2(){return z + boxx + width;}
    void z2_set(double v){z = v - boxx - width;}

    double w1(){return w + boxy;}
    void w1_set(double v){w = v - boxy;}
    double w2(){return w + boxy + height;}
    void w2_set(double v){w = v - boxy - height;}

    void render(Renderer * ren);
    void move(const unsigned char* keystate, Map * map, double dt);
};

#endif
