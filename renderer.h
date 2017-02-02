#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Renderer;
#ifndef CFIELDS
#define CFIELDS
enum Cfields {C_None, C_Field1, C_Field2};
#endif

class Texture{
public:
    static Renderer * renderer;

    SDL_Texture * tex;
    const SDL_Rect * spriteRects;
    int spriteCount;

    Texture(const std::string & texfile, const SDL_Rect * _spriteRects = nullptr, int _spriteCount = 0, SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND);
    ~Texture();

    void draw(const SDL_Rect * drect, int index = 0);
    void draw(const SDL_Rect & rect, double x, double y, double w, double h, int index = 0, double alpha = 1.0);
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
    int mapSize;

    Renderer(int _mapSize);
    ~Renderer();

    void clear();
    void render();
    void present();

    enum Cfields GetCursorField(int x, int y);
    void GetCursorCoord(int x, int y, const SDL_Rect & rect, int & u, int & v);
};

#endif
