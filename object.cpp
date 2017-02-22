#include <cmath>
#include "object.h"
#include "map.h"
#include "block.h"
#include "renderer.h"

using std::max;
using std::min;

void Object::move(Map * map, double dt){
    // boundary detect
    if (x1() + v.x * dt < 0) {
        v.x = 0;
        x1_set(0);
    }
    if (x2() + v.x * dt > map->size) {
        v.x = 0;
        x2_set(map->size);
    }
    if (y1() + v.y * dt < 0) {
        v.y = 0;
        y1_set(0);
        ground1 = true;
    }
    if (y2() + v.y * dt > map->size) {
        v.y = 0;
        y2_set(map->size);
    }

    if (z1() + v.z * dt < 0) {
        v.z = 0;
        z1_set(0);
    }
    if (z2() + v.z * dt > map->size) {
        v.z = 0;
        z2_set(map->size);
    }
    if (w1() + v.w * dt < 0) {
        v.w = 0;
        w1_set(0);
        ground2 = true;
    }
    if (w2() + v.w * dt > map->size) {
        v.w = 0;
        w2_set(map->size);
    }

    //collision detect and moving
    if (v.x < 0){ 
        for (int i = max(0, (int)floor(x1() + v.x * dt)); i < min((int)ceil(x1()), map->size); ++i)
        for (int j = max(0, (int)floor(y1())); j < min((int)ceil(y2()), map->size); ++j)
        for (int k = max(0, (int)floor(z1())); k < min((int)ceil(z2()), map->size); ++k)
        for (int l = max(0, (int)floor(w1())); l < min((int)ceil(w2()), map->size); ++l)
            map->getBlockType(i, j, k, l)->collide(this, P_xNegative, vec4int(i,j,k,l));
    }
    if (v.x > 0){
        for (int i = max(0, (int)floor(x2())); i < min((int)ceil(x2() + v.x * dt), map->size); ++i)
        for (int j = max(0, (int)floor(y1())); j < min((int)ceil(y2()), map->size); ++j)
        for (int k = max(0, (int)floor(z1())); k < min((int)ceil(z2()), map->size); ++k)
        for (int l = max(0, (int)floor(w1())); l < min((int)ceil(w2()), map->size); ++l)
            map->getBlockType(i, j, k, l)->collide(this, P_xPositive, vec4int(i,j,k,l));
    }
    pos.x += v.x * dt;

    if (v.y < 0){ 
        for (int i = max(0, (int)floor(x1())); i < min((int)ceil(x2()), map->size); ++i)
        for (int j = max(0, (int)floor(y1() + v.y * dt)); j < min((int)ceil(y1()), map->size); ++j)
        for (int k = max(0, (int)floor(z1())); k < min((int)ceil(z2()), map->size); ++k)
        for (int l = max(0, (int)floor(w1())); l < min((int)ceil(w2()), map->size); ++l)
            map->getBlockType(i, j, k, l)->collide(this, P_yNegative, vec4int(i,j,k,l));
    }
    if (v.y > 0){
        for (int i = max(0, (int)floor(x1())); i < min((int)ceil(x2()), map->size); ++i)
        for (int j = max(0, (int)floor(y2())); j < min((int)ceil(y2() + v.y * dt), map->size); ++j)
        for (int k = max(0, (int)floor(z1())); k < min((int)ceil(z2()), map->size); ++k)
        for (int l = max(0, (int)floor(w1())); l < min((int)ceil(w2()), map->size); ++l)
            map->getBlockType(i, j, k, l)->collide(this, P_yPositive, vec4int(i,j,k,l));
    }
    pos.y += v.y * dt;
    if (v.y < 0) ground1 = false;

    if (v.z < 0){ 
        for (int i = max(0, (int)floor(x1())); i < min((int)ceil(x2()), map->size); ++i)
        for (int j = max(0, (int)floor(y1())); j < min((int)ceil(y2()), map->size); ++j)
        for (int k = max(0, (int)floor(z1() + v.z * dt)); k < min((int)ceil(z1()), map->size); ++k)
        for (int l = max(0, (int)floor(w1())); l < min((int)ceil(w2()), map->size); ++l)
            map->getBlockType(i, j, k, l)->collide(this, P_zNegative, vec4int(i,j,k,l));
    }
    if (v.z > 0){
        for (int i = max(0, (int)floor(x1())); i < min((int)ceil(x2()), map->size); ++i)
        for (int j = max(0, (int)floor(y1())); j < min((int)ceil(y2()), map->size); ++j)
        for (int k = max(0, (int)floor(z2())); k < min((int)ceil(z2() + v.z * dt), map->size); ++k)
        for (int l = max(0, (int)floor(w1())); l < min((int)ceil(w2()), map->size); ++l)
            map->getBlockType(i, j, k, l)->collide(this, P_zPositive, vec4int(i,j,k,l));
    }
    pos.z += v.z * dt;

    if (v.w < 0){ 
        for (int i = max(0, (int)floor(x1())); i < min((int)ceil(x2()), map->size); ++i)
        for (int j = max(0, (int)floor(y1())); j < min((int)ceil(y2()), map->size); ++j)
        for (int k = max(0, (int)floor(z1())); k < min((int)ceil(z2()), map->size); ++k)
        for (int l = max(0, (int)floor(w1() + v.w * dt)); l < min((int)ceil(w1()), map->size); ++l)
            map->getBlockType(i, j, k, l)->collide(this, P_wNegative, vec4int(i,j,k,l));
    }
    if (v.w > 0){
        for (int i = max(0, (int)floor(x1())); i < min((int)ceil(x2()), map->size); ++i)
        for (int j = max(0, (int)floor(y1())); j < min((int)ceil(y2()), map->size); ++j)
        for (int k = max(0, (int)floor(z1())); k < min((int)ceil(z2()), map->size); ++k)
        for (int l = max(0, (int)floor(w2())); l < min((int)ceil(w2() + v.w * dt), map->size); ++l)
            map->getBlockType(i, j, k, l)->collide(this, P_wPositive, vec4int(i,j,k,l));
    }
    pos.w += v.w * dt;
    if (v.w < 0) ground2 = false;

}

void Object::render(Renderer * ren){
    ren->tex[lSpriteName]->draw(ren->lfieldrect, x1(), y1(), box.width1(), box.height1(), lSpriteNum);
    ren->tex[rSpriteName]->draw(ren->rfieldrect, z1(), w1(), box.width2(), box.height2(), rSpriteNum);
}
