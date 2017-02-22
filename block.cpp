#include "block.h"
#include "object.h"
#include "renderer.h"

void BlockType::renderLeft(Renderer * ren, int x, int y, double alpha){
    ren->tex[lSpriteName]->draw(ren->lfieldrect, x, y, 1, 1, lSpriteNum, alpha);
}

void BlockType::renderRight(Renderer * ren, int x, int y, double alpha){
    ren->tex[rSpriteName]->draw(ren->rfieldrect, x, y, 1, 1, rSpriteNum, alpha);
}

void B_Solid::collide(Object * object, enum P_Dir dir, vec4int pos){
    switch (dir){
        case P_xPositive:
            object->v.x = 0;
            object->x2_set(pos.x);
            break;
        case P_xNegative:
            object->v.x = 0;
            object->x1_set(pos.x+1);
            break;
        case P_yPositive:
            object->v.y = 0;
            object->y2_set(pos.y);
            break;
        case P_yNegative:
            object->v.y = 0;
            object->y1_set(pos.y+1);
            object->ground1 = true;
            break;
        case P_zPositive:
            object->v.z = 0;
            object->z2_set(pos.z);
            break;
        case P_zNegative:
            object->v.z = 0;
            object->z1_set(pos.z+1);
            break;
        case P_wPositive:
            object->v.w = 0;
            object->w2_set(pos.w);
            break;
        case P_wNegative:
            object->v.w = 0;
            object->w1_set(pos.w+1);
            object->ground2 = true;
            break;
    }
}

Json::Value BlockType::toJson(){
    Json::Value json;
    return json;
}

void BlockType::fromJson(Json::Value json){
}

