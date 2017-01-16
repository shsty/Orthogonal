#include "player.h"
#include <SDL2/SDL.h>

Player::Player(){
    x = z = 0.5;
    y = w = 0;
    vx = vy = vz = vw = 0;
    boxy = 0;
    boxx = -12.0/16/2;
    height = 12.0/16;
    width = 12.0/16;
    speed = 8.0;
    spritenum1 = 0;spritenum2 = 4;
}
