#ifndef MAIN_H
#define MAIN_H

#include <cstdio>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include "exception.h"
#include "player.h"
#include "map.h"

class MainApp{
    private:
        static const char * WINDOW_NAME;
        static const std::string respath;
        static const SDL_Rect playerSpritePos[];
        static const SDL_Rect blockSpritePos[];
        static const SDL_Rect cursorSpritePos[];
        static const struct blocktype blockTypes[];
        int screen_width;
        int screen_height;
        int fieldscale;
        float dt;
        float g;

        enum {S_STOP, S_RUNNING} state;

        SDL_Window * window;
        SDL_Renderer * ren;
        SDL_Texture * bgtex;
        SDL_Texture * fieldtex;
        SDL_Texture * playertex;
        SDL_Texture * blocktex;
        SDL_Texture * cursortex;
        SDL_Event quitevent;

        Player player;

        std::string mapname;
        Map map;
        SDL_Rect lfieldrect, rfieldrect;
        struct Cursor cursor;

        //Main structure
        bool OnInit();
        void OnEvent(SDL_Event* event);
        void OnLoop();
        void OnRender();
        void OnCleanup();
        void OnExit();
        void OnDelay();


        //Renderer functions
        SDL_Texture * LoadTexture(const std::string & imgname);
        void RenderPlayer(SDL_Rect fieldrect, int index, float x, float y);
        void RenderMap();
        void RenderBlock(const SDL_Rect & fieldrect, int index, int x, int y);
        void RenderCursor();
        void RenderCursorBlock(const SDL_Rect & fieldrect, int spritenum, int x, int y);

        //Event handler
        void KeyDownEvent(SDL_Event * event);
        void KeyUpEvent(SDL_Event * event);
        void MouseDownEvent(SDL_Event * event);
        void MouseUpEvent(SDL_Event * event);
        void MouseMotionEvent(SDL_Event * event);
        void CursorStart(int x, int y);
        void CursorMove(int x, int y);
        void CursorEnd(int x, int y);
        enum Cursor::Cfields GetCursorField(int x, int y);
        void GetCursorCoord(int x, int y, const SDL_Rect & rect, int & u, int & v);

    public:
        MainApp();
        ~MainApp();
        int OnExecute();
};

#endif

