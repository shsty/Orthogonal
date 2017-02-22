#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include "declaration.h"
#include "base.h"

class Object{
public:
    vec4double pos;
    vec4double v;
    box4double box;
    bool hasgravity;
    double g;
    bool ground1, ground2;

    std::string lSpriteName, rSpriteName;
    int lSpriteNum, rSpriteNum;

    double x1(){return pos.x + box.x1;}
    void x1_set(double v){pos.x = v - box.x1;}
    double x2(){return pos.x + box.x2;}
    void x2_set(double v){pos.x = v - box.x2;}

    double y1(){return pos.y + box.y1;}
    void y1_set(double v){pos.y = v - box.y1;}
    double y2(){return pos.y + box.y2;}
    void y2_set(double v){pos.y = v - box.y2;}

    double z1(){return pos.z + box.z1;}
    void z1_set(double v){pos.z = v - box.z1;}
    double z2(){return pos.z + box.z2;}
    void z2_set(double v){pos.z = v - box.z2;}

    double w1(){return pos.w + box.w1;}
    void w1_set(double v){pos.w = v - box.w1;}
    double w2(){return pos.w + box.w2;}
    void w2_set(double v){pos.w = v - box.w2;}

    Object():pos(), v(), box(){}
    virtual void render(Renderer * ren);
    virtual void move(Map * map, double dt);
};

#endif
