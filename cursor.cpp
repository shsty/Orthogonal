#include "cursor.h"
#include "renderer.h"

void Cursor::render(Renderer * ren){
    if (active1){
        for (int i = x1; i <= x2; ++i)
        for (int j = y1; j <= y2; ++j){
            int index = 0;
            if (i != x1) index += 1;
            if (i != x2) index += 2;
            if (j != y1) index += 4;
            if (j != y2) index += 8;
            ren->cursortex->draw(ren->lfieldrect, i, j, 1, 1, index);
        }
    }
    if (active2){
        for (int k = z1; k <= z2; ++k)
        for (int l = w1; l <= w2; ++l){
            int index = 0;
            if (k != z1) index += 1;
            if (k != z2) index += 2;
            if (l != w1) index += 4;
            if (l != w2) index += 8;
            ren->cursortex->draw(ren->rfieldrect, k, l, 1, 1, index);
        }
    }
}

void Cursor::CursorStart(int x, int y, Renderer * renderer){
    focus = renderer->GetCursorField(x, y);
    switch (focus){
        case C_Field1:
            active1 = true;
            renderer->GetCursorCoord(x, y, renderer->lfieldrect, xprev, yprev);
            x1 = x2 = xprev;
            y1 = y2 = yprev;
            break;
        case C_Field2:
            active2 = true;
            renderer->GetCursorCoord(x, y, renderer->rfieldrect, zprev, wprev);
            z1 = z2 = zprev;
            w1 = w2 = wprev;
            break;
    }
}

void Cursor::CursorMove(int x, int y, Renderer * renderer){
    int xcur, ycur;
    switch (focus){
        case C_Field1:
            renderer->GetCursorCoord(x, y, renderer->lfieldrect, xcur, ycur);
            x1 = (xcur<xprev)?xcur:xprev;
            x2 = (xcur<xprev)?xprev:xcur;
            y1 = (ycur<yprev)?ycur:yprev;
            y2 = (ycur<yprev)?yprev:ycur;
            break;
        case C_Field2:
            renderer->GetCursorCoord(x, y, renderer->rfieldrect, xcur, ycur);
            z1 = (xcur<zprev)?xcur:zprev;
            z2 = (xcur<zprev)?zprev:xcur;
            w1 = (ycur<wprev)?ycur:wprev;
            w2 = (ycur<wprev)?wprev:ycur;
            break;
    }
}

void Cursor::CursorEnd(int x, int y, Renderer * renderer){
    CursorMove(x, y, renderer);
    focus = C_None;
}


