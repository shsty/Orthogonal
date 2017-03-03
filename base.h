#ifndef BASE_H
#define BASE_H

#include <algorithm>

enum AxisPair {AXIS_XY = 0, AXIS_ZW = 1};

class vec2int{
public:
    int x, y;
    vec2int(int _x, int _y):x(_x), y(_y){}
    vec2int():vec2int(0, 0){}
    vec2int operator + (const vec2int & v) const {return vec2int(x + v.x, y + v.y);}
    vec2int operator * (const int & a) const {return vec2int(x*a, y*a);}
};

class vec4int{
public:
    int x, y, z, w;
    vec4int(int _x, int _y, int _z, int _w):x(_x), y(_y), z(_z), w(_w){}
    vec4int(vec2int p, vec2int q):x(p.x), y(p.y), z(q.x), w(q.y){}
    vec4int():vec4int(0, 0, 0, 0){}
    vec2int getxy() const {return vec2int(x, y);}
    vec2int getzw() const {return vec2int(z, w);}
};

class box4int{
public:
    int x1, x2, y1, y2, z1, z2, w1, w2;
    box4int(int _x1, int _x2, int _y1, int _y2, int _z1, int _z2, int _w1, int _w2):x1(_x1), x2(_x2), y1(_y1), y2(_y2), z1(_z1), z2(_z2), w1(_w1), w2(_w2){
        if (x1 < x2) std::swap(x1, x2);
        if (y1 < y2) std::swap(y1, y2);
        if (z1 < z2) std::swap(z1, z2);
        if (w1 < w2) std::swap(w1, w2);
    }
    box4int(vec4int v1, vec4int v2):box4int(v1.x, v2.x, v1.y, v2.y, v1.z, v2.z, v1.w, v2.w){}
    box4int():box4int(0, 0, 0, 0, 0, 0, 0, 0){}

    int width1(){return x2 - x1;}
    int height1(){return y2 - y1;}
    int width2(){return z2 - z1;}
    int height2(){return w2 - w1;}

    void width1_set(int width1){x2 = x1 + width1;}
    void height1_set(int height1){y2 = y1 + height1;}
    void width2_set(int width2){z2 = z1 + width2;}
    void height2_set(int height2){w2 = w1 + height2;}
};

class vec2double{
public:
    double x, y;
    vec2double(double _x, double _y):x(_x), y(_y){}
    vec2double():vec2double(0, 0){}
    vec2double operator + (const vec2double & v) const {return vec2double(x + v.x, y + v.y);}
    vec2double operator * (const double & a) const {return vec2double(x*a, y*a);}
};

class vec4double{
public:
    double x, y, z, w;
    vec4double(double _x, double _y, double _z, double _w):x(_x), y(_y), z(_z), w(_w){}
    vec4double(vec2double p, vec2double q):x(p.x), y(p.y), z(q.x), w(q.y){}
    vec4double():vec4double(0, 0, 0, 0){}
    vec2double getxy() const {return vec2double(x, y);}
    vec2double getzw() const {return vec2double(z, w);}
};

class box4double{
public:
    double x1, x2, y1, y2, z1, z2, w1, w2;
    box4double(double _x1, double _x2, double _y1, double _y2, double _z1, double _z2, double _w1, double _w2):x1(_x1), x2(_x2), y1(_y1), y2(_y2), z1(_z1), z2(_z2), w1(_w1), w2(_w2){
        if (x1 < x2) std::swap(x1, x2);
        if (y1 < y2) std::swap(y1, y2);
        if (z1 < z2) std::swap(z1, z2);
        if (w1 < w2) std::swap(w1, w2);
    }
    box4double(vec4double v1, vec4double v2):box4double(v1.x, v2.x, v1.y, v2.y, v1.z, v2.z, v1.w, v2.w){}
    box4double():box4double(0, 0, 0, 0, 0, 0, 0, 0){}

    double width1(){return x2 - x1;}
    double height1(){return y2 - y1;}
    double width2(){return z2 - z1;}
    double height2(){return w2 - w1;}

    void width1_set(double width1){x2 = x1 + width1;}
    void height1_set(double height1){y2 = y1 + height1;}
    void width2_set(double width2){z2 = z1 + width2;}
    void height2_set(double height2){w2 = w1 + height2;}
};

#endif
