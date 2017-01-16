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
        SDL_Event quitevent;

        Player player;

        std::string mapname;
        Map map;

        bool OnInit();
        void OnEvent(SDL_Event* event);
        void OnLoop();
        void OnRender();
        void OnCleanup();
        void OnExit();
        void OnDelay();

        SDL_Texture * LoadTexture(const std::string & imgname);

        void RenderPlayer(SDL_Rect fieldrect, int index, float x, float y);
        void RenderMap(const SDL_Rect & lfieldrect, const SDL_Rect & rfieldrect);
        void RenderBlock(const SDL_Rect & fieldrect, int index, float x, float y);

        void KeyDownEvent(SDL_Event * event);
        void KeyUpEvent(SDL_Event * event);
        void MouseDownEvent(SDL_Event * event);
        void MouseUpEvent(SDL_Event * event);
        void MouseMotionEvent(SDL_Event * event);

    public:
        MainApp();
        ~MainApp();
        int OnExecute();
};

#endif

