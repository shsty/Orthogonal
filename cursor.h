#ifndef CURSOR_H
#define CURSOR_H

class Renderer;

class Cursor{
public:
    int x1, x2, y1, y2, z1, z2, w1, w2;
    int xprev, yprev, zprev, wprev;
    bool active1, active2;
    enum Cfields {C_None, C_Field1, C_Field2} focus;

    void render(Renderer * ren);
};

#endif
