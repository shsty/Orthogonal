#include "main.h"

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
            if (event->key.keysym.mod & KMOD_CTRL){
                map.save(mapname);
                SDL_Log("map saved to %s" ,mapname.c_str());
            }
            break;
        case SDL_SCANCODE_W:
            if (player.hasgravity) player.jumpflag1 = true;
            break;
        case SDL_SCANCODE_UP:
            if (player.hasgravity) player.jumpflag2 = true;
            break;
    }
}

void MainApp::KeyUpEvent(SDL_Event * event){
    switch (event->key.keysym.scancode){
        case SDL_SCANCODE_W:
            if (player.hasgravity) player.jumpflag1 = false;
            break;
        case SDL_SCANCODE_UP:
            if (player.hasgravity) player.jumpflag2 = false;
            break;
    }
}

void MainApp::MouseDownEvent(SDL_Event * event){
    switch (event->button.button){
        case SDL_BUTTON_LEFT:
            break;
    }
}

void MainApp::MouseMotionEvent(SDL_Event * event){
}

