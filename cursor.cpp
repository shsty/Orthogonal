#include "cursor.h"
#include "renderer.h"

void Cursor::render(Renderer * ren){
    if (active1){
        for (int i = x1; i <= x2; ++i)
        for (int j = y1; j <= y2; ++j)
            ren->cursortex->draw(ren->lfieldrect, i, j, 1, 1, 0);
    }
    if (active2){
        for (int k = z1; k <= z2; ++k)
        for (int l = w1; l <= w2; ++l)
            ren->cursortex->draw(ren->rfieldrect, k, l, 1, 1, 0);
    }
}
