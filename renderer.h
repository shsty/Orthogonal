#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Renderer;

class Texture{
public:
    static Renderer * renderer;

    SDL_Texture * tex;
    const SDL_Rect * spriteRects;
    int spriteCount;

    Texture(const std::string & texfile, const SDL_Rect * _spriteRects = nullptr, int _spriteCount = 0);
    ~Texture();

    void draw(const SDL_Rect * drect, int index = 0);
    void draw(const SDL_Rect & rect, double x, double y, double w, double h, int index = 0);
};

class Renderer{
public:
    SDL_Window * window;
    SDL_Renderer * ren;
    Texture * bgtex;
    Texture * fieldtex;
    Texture * playertex;
    Texture * blocktex;
    Texture * cursortex;

    static const SDL_Rect blockSpritePos[];
    static const SDL_Rect playerSpritePos[];
    static const SDL_Rect cursorSpritePos[];

    SDL_Rect lfieldrect, rfieldrect;

    static const char * WINDOW_NAME;
    static std::string respath;
    int screen_width;
    int screen_height;
    int fieldscale;

    Renderer(int mapSize);
    ~Renderer();

    void clear();
    void render();
    void present();
};

#endif
