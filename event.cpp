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
            if (event->key.keysym.mod & KMOD_CTRL){
                map.save(mapname);
                SDL_Log("map saved to %s" ,mapname.c_str());
            }
            break;
        case SDL_SCANCODE_W:
            if (!event->key.repeat && player.hasgravity) player.jumpflag1 = true;
            break;
        case SDL_SCANCODE_UP:
            if (!event->key.repeat && player.hasgravity) player.jumpflag2 = true;
            break;
        case SDL_SCANCODE_G:
            player.hasgravity = !player.hasgravity;
            player.ground1 = player.ground2 = false;
            break;
        case SDL_SCANCODE_1:
            if (cursor.active1 && cursor.active2) map.fill(0, cursor.x1, cursor.x2, cursor.y1, cursor.y2, cursor.z1, cursor.z2, cursor.w1, cursor.w2);
            break;
        case SDL_SCANCODE_2:
            if (cursor.active1 && cursor.active2) map.fill(1, cursor.x1, cursor.x2, cursor.y1, cursor.y2, cursor.z1, cursor.z2, cursor.w1, cursor.w2);
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
            CursorStart(event->button.x, event->button.y);
            break;
        case SDL_BUTTON_RIGHT:
            cursor.active1 = false;
            cursor.active2 = false;
            break;
    }
}

void MainApp::MouseUpEvent(SDL_Event * event){
    switch (event->button.button){
        case SDL_BUTTON_LEFT:
            CursorEnd(event->button.x, event->button.y);
            break;
    }
}

void MainApp::MouseMotionEvent(SDL_Event * event){
    if (event->motion.state & SDL_BUTTON_LMASK){
        CursorMove(event->motion.x, event->motion.y);
    }
}

void MainApp::CursorStart(int x, int y){
    cursor.focus = GetCursorField(x, y);
    switch (cursor.focus){
        case Cursor::C_Field1:
            cursor.active1 = true;
            GetCursorCoord(x, y, lfieldrect, cursor.xprev, cursor.yprev);
            cursor.x1 = cursor.x2 = cursor.xprev;
            cursor.y1 = cursor.y2 = cursor.yprev;
            break;
        case Cursor::C_Field2:
            cursor.active2 = true;
            GetCursorCoord(x, y, rfieldrect, cursor.zprev, cursor.wprev);
            cursor.z1 = cursor.z2 = cursor.zprev;
            cursor.w1 = cursor.w2 = cursor.wprev;
            break;
    }
}

void MainApp::CursorMove(int x, int y){
    int xcur, ycur;
    switch (cursor.focus){
        case Cursor::C_Field1:
            GetCursorCoord(x, y, lfieldrect, xcur, ycur);
            cursor.x1 = (xcur<cursor.xprev)?xcur:cursor.xprev;
            cursor.x2 = (xcur<cursor.xprev)?cursor.xprev:xcur;
            cursor.y1 = (ycur<cursor.yprev)?ycur:cursor.yprev;
            cursor.y2 = (ycur<cursor.yprev)?cursor.yprev:ycur;
            break;
        case Cursor::C_Field2:
            GetCursorCoord(x, y, rfieldrect, xcur, ycur);
            cursor.z1 = (xcur<cursor.zprev)?xcur:cursor.zprev;
            cursor.z2 = (xcur<cursor.zprev)?cursor.zprev:xcur;
            cursor.w1 = (ycur<cursor.wprev)?ycur:cursor.wprev;
            cursor.w2 = (ycur<cursor.wprev)?cursor.wprev:ycur;
            break;
    }
}

void MainApp::CursorEnd(int x, int y){
    CursorMove(x, y);
    cursor.focus = Cursor::C_None;
}

enum Cursor::Cfields MainApp::GetCursorField(int x, int y){
    if ((lfieldrect.x <= x) && (x <= lfieldrect.x + lfieldrect.w) && (lfieldrect.y <= y) && (y <= lfieldrect.y + lfieldrect.h)) return Cursor::C_Field1;
    if ((rfieldrect.x <= x) && (x <= rfieldrect.x + rfieldrect.w) && (rfieldrect.y <= y) && (y <= rfieldrect.y + rfieldrect.h)) return Cursor::C_Field2;
    return Cursor::C_None;
}

void MainApp::GetCursorCoord(int x, int y, const SDL_Rect & rect, int & u, int & v){
    u = (x - rect.x)/fieldscale;
    v = (rect.y + rect.h - y)/fieldscale;
    if (u < 0) u = 0;
    if (v < 0) v = 0;
    if (u >= map.size) u = map.size - 1;
    if (v >= map.size) v = map.size - 1;
}
