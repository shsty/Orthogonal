#include "player.h"
#include "map.h"
#include "renderer.h"
#include "block.h"
#include "exception.h"
#include <SDL2/SDL.h>

Player::Player(Map * _map):Object(_map){
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
    double jumptime = 1.2;
    double jumpdistance = 5;
    multg = 5;
    ground1 = ground2 = false;
    jumpflag1 = jumpflag2 = false;
    acc = 10;

    g = 8 * jumpheight / jumptime / jumptime;
    jumpspeed = 4 * jumpheight / jumptime;
    speed = jumpdistance / jumptime;

    addAction(new Action::keyboardAction);
}

void Player::init(Map * _map){
    map = _map;
    if (map->fixEntrance) pos = map->initpos;
}

inline int min(int a, int b){
    return (a<b)?a:b;
}

inline int max(int a, int b){
    return (a>b)?a:b;
}

namespace Action{

    void keyboardAction::act(){
        Player * player = dynamic_cast<Player *> (obj);
        if (player == nullptr) throw std::runtime_error("Uncompactable object type for the action");

        double dt = player->map->dt;
        const Uint8 * keystate = SDL_GetKeyboardState(NULL);

        player->lSpriteNum = 0;
        player->rSpriteNum = 4;
        player->v.x = player->v.z = 0;
        if (!player->hasgravity){
            player->v.y = player->v.w = 0;
        }

        //player1 velocity
        if (keystate[SDL_SCANCODE_S]){
            player->lSpriteNum = 0;
            if (!player->hasgravity) player->v.y = -player->speed;
        }
        if (keystate[SDL_SCANCODE_D]){
            player->lSpriteNum = 1;
            player->v.x = player->speed;
        }
        if (keystate[SDL_SCANCODE_A]){
            if (keystate[SDL_SCANCODE_D]){
                player->lSpriteNum = 0;
                player->v.x = 0;
            } else {
                player->lSpriteNum = 2;
                player->v.x = -player->speed;
            }
        }
        if (keystate[SDL_SCANCODE_W]){
            player->lSpriteNum = 3;
            if (player->hasgravity){
                player->v.y -= player->g * dt;
            } else {
                player->v.y = player->speed;
            }
        } else if (player->hasgravity){
            player->v.y -= dt * player->g * ((player->v.y<0)?1:player->multg);
        }
        if (player->hasgravity && player->ground1 && player->jumpflag1){
            player->v.y = player->jumpspeed;
            player->ground1 = false;
            player->jumpflag1 = false;
        }

        //player2 velocity
        if (keystate[SDL_SCANCODE_DOWN]){
            player->rSpriteNum = 4;
            if (!player->hasgravity) player->v.w = -player->speed;
        }
        if (keystate[SDL_SCANCODE_RIGHT]){
            player->rSpriteNum = 5;
            player->v.z = player->speed;
        }
        if (keystate[SDL_SCANCODE_LEFT]){
            if (keystate[SDL_SCANCODE_RIGHT]){
                player->rSpriteNum = 4;
                player->v.z = 0;
            } else {
                player->rSpriteNum = 6;
                player->v.z = -player->speed;
            }
        }
        if (keystate[SDL_SCANCODE_UP]){
            player->rSpriteNum = 7;
            if (player->hasgravity){
                player->v.w -= player->g * dt;
            } else {
                player->v.w = player->speed;
            }
        } else if (player->hasgravity){
            player->v.w -= dt * player->g * ((player->v.w<0)?1:player->multg);
        }
        if (player->hasgravity && player->ground2 && player->jumpflag2){
            player->v.w = player->jumpspeed;
            player->ground2 = false;
            player->jumpflag2 = false;
        }

    }

}
