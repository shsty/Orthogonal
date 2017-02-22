#ifndef MAIN_H
#define MAIN_H

#include <cstdio>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include "exception.h"
#include "cursor.h"
#include "declaration.h"

class MainApp{
public:
    static const int mapSize;
    double dt;
    double g;

    SDL_Event quitevent;
    enum {S_STOP, S_RUNNING} state;

    Renderer * renderer;
    Player * player;
    Map * map;
    Cursor * cursor;

    std::string mapname;

    //Main structure
    bool OnInit();
    void OnEvent(SDL_Event* event);
    void OnLoop();
    void OnRender();
    void OnCleanup();
    void OnExit();
    void OnDelay();

    //Event handler
    void KeyDownEvent(SDL_Event * event);
    void KeyUpEvent(SDL_Event * event);
    void MouseDownEvent(SDL_Event * event);
    void MouseUpEvent(SDL_Event * event);
    void MouseMotionEvent(SDL_Event * event);
    void CursorStart(int x, int y);
    void CursorMove(int x, int y);
    void CursorEnd(int x, int y);
    enum Cfields GetCursorField(int x, int y);
    void GetCursorCoord(int x, int y, const SDL_Rect & rect, int & u, int & v);

    MainApp();
    ~MainApp();
    int OnExecute();
};

#endif

