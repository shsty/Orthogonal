#ifndef CURSOR_H
#define CURSOR_H

#include "declaration.h"

#ifndef CFIELDS
#define CFIELDS
enum Cfields {C_None, C_Field1, C_Field2};
#endif

class Cursor{
public:
    int x1, x2, y1, y2, z1, z2, w1, w2;
    int xprev, yprev, zprev, wprev;
    bool active1, active2;
    enum Cfields focus;

    void render(Renderer * ren);
    void CursorStart(int x, int y, Renderer * renderer);
    void CursorMove(int x, int y, Renderer * renderer);
    void CursorEnd(int x, int y, Renderer * renderer);
};

#endif
