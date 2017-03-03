#include <cmath>
#include "main.h"
#include "object.h"
#include "map.h"
#include "block.h"
#include "renderer.h"

using std::max;
using std::min;

Object::Object(Map * _map):pos(), v(), box(){
    map = _map;
    actions = nullptr;
    addAction(new Action::boundaryDetect);
    addAction(new Action::blockDetectAndMove);
}

Object::~Object(){
    clearActions(actions);
}

void Object::update(){
    actions->chainact();
}

void Object::clearActions(Action::Action * _actions){
    if (_actions){
        clearActions(_actions->next);
        delete _actions;
    }
}

Object & Object::addAction(Action::Action * action){
    if (action){
        action->next = actions;
        action->obj = this;
        actions = action;
    }
    return (*this);
}

void Object::render(Renderer * ren){
    ren->tex[lSpriteName]->draw(ren->lfieldrect, x1(), y1(), box.width1(), box.height1(), lSpriteNum);
    ren->tex[rSpriteName]->draw(ren->rfieldrect, z1(), w1(), box.width2(), box.height2(), rSpriteNum);
}

namespace Action{

    void Action::chainact(){
        act();
        if (next) next->chainact();
    }

    void blockDetectAndMove::act(){
        Map * map = obj->map;
        int size = map->size;
        double dt = map->dt;

        //collision detect and moving
        if (obj->v.x < 0){ 
            for (int i = max(0, (int)floor(obj->x1() + obj->v.x * dt)); i < min((int)ceil(obj->x1()), size); ++i)
            for (int j = max(0, (int)floor(obj->y1())); j < min((int)ceil(obj->y2()), size); ++j)
            for (int k = max(0, (int)floor(obj->z1())); k < min((int)ceil(obj->z2()), size); ++k)
            for (int l = max(0, (int)floor(obj->w1())); l < min((int)ceil(obj->w2()), size); ++l)
                map->getBlockType(i, j, k, l)->collide(obj, P_xNegative, vec4int(i,j,k,l));
        }
        if (obj->v.x > 0){
            for (int i = max(0, (int)floor(obj->x2())); i < min((int)ceil(obj->x2() + obj->v.x * dt), size); ++i)
            for (int j = max(0, (int)floor(obj->y1())); j < min((int)ceil(obj->y2()), size); ++j)
            for (int k = max(0, (int)floor(obj->z1())); k < min((int)ceil(obj->z2()), size); ++k)
            for (int l = max(0, (int)floor(obj->w1())); l < min((int)ceil(obj->w2()), size); ++l)
                map->getBlockType(i, j, k, l)->collide(obj, P_xPositive, vec4int(i,j,k,l));
        }
        obj->pos.x += obj->v.x * dt;

        if (obj->v.y < 0){ 
            for (int i = max(0, (int)floor(obj->x1())); i < min((int)ceil(obj->x2()), size); ++i)
            for (int j = max(0, (int)floor(obj->y1() + obj->v.y * dt)); j < min((int)ceil(obj->y1()), size); ++j)
            for (int k = max(0, (int)floor(obj->z1())); k < min((int)ceil(obj->z2()), size); ++k)
            for (int l = max(0, (int)floor(obj->w1())); l < min((int)ceil(obj->w2()), size); ++l)
                map->getBlockType(i, j, k, l)->collide(obj, P_yNegative, vec4int(i,j,k,l));
        }
        if (obj->v.y > 0){
            for (int i = max(0, (int)floor(obj->x1())); i < min((int)ceil(obj->x2()), size); ++i)
            for (int j = max(0, (int)floor(obj->y2())); j < min((int)ceil(obj->y2() + obj->v.y * dt), size); ++j)
            for (int k = max(0, (int)floor(obj->z1())); k < min((int)ceil(obj->z2()), size); ++k)
            for (int l = max(0, (int)floor(obj->w1())); l < min((int)ceil(obj->w2()), size); ++l)
                map->getBlockType(i, j, k, l)->collide(obj, P_yPositive, vec4int(i,j,k,l));
        }
        obj->pos.y += obj->v.y * dt;
        if (obj->v.y < 0) obj->ground1 = false;

        if (obj->v.z < 0){ 
            for (int i = max(0, (int)floor(obj->x1())); i < min((int)ceil(obj->x2()), size); ++i)
            for (int j = max(0, (int)floor(obj->y1())); j < min((int)ceil(obj->y2()), size); ++j)
            for (int k = max(0, (int)floor(obj->z1() + obj->v.z * dt)); k < min((int)ceil(obj->z1()), size); ++k)
            for (int l = max(0, (int)floor(obj->w1())); l < min((int)ceil(obj->w2()), size); ++l)
                map->getBlockType(i, j, k, l)->collide(obj, P_zNegative, vec4int(i,j,k,l));
        }
        if (obj->v.z > 0){
            for (int i = max(0, (int)floor(obj->x1())); i < min((int)ceil(obj->x2()), size); ++i)
            for (int j = max(0, (int)floor(obj->y1())); j < min((int)ceil(obj->y2()), size); ++j)
            for (int k = max(0, (int)floor(obj->z2())); k < min((int)ceil(obj->z2() + obj->v.z * dt), size); ++k)
            for (int l = max(0, (int)floor(obj->w1())); l < min((int)ceil(obj->w2()), size); ++l)
                map->getBlockType(i, j, k, l)->collide(obj, P_zPositive, vec4int(i,j,k,l));
        }
        obj->pos.z += obj->v.z * dt;

        if (obj->v.w < 0){ 
            for (int i = max(0, (int)floor(obj->x1())); i < min((int)ceil(obj->x2()), size); ++i)
            for (int j = max(0, (int)floor(obj->y1())); j < min((int)ceil(obj->y2()), size); ++j)
            for (int k = max(0, (int)floor(obj->z1())); k < min((int)ceil(obj->z2()), size); ++k)
            for (int l = max(0, (int)floor(obj->w1() + obj->v.w * dt)); l < min((int)ceil(obj->w1()), size); ++l)
                map->getBlockType(i, j, k, l)->collide(obj, P_wNegative, vec4int(i,j,k,l));
        }
        if (obj->v.w > 0){
            for (int i = max(0, (int)floor(obj->x1())); i < min((int)ceil(obj->x2()), size); ++i)
            for (int j = max(0, (int)floor(obj->y1())); j < min((int)ceil(obj->y2()), size); ++j)
            for (int k = max(0, (int)floor(obj->z1())); k < min((int)ceil(obj->z2()), size); ++k)
            for (int l = max(0, (int)floor(obj->w2())); l < min((int)ceil(obj->w2() + obj->v.w * dt), size); ++l)
                map->getBlockType(i, j, k, l)->collide(obj, P_wPositive, vec4int(i,j,k,l));
        }
        obj->pos.w += obj->v.w * dt;
        if (obj->v.w < 0) obj->ground2 = false;

    }

