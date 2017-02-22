#include "main.h"
#include "map.h"
#include "player.h"
#include "cursor.h"
#include "renderer.h"

void MainApp::OnEvent(SDL_Event* event){
    switch (event->type){
        case SDL_QUIT:
            SDL_Log("Quit Event at timestamp %d", event->quit.timestamp);
            state = S_STOP;
            break;
        case SDL_KEYDOWN:
            KeyDownEvent(event);
            break;
        case SDL_KEYUP:
            KeyUpEvent(event);
            break;
        case SDL_MOUSEBUTTONDOWN:
            MouseDownEvent(event);
            break;
        case SDL_MOUSEBUTTONUP:
            MouseUpEvent(event);
            break;
        case SDL_MOUSEMOTION:
            MouseMotionEvent(event);
            break;
        //default:
        //    SDL_Log("Event %d", event->type);
    }
}

void MainApp::KeyDownEvent(SDL_Event * event){
    switch (event->key.keysym.scancode){
        case SDL_SCANCODE_ESCAPE:
            quitevent.type = SDL_QUIT;
            quitevent.quit.timestamp = event->key.timestamp;
            SDL_PushEvent(&quitevent);
            break;
        case SDL_SCANCODE_S:
            if (event->key.keysym.mod & KMOD_CTRL)
                map->save(mapname);
            break;
        case SDL_SCANCODE_W:
            if (!event->key.repeat && player->hasgravity) player->jumpflag1 = true;
            break;
        case SDL_SCANCODE_UP:
            if (!event->key.repeat && player->hasgravity) player->jumpflag2 = true;
            break;
        case SDL_SCANCODE_G:
            player->hasgravity = !player->hasgravity;
            player->ground1 = player->ground2 = false;
            break;
        case SDL_SCANCODE_1:
        case SDL_SCANCODE_2:
        case SDL_SCANCODE_3:
        case SDL_SCANCODE_4:
        case SDL_SCANCODE_5:
        case SDL_SCANCODE_6:
        case SDL_SCANCODE_7:
        case SDL_SCANCODE_8:
        case SDL_SCANCODE_9:
        case SDL_SCANCODE_0:
            if (cursor->active1 && cursor->active2) map->fill(event->key.keysym.scancode - SDL_SCANCODE_1, cursor->x1, cursor->x2, cursor->y1, cursor->y2, cursor->z1, cursor->z2, cursor->w1, cursor->w2);
            break;
    }
}

void MainApp::KeyUpEvent(SDL_Event * event){
    switch (event->key.keysym.scancode){
        case SDL_SCANCODE_W:
            if (player->hasgravity) player->jumpflag1 = false;
            break;
        case SDL_SCANCODE_UP:
            if (player->hasgravity) player->jumpflag2 = false;
            break;
    }
}

void MainApp::MouseDownEvent(SDL_Event * event){
    switch (event->button.button){
        case SDL_BUTTON_LEFT:
            cursor->CursorStart(event->button.x, event->button.y, renderer);
            break;
        case SDL_BUTTON_RIGHT:
            cursor->active1 = false;
            cursor->active2 = false;
            break;
    }
}

void MainApp::MouseUpEvent(SDL_Event * event){
    switch (event->button.button){
        case SDL_BUTTON_LEFT:
            cursor->CursorEnd(event->button.x, event->button.y, renderer);
            break;
    }
}

void MainApp::MouseMotionEvent(SDL_Event * event){
    if (event->motion.state & SDL_BUTTON_LMASK){
        cursor->CursorMove(event->motion.x, event->motion.y, renderer);
    }
}
