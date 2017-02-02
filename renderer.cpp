#include "renderer.h"
#include "exception.h"

const char * Renderer::WINDOW_NAME = "Orthogonal";
std::string Renderer::respath  = "sketch/";

Renderer * Texture::renderer = nullptr;

const SDL_Rect Renderer::blockSpritePos[16] = {
    {0, 0, 16, 16},
    {16, 0, 16, 16},
    {32, 0, 16, 16},
    {48, 0, 16, 16},
    {0, 16, 16, 16},
    {16, 16, 16, 16},
    {32, 16, 16, 16},
    {48, 16, 16, 16},
    {0, 32, 16, 16},
    {16, 32, 16, 16},
    {32, 32, 16, 16},
    {48, 32, 16, 16},
    {0, 48, 16, 16},
    {16, 48, 16, 16},
    {32, 48, 16, 16},
    {48, 48, 16, 16},
};

const SDL_Rect Renderer::playerSpritePos[8] = {
    {0, 0, 12, 12},
    {12, 0, 12, 12},
    {24, 0, 12, 12},
    {36, 0, 12, 12},
    {0, 12, 12, 12},
    {12, 12, 12, 12},
    {24, 12, 12, 12},
    {36, 12, 12, 12}
};

const SDL_Rect Renderer::cursorSpritePos[16] = {
    {0, 0, 16, 16},
    {48, 0, 16, 16},
    {16, 0, 16, 16},
    {32, 0, 16, 16},
    {0, 16, 16, 16},
    {48, 16, 16, 16},
    {16, 16, 16, 16},
    {32, 16, 16, 16},
    {0, 48, 16, 16},
    {48, 48, 16, 16},
    {16, 48, 16, 16},
    {32, 48, 16, 16},
    {0, 32, 16, 16},
    {48, 32, 16, 16},
    {16, 32, 16, 16},
    {32, 32, 16, 16},
};

Renderer::Renderer(int _mapSize){
    mapSize = _mapSize;
    fieldscale = 48;
    screen_width = (2 * mapSize + 2.25) * fieldscale;
    screen_height = (mapSize + 1.5) * fieldscale;

    window = nullptr;
    ren = nullptr;
    
    bgtex = nullptr;
    fieldtex = nullptr;
    playertex = nullptr;
    blocktex = nullptr;
    cursortex = nullptr;

    SDL_version sdlversion;
    SDL_GetVersion(&sdlversion);

    //initializing SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) throw SDL_Exception();

    int imgflags = IMG_INIT_PNG;
    if (IMG_Init(imgflags) & imgflags != imgflags) throw IMG_Exception();

    SDL_Log("SDL Version %d.%d.%d", sdlversion.major, sdlversion.minor, sdlversion.patch);

    const SDL_version * img_version = IMG_Linked_Version();

    SDL_Log("SDL_Image Version %d.%d.%d", img_version->major, img_version->minor, img_version->patch);

    //Creating window
    window = SDL_CreateWindow(
            WINDOW_NAME,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            screen_width,
            screen_height,
            SDL_WINDOW_SHOWN
    );
    if (window == nullptr) throw SDL_Exception();

    //Creating renderer
    ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) throw SDL_Exception();

    Texture::renderer = this;

    //loading images
    bgtex = new Texture(respath + "background2.png");
    fieldtex = new Texture(respath + "field2.png");
    playertex = new Texture(respath + "player.png", playerSpritePos, (sizeof playerSpritePos) / (sizeof *playerSpritePos));
    blocktex = new Texture(respath + "blocks.png", blockSpritePos, (sizeof blockSpritePos) / (sizeof *blockSpritePos));
    cursortex = new Texture(respath + "cursor.png", cursorSpritePos, (sizeof cursorSpritePos) / (sizeof *cursorSpritePos));
    
    //setting up fields
    int fw = fieldscale * mapSize;
    int fh = fieldscale * mapSize;
    lfieldrect.w = rfieldrect.w = fw;
    lfieldrect.h = rfieldrect.h = fh;
    lfieldrect.x = (screen_width - 2*fw)/3;
    lfieldrect.y = (screen_height - fh)/2;
    rfieldrect.x = lfieldrect.x*2 + fw;
    rfieldrect.y = lfieldrect.y;
}

Renderer::~Renderer(){
    if (bgtex) delete bgtex;
    if (fieldtex) delete fieldtex;
    if (playertex) delete playertex;
    if (blocktex) delete blocktex;
    if (cursortex) delete cursortex;
    Texture::renderer = nullptr;
    if (ren) SDL_DestroyRenderer(ren);
    if (window) SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

void Renderer::clear(){
    SDL_RenderClear(ren);
}

void Renderer::present(){
    SDL_RenderPresent(ren);
}

enum Cfields Renderer::GetCursorField(int x, int y){
    if ((lfieldrect.x <= x) && (x <= lfieldrect.x + lfieldrect.w) && (lfieldrect.y <= y) && (y <= lfieldrect.y + lfieldrect.h)) return C_Field1;
    if ((rfieldrect.x <= x) && (x <= rfieldrect.x + rfieldrect.w) && (rfieldrect.y <= y) && (y <= rfieldrect.y + rfieldrect.h)) return C_Field2;
    return C_None;
}

void Renderer::GetCursorCoord(int x, int y, const SDL_Rect & rect, int & u, int & v){
    u = (x - rect.x)/fieldscale;
    v = (rect.y + rect.h - y)/fieldscale;
    if (u < 0) u = 0;
    if (v < 0) v = 0;
    if (u >= mapSize) u = mapSize - 1;
    if (v >= mapSize) v = mapSize - 1;
}

Texture::Texture(const std::string & texfile, const SDL_Rect * _spriteRects, int _spriteCount, SDL_BlendMode blendMode){
    spriteRects = _spriteRects;
    spriteCount = _spriteCount;

    //Loading resources
    std::string imgpath = texfile;
    SDL_Surface *img = IMG_Load(texfile.c_str());
    if (img == nullptr) throw IMG_Exception();

    //convert surface to texture
    tex = SDL_CreateTextureFromSurface(renderer->ren, img);
    SDL_FreeSurface(img);
    if (tex == nullptr) throw SDL_Exception();

    //setting blend mode
    if (SDL_SetTextureBlendMode(tex, blendMode)) throw SDL_Exception();
}

Texture::~Texture(){
    if (tex) SDL_DestroyTexture(tex);
}

void Texture::draw(const SDL_Rect & rect, double x, double y, double w, double h, int index, double alpha){
    int a = (int)(alpha * 256);
    if (a < 0) a = 0;
    if (a > 255) a = 255;
    if (SDL_SetTextureAlphaMod(tex, a)) throw SDL_Exception();

    const SDL_Rect * srect;
    if (spriteRects) {
        if ((index < 0 || index >= spriteCount)) throw std::runtime_error("Error: Sprite number out of bound!");
        srect = &spriteRects[index];
    } else srect = nullptr;

    SDL_Rect drect;
    drect.x = rect.x + renderer->fieldscale * x;
    drect.y = rect.y + rect.h - renderer->fieldscale * (y + h);
    drect.w = renderer->fieldscale * w;
    drect.h = renderer->fieldscale * h;
    SDL_RenderCopy(renderer->ren, tex, srect, &drect);
}

void Texture::draw(const SDL_Rect * drect, int index){
    const SDL_Rect * srect;
    if (spriteRects) {
        if ((index < 0 || index >= spriteCount)) throw std::runtime_error("Error: Sprite number out of bound!");
        srect = &spriteRects[index];
    } else srect = nullptr;
    SDL_RenderCopy(renderer->ren, tex, srect, drect);
}

