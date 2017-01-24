#include <cmath>
#include "main.h"

const struct blocktype MainApp::blockTypes[2] = {
    {1, 0},
    {0, 1}
};
/*
inline float min(float a, float b){
    return (a<b)?a:b;
}

inline float max(float a, float b){
    return (a>b)?a:b;
}
*/
inline int min(int a, int b){
    return (a<b)?a:b;
}

inline int max(int a, int b){
    return (a>b)?a:b;
}

void MainApp::OnLoop(){
    const Uint8* keystate = SDL_GetKeyboardState(NULL);

    player.spritenum1 = 0;
    player.spritenum2 = 4;
    player.vx = player.vz = 0;
    if (!player.hasgravity){
        player.vy = player.vw = 0;
    }

    //player1 velocity
    if (keystate[SDL_SCANCODE_S]){
        player.spritenum1 = 0;
        if (!player.hasgravity) player.vy = -player.speed;
    }
    if (keystate[SDL_SCANCODE_D]){
        player.spritenum1 = 1;
        player.vx = player.speed;
    }
    if (keystate[SDL_SCANCODE_A]){
        if (keystate[SDL_SCANCODE_D]){
            player.spritenum1 = 0;
            player.vx = 0;
        } else {
            player.spritenum1 = 2;
            player.vx = -player.speed;
        }
    }
    if (keystate[SDL_SCANCODE_W]){
        player.spritenum1 = 3;
        if (player.hasgravity){
            player.vy -= player.g * dt;
        } else {
            player.vy = player.speed;
        }
    } else if (player.hasgravity){
        player.vy -= dt * player.g * ((player.vy<0)?1:player.multg);
    }
    if (player.hasgravity && player.ground1 && player.jumpflag1){
        player.vy = player.jumpspeed;
        player.ground1 = false;
        player.jumpflag1 = false;
    }

    //player2 velocity
    if (keystate[SDL_SCANCODE_DOWN]){
        player.spritenum2 = 4;
        if (!player.hasgravity) player.vw = -player.speed;
    }
    if (keystate[SDL_SCANCODE_RIGHT]){
        player.spritenum2 = 5;
        player.vz = player.speed;
    }
    if (keystate[SDL_SCANCODE_LEFT]){
        if (keystate[SDL_SCANCODE_RIGHT]){
            player.spritenum2 = 4;
            player.vz = 0;
        } else {
            player.spritenum2 = 6;
            player.vz = -player.speed;
        }
    }
    if (keystate[SDL_SCANCODE_UP]){
        player.spritenum2 = 7;
        if (player.hasgravity){
            player.vw -= player.g * dt;
        } else {
            player.vw = player.speed;
        }
    } else if (player.hasgravity){
        player.vw -= dt * player.g * ((player.vw<0)?1:player.multg);
    }
    if (player.hasgravity && player.ground2 && player.jumpflag2){
        player.vw = player.jumpspeed;
        player.ground2 = false;
        player.jumpflag2 = false;
    }

    // boundary detect
    if (player.x1() + player.vx * dt < 0) {
        player.vx = 0;
        player.x1_set(0);
    }
    if (player.x2() + player.vx * dt > map.size) {
        player.vx = 0;
        player.x2_set(map.size);
    }
    if (player.y1() + player.vy * dt < 0) {
        player.vy = 0;
        player.y1_set(0);
        player.ground1 = true;
    }
    if (player.y2() + player.vy * dt > map.size) {
        player.vy = 0;
        player.y2_set(map.size);
    }

    if (player.z1() + player.vz * dt < 0) {
        player.vz = 0;
        player.z1_set(0);
    }
    if (player.z2() + player.vz * dt > map.size) {
        player.vz = 0;
        player.z2_set(map.size);
    }
    if (player.w1() + player.vw * dt < 0) {
        player.vw = 0;
        player.w1_set(0);
        player.ground2 = true;
    }
    if (player.w2() + player.vw * dt > map.size) {
        player.vw = 0;
        player.w2_set(map.size);
    }

    //collision detect and moving
    if (player.vx < 0){ 
        for (int i = max(0, 1 + floor(player.x1() + player.vx * dt - 1)); i <= min(-1 + ceil(player.x1()), map.size-1); ++i)
        for (int j = max(0, 1 + floor(player.y1() - 1)); j <= min(-1 + ceil(player.y2()), map.size-1); ++j)
        for (int k = max(0, 1 + floor(player.z1() - 1)); k <= min(-1 + ceil(player.z2()), map.size-1); ++k)
        for (int l = max(0, 1 + floor(player.w1() - 1)); l <= min(-1 + ceil(player.w2()), map.size-1); ++l)
            if (!blockTypes[map.get(i,j,k,l)].passable) {
                player.vx = 0;
                player.x1_set(i+1);
            };
    }
    if (player.vx > 0){
        for (int i = max(0, 1 + floor(player.x2() - 1)); i <= min(-1 + ceil(player.x2() + player.vx * dt), map.size-1); ++i)
        for (int j = max(0, 1 + floor(player.y1() - 1)); j <= min(-1 + ceil(player.y2()), map.size-1); ++j)
        for (int k = max(0, 1 + floor(player.z1() - 1)); k <= min(-1 + ceil(player.z2()), map.size-1); ++k)
        for (int l = max(0, 1 + floor(player.w1() - 1)); l <= min(-1 + ceil(player.w2()), map.size-1); ++l)
            if (!blockTypes[map.get(i,j,k,l)].passable) {
                player.vx = 0;
                player.x2_set(i);
            };
    }
    player.x += player.vx * dt;

    if (player.vy < 0){ 
        for (int i = max(0, 1 + floor(player.x1() - 1)); i <= min(-1 + ceil(player.x2()), map.size-1); ++i)
        for (int j = max(0, 1 + floor(player.y1() + player.vy * dt - 1)); j <= min(-1 + ceil(player.y1()), map.size-1); ++j)
        for (int k = max(0, 1 + floor(player.z1() - 1)); k <= min(-1 + ceil(player.z2()), map.size-1); ++k)
        for (int l = max(0, 1 + floor(player.w1() - 1)); l <= min(-1 + ceil(player.w2()), map.size-1); ++l)
            if (!blockTypes[map.get(i,j,k,l)].passable) {
                player.vy = 0;
                player.y1_set(j+1);
                player.ground1 = true;
            };
    }
    if (player.vy > 0){
        for (int i = max(0, 1 + floor(player.x1() - 1)); i <= min(-1 + ceil(player.x2()), map.size-1); ++i)
        for (int j = max(0, 1 + floor(player.y2() - 1)); j <= min(-1 + ceil(player.y2() + player.vy * dt), map.size-1); ++j)
        for (int k = max(0, 1 + floor(player.z1() - 1)); k <= min(-1 + ceil(player.z2()), map.size-1); ++k)
        for (int l = max(0, 1 + floor(player.w1() - 1)); l <= min(-1 + ceil(player.w2()), map.size-1); ++l)
            if (!blockTypes[map.get(i,j,k,l)].passable) {
                player.vy = 0;
                player.y2_set(j);
            };
    }
    player.y += player.vy * dt;
    if (player.vy < 0) player.ground1 = false;

    if (player.vz < 0){ 
        for (int i = max(0, 1 + floor(player.x1() - 1)); i <= min(-1 + ceil(player.x2()), map.size-1); ++i)
        for (int j = max(0, 1 + floor(player.y1() - 1)); j <= min(-1 + ceil(player.y2()), map.size-1); ++j)
        for (int k = max(0, 1 + floor(player.z1() + player.vz * dt - 1)); k <= min(-1 + ceil(player.z1()), map.size-1); ++k)
        for (int l = max(0, 1 + floor(player.w1() - 1)); l <= min(-1 + ceil(player.w2()), map.size-1); ++l)
            if (!blockTypes[map.get(i,j,k,l)].passable) {
                player.vz = 0;
                player.z1_set(k+1);
            };
    }
    if (player.vz > 0){
        for (int i = max(0, 1 + floor(player.x1() - 1)); i <= min(-1 + ceil(player.x2()), map.size-1); ++i)
        for (int j = max(0, 1 + floor(player.y1() - 1)); j <= min(-1 + ceil(player.y2()), map.size-1); ++j)
        for (int k = max(0, 1 + floor(player.z2() - 1)); k <= min(-1 + ceil(player.z2() + player.vz * dt), map.size-1); ++k)
        for (int l = max(0, 1 + floor(player.w1() - 1)); l <= min(-1 + ceil(player.w2()), map.size-1); ++l)
            if (!blockTypes[map.get(i,j,k,l)].passable) {
                player.vz = 0;
                player.z2_set(k);
            };
    }
    player.z += player.vz * dt;

    if (player.vw < 0){ 
        for (int i = max(0, 1 + floor(player.x1() - 1)); i <= min(-1 + ceil(player.x2()), map.size-1); ++i)
        for (int j = max(0, 1 + floor(player.y1() - 1)); j <= min(-1 + ceil(player.y2()), map.size-1); ++j)
        for (int k = max(0, 1 + floor(player.z1() - 1)); k <= min(-1 + ceil(player.z2()), map.size-1); ++k)
        for (int l = max(0, 1 + floor(player.w1() + player.vw * dt - 1)); l <= min(-1 + ceil(player.w1()), map.size-1); ++l)
            if (!blockTypes[map.get(i,j,k,l)].passable) {
                player.vw = 0;
                player.w1_set(l+1);
                player.ground2 = true;
            };
    }
    if (player.vw > 0){
        for (int i = max(0, 1 + floor(player.x1() - 1)); i <= min(-1 + ceil(player.x2()), map.size-1); ++i)
        for (int j = max(0, 1 + floor(player.y1() - 1)); j <= min(-1 + ceil(player.y2()), map.size-1); ++j)
        for (int k = max(0, 1 + floor(player.z1() - 1)); k <= min(-1 + ceil(player.z2()), map.size-1); ++k)
        for (int l = max(0, 1 + floor(player.w2() - 1)); l <= min(-1 + ceil(player.w2() + player.vw * dt), map.size-1); ++l)
            if (!blockTypes[map.get(i,j,k,l)].passable) {
                player.vw = 0;
                player.w2_set(l);
            };
    }
    player.w += player.vw * dt;
    if (player.vw < 0) player.ground2 = false;

}

