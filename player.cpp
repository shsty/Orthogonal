#include "player.h"
#include "map.h"
#include "renderer.h"
#include "block.h"
#include <SDL2/SDL.h>

Player::Player(){
    pos.x = pos.z = 0.5;
    pos.y = pos.w = 15;
    v.x = v.y = v.z = v.w = 0;
    box.y1 = box.w1 = 0;
    box.x1 = box.z1 = -12.0/16/2;
    box.height1_set(12.0/16);
    box.width1_set(12.0/16);
    box.height2_set(12.0/16);
    box.width2_set(12.0/16);
    
    lSpriteName = rSpriteName = "player";
    lSpriteNum = 0;rSpriteNum = 4;

    //things about jumping
    hasgravity = true;
    double jumpheight = 3.2;
    double jumptime = 0.8;
    double jumpdistance = 5;
    multg = 5;
    ground1 = ground2 = false;
    jumpflag1 = jumpflag2 = false;
    acc = 10;

    g = 8 * jumpheight / jumptime / jumptime;
    jumpspeed = 4 * jumpheight / jumptime;
    speed = jumpdistance / jumptime;

}

void Player::init(Map * map){
    pos = map->initpos;
}

inline int min(int a, int b){
    return (a<b)?a:b;
}

inline int max(int a, int b){
    return (a>b)?a:b;
}

void Player::react(const unsigned char * keystate, double dt){
    lSpriteNum = 0;
    rSpriteNum = 4;
    v.x = v.z = 0;
    if (!hasgravity){
        v.y = v.w = 0;
    }

    //player1 velocity
    if (keystate[SDL_SCANCODE_S]){
        lSpriteNum = 0;
        if (!hasgravity) v.y = -speed;
    }
    if (keystate[SDL_SCANCODE_D]){
        lSpriteNum = 1;
        v.x = speed;
    }
    if (keystate[SDL_SCANCODE_A]){
        if (keystate[SDL_SCANCODE_D]){
            lSpriteNum = 0;
            v.x = 0;
        } else {
            lSpriteNum = 2;
            v.x = -speed;
        }
    }
    if (keystate[SDL_SCANCODE_W]){
        lSpriteNum = 3;
        if (hasgravity){
            v.y -= g * dt;
        } else {
            v.y = speed;
        }
    } else if (hasgravity){
        v.y -= dt * g * ((v.y<0)?1:multg);
    }
    if (hasgravity && ground1 && jumpflag1){
        v.y = jumpspeed;
        ground1 = false;
        jumpflag1 = false;
    }

    //player2 velocity
    if (keystate[SDL_SCANCODE_DOWN]){
        rSpriteNum = 4;
        if (!hasgravity) v.w = -speed;
    }
    if (keystate[SDL_SCANCODE_RIGHT]){
        rSpriteNum = 5;
        v.z = speed;
    }
    if (keystate[SDL_SCANCODE_LEFT]){
        if (keystate[SDL_SCANCODE_RIGHT]){
            rSpriteNum = 4;
            v.z = 0;
        } else {
            rSpriteNum = 6;
            v.z = -speed;
        }
    }
    if (keystate[SDL_SCANCODE_UP]){
        rSpriteNum = 7;
        if (hasgravity){
            v.w -= g * dt;
        } else {
            v.w = speed;
        }
    } else if (hasgravity){
        v.w -= dt * g * ((v.w<0)?1:multg);
    }
    if (hasgravity && ground2 && jumpflag2){
        v.w = jumpspeed;
        ground2 = false;
        jumpflag2 = false;
    }

}