    void overlayDetect::act(){
        Map * map = obj->map;
        int size = map->size;

        for (int i = max(0, (int)floor(obj->x1())); i < min((int)ceil(obj->x2()), size); ++i)
        for (int j = max(0, (int)floor(obj->y1())); j < min((int)ceil(obj->y2()), size); ++j)
        for (int k = max(0, (int)floor(obj->z1())); k < min((int)ceil(obj->z2()), size); ++k)
        for (int l = max(0, (int)floor(obj->w1())); l < min((int)ceil(obj->w2()), size); ++l)
            map->getBlockType(i, j, k, l)->overlay(obj, vec4int(i,j,k,l));
    }

    void boundaryDetect::act(){
        Map * map = obj->map;
        double dt = map->dt;

        // boundary detect
        if (obj->x1() + obj->v.x * dt < 0) {
            obj->v.x = 0;
            obj->x1_set(0);
        }
        if (obj->x2() + obj->v.x * dt > map->size) {
            obj->v.x = 0;
            obj->x2_set(map->size);
        }
        if (obj->y1() + obj->v.y * dt < 0) {
            obj->v.y = 0;
            obj->y1_set(0);
            obj->ground1 = true;
        }
        if (obj->y2() + obj->v.y * dt > map->size) {
            obj->v.y = 0;
            obj->y2_set(map->size);
        }

        if (obj->z1() + obj->v.z * dt < 0) {
            obj->v.z = 0;
            obj->z1_set(0);
        }
        if (obj->z2() + obj->v.z * dt > map->size) {
            obj->v.z = 0;
            obj->z2_set(map->size);
        }
        if (obj->w1() + obj->v.w * dt < 0) {
            obj->v.w = 0;
            obj->w1_set(0);
            obj->ground2 = true;
        }
        if (obj->w2() + obj->v.w * dt > map->size) {
            obj->v.w = 0;
            obj->w2_set(map->size);
        }

    }

}
