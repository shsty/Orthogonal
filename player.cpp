#include "player.h"
#include "map.h"
#include "renderer.h"
#include <SDL2/SDL.h>

Player::Player(){
    x = z = 0.5;
    y = w = 15;
    vx = vy = vz = vw = 0;
    boxy = 0;
    boxx = -12.0/16/2;
    height = 12.0/16;
    width = 12.0/16;
    speed = 8.0;
    spritenum1 = 0;spritenum2 = 4;

    //things about jumping
    hasgravity = true;
    jumpheight = 3.2;
    jumptime = 0.8;
    jumpdistance = 5;
    multg = 5;
    ground1 = ground2 = false;
    jumpflag1 = jumpflag2 = false;

    g = 8 * jumpheight / jumptime / jumptime;
    jumpspeed = 4 * jumpheight / jumptime;
    speed = jumpdistance / jumptime;

}

void Player::render(Renderer * ren){
    ren->playertex->draw(ren->lfieldrect, x + boxx, y + boxy, width, height, spritenum1);
    ren->playertex->draw(ren->rfieldrect, z + boxx, w + boxy, width, height, spritenum2);
}

inline int min(int a, int b){
    return (a<b)?a:b;
}

inline int max(int a, int b){
    return (a>b)?a:b;
}

void Player::move(const Uint8* keystate, Map * map, double dt){
    spritenum1 = 0;
    spritenum2 = 4;
    vx = vz = 0;
    if (!hasgravity){
        vy = vw = 0;
    }

    //player1 velocity
    if (keystate[SDL_SCANCODE_S]){
        spritenum1 = 0;
        if (!hasgravity) vy = -speed;
    }
    if (keystate[SDL_SCANCODE_D]){
        spritenum1 = 1;
        vx = speed;
    }
    if (keystate[SDL_SCANCODE_A]){
        if (keystate[SDL_SCANCODE_D]){
            spritenum1 = 0;
            vx = 0;
        } else {
            spritenum1 = 2;
            vx = -speed;
        }
    }
    if (keystate[SDL_SCANCODE_W]){
        spritenum1 = 3;
        if (hasgravity){
            vy -= g * dt;
        } else {
            vy = speed;
        }
    } else if (hasgravity){
        vy -= dt * g * ((vy<0)?1:multg);
    }
    if (hasgravity && ground1 && jumpflag1){
        vy = jumpspeed;
        ground1 = false;
        jumpflag1 = false;
    }

    //player2 velocity
    if (keystate[SDL_SCANCODE_DOWN]){
        spritenum2 = 4;
        if (!hasgravity) vw = -speed;
    }
    if (keystate[SDL_SCANCODE_RIGHT]){
        spritenum2 = 5;
        vz = speed;
    }
    if (keystate[SDL_SCANCODE_LEFT]){
        if (keystate[SDL_SCANCODE_RIGHT]){
            spritenum2 = 4;
            vz = 0;
        } else {
            spritenum2 = 6;
            vz = -speed;
        }
    }
    if (keystate[SDL_SCANCODE_UP]){
        spritenum2 = 7;
        if (hasgravity){
            vw -= g * dt;
        } else {
            vw = speed;
        }
    } else if (hasgravity){
        vw -= dt * g * ((vw<0)?1:multg);
    }
    if (hasgravity && ground2 && jumpflag2){
        vw = jumpspeed;
        ground2 = false;
        jumpflag2 = false;
    }

    // boundary detect
    if (x1() + vx * dt < 0) {
        vx = 0;
        x1_set(0);
    }
    if (x2() + vx * dt > map->size) {
        vx = 0;
        x2_set(map->size);
    }
    if (y1() + vy * dt < 0) {
        vy = 0;
        y1_set(0);
        ground1 = true;
    }
    if (y2() + vy * dt > map->size) {
        vy = 0;
        y2_set(map->size);
    }

    if (z1() + vz * dt < 0) {
        vz = 0;
        z1_set(0);
    }
    if (z2() + vz * dt > map->size) {
        vz = 0;
        z2_set(map->size);
    }
    if (w1() + vw * dt < 0) {
        vw = 0;
        w1_set(0);
        ground2 = true;
    }
    if (w2() + vw * dt > map->size) {
        vw = 0;
        w2_set(map->size);
    }

    //collision detect and moving
    if (vx < 0){ 
        for (int i = max(0, (int)floor(x1() + vx * dt)); i < min((int)ceil(x1()), map->size); ++i)
        for (int j = max(0, (int)floor(y1())); j < min((int)ceil(y2()), map->size); ++j)
        for (int k = max(0, (int)floor(z1())); k < min((int)ceil(z2()), map->size); ++k)
        for (int l = max(0, (int)floor(w1())); l < min((int)ceil(w2()), map->size); ++l)
            if (!map->blockTypes[map->get(i,j,k,l)].passable) {
                vx = 0;
                x1_set(i+1);
            };
    }
    if (vx > 0){
        for (int i = max(0, (int)floor(x2())); i < min((int)ceil(x2() + vx * dt), map->size); ++i)
        for (int j = max(0, (int)floor(y1())); j < min((int)ceil(y2()), map->size); ++j)
        for (int k = max(0, (int)floor(z1())); k < min((int)ceil(z2()), map->size); ++k)
        for (int l = max(0, (int)floor(w1())); l < min((int)ceil(w2()), map->size); ++l)
            if (!map->blockTypes[map->get(i,j,k,l)].passable) {
                vx = 0;
                x2_set(i);
            };
    }
    x += vx * dt;

    if (vy < 0){ 
        for (int i = max(0, (int)floor(x1())); i < min((int)ceil(x2()), map->size); ++i)
        for (int j = max(0, (int)floor(y1() + vy * dt)); j < min((int)ceil(y1()), map->size); ++j)
        for (int k = max(0, (int)floor(z1())); k < min((int)ceil(z2()), map->size); ++k)
        for (int l = max(0, (int)floor(w1())); l < min((int)ceil(w2()), map->size); ++l)
            if (!map->blockTypes[map->get(i,j,k,l)].passable) {
                vy = 0;
                y1_set(j+1);
                ground1 = true;
            };
    }
    if (vy > 0){
        for (int i = max(0, (int)floor(x1())); i < min((int)ceil(x2()), map->size); ++i)
        for (int j = max(0, (int)floor(y2())); j < min((int)ceil(y2() + vy * dt), map->size); ++j)
        for (int k = max(0, (int)floor(z1())); k < min((int)ceil(z2()), map->size); ++k)
        for (int l = max(0, (int)floor(w1())); l < min((int)ceil(w2()), map->size); ++l)
            if (!map->blockTypes[map->get(i,j,k,l)].passable) {
                vy = 0;
                y2_set(j);
            };
    }
    y += vy * dt;
    if (vy < 0) ground1 = false;

    if (vz < 0){ 
        for (int i = max(0, (int)floor(x1())); i < min((int)ceil(x2()), map->size); ++i)
        for (int j = max(0, (int)floor(y1())); j < min((int)ceil(y2()), map->size); ++j)
        for (int k = max(0, (int)floor(z1() + vz * dt)); k < min((int)ceil(z1()), map->size); ++k)
        for (int l = max(0, (int)floor(w1())); l < min((int)ceil(w2()), map->size); ++l)
            if (!map->blockTypes[map->get(i,j,k,l)].passable) {
                vz = 0;
                z1_set(k+1);
            };
    }
    if (vz > 0){
        for (int i = max(0, (int)floor(x1())); i < min((int)ceil(x2()), map->size); ++i)
        for (int j = max(0, (int)floor(y1())); j < min((int)ceil(y2()), map->size); ++j)
        for (int k = max(0, (int)floor(z2())); k < min((int)ceil(z2() + vz * dt), map->size); ++k)
        for (int l = max(0, (int)floor(w1())); l < min((int)ceil(w2()), map->size); ++l)
            if (!map->blockTypes[map->get(i,j,k,l)].passable) {
                vz = 0;
                z2_set(k);
            };
    }
    z += vz * dt;

    if (vw < 0){ 
        for (int i = max(0, (int)floor(x1())); i < min((int)ceil(x2()), map->size); ++i)
        for (int j = max(0, (int)floor(y1())); j < min((int)ceil(y2()), map->size); ++j)
        for (int k = max(0, (int)floor(z1())); k < min((int)ceil(z2()), map->size); ++k)
        for (int l = max(0, (int)floor(w1() + vw * dt)); l < min((int)ceil(w1()), map->size); ++l)
            if (!map->blockTypes[map->get(i,j,k,l)].passable) {
                vw = 0;
                w1_set(l+1);
                ground2 = true;
            };
    }
    if (vw > 0){
        for (int i = max(0, (int)floor(x1())); i < min((int)ceil(x2()), map->size); ++i)
        for (int j = max(0, (int)floor(y1())); j < min((int)ceil(y2()), map->size); ++j)
        for (int k = max(0, (int)floor(z1())); k < min((int)ceil(z2()), map->size); ++k)
        for (int l = max(0, (int)floor(w2())); l < min((int)ceil(w2() + vw * dt), map->size); ++l)
            if (!map->blockTypes[map->get(i,j,k,l)].passable) {
                vw = 0;
                w2_set(l);
            };
    }
    w += vw * dt;
    if (vw < 0) ground2 = false;

}
