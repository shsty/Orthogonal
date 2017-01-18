#include "main.h"

const SDL_Rect MainApp::playerSpritePos[8] = {
    {0, 0, 12, 12},
    {12, 0, 12, 12},
    {24, 0, 12, 12},
    {36, 0, 12, 12},
    {0, 12, 12, 12},
    {12, 12, 12, 12},
    {24, 12, 12, 12},
    {36, 12, 12, 12}
};

const SDL_Rect MainApp::blockSpritePos[2] = {
    {0, 0, 16, 16},
    {16, 0, 16, 16}
};

const SDL_Rect MainApp::cursorSpritePos[16] = {
    {0, 0, 16, 16},
    {0, 16, 16, 16},
    {0, 32, 16, 16},
    {0, 48, 16, 16},
    {16, 0, 16, 16},
    {16, 16, 16, 16},
    {16, 32, 16, 16},
    {16, 48, 16, 16},
    {32, 0, 16, 16},
    {32, 16, 16, 16},
    {32, 32, 16, 16},
    {32, 48, 16, 16},
    {48, 0, 16, 16},
    {48, 16, 16, 16},
    {48, 32, 16, 16},
    {48, 48, 16, 16},
};

void MainApp::OnRender(){
    SDL_RenderClear(ren);

    SDL_RenderCopy(ren, bgtex, NULL, NULL);

    SDL_RenderCopy(ren, fieldtex, NULL, &lfieldrect);
    SDL_RenderCopy(ren, fieldtex, NULL, &rfieldrect);

    RenderMap();
    RenderCursor();

    RenderPlayer(lfieldrect, player.spritenum1, player.x, player.y);
    RenderPlayer(rfieldrect, player.spritenum2, player.z, player.w);

    SDL_RenderPresent(ren);
    
}

void MainApp::RenderPlayer(SDL_Rect fieldrect, int index, float x, float y){
    SDL_Rect rect;
    rect.w = fieldscale * player.width;
    rect.h = fieldscale * player.height;
    rect.x = fieldrect.x + fieldscale * x - rect.w/2;
    rect.y = fieldrect.y + fieldrect.h - fieldscale * y - rect.h;
    SDL_RenderCopy(ren, playertex, &playerSpritePos[index], &rect);
}

void MainApp::RenderMap(){
    int x = int(player.x);
    int y = int(player.y);
    int z = int(player.z);
    int w = int(player.w);
    for (int i = 0; i < map.size; ++i)
        for (int j = 0; j < map.size; ++j){
            int b = map.get(i, j, z, w);
            RenderBlock(lfieldrect, b, i, j);
        }
    for (int i = 0; i < map.size; ++i)
        for (int j = 0; j < map.size; ++j){
            int b = map.get(x, y, i, j);
            RenderBlock(rfieldrect, b, i, j);
        }
}

void MainApp::RenderBlock(const SDL_Rect & fieldrect, int index, int x, int y){
    SDL_Rect rect;
    rect.w = fieldscale;
    rect.h = fieldscale;
    rect.x = fieldrect.x + fieldscale * x;
    rect.y = fieldrect.y + fieldrect.h - fieldscale * (y+1);
    SDL_RenderCopy(ren, blocktex, &blockSpritePos[blockTypes[index].spritenum], &rect);
}

void MainApp::RenderCursor(){
    if (cursor.active1){
        for (int i = cursor.x1; i <= cursor.x2; ++i)
        for (int j = cursor.y1; j <= cursor.y2; ++j)
            RenderCursorBlock(lfieldrect, 0, i, j);
    }
    if (cursor.active2){
        for (int k = cursor.z1; k <= cursor.z2; ++k)
        for (int l = cursor.w1; l <= cursor.w2; ++l)
            RenderCursorBlock(rfieldrect, 0, k, l);
    }
}

void MainApp::RenderCursorBlock(const SDL_Rect & fieldrect, int spritenum, int x, int y){
    SDL_Rect rect;
    rect.w = fieldscale;
    rect.h = fieldscale;
    rect.x = fieldrect.x + fieldscale * x;
    rect.y = fieldrect.y + fieldrect.h - fieldscale * (y+1);
    SDL_RenderCopy(ren, cursortex, &blockSpritePos[spritenum], &rect);
}
