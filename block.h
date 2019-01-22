#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <json/json.h>
#include "base.h"
#include "declaration.h"

enum P_Dir{
    P_xPositive, P_xNegative,
    P_yPositive, P_yNegative,
    P_zPositive, P_zNegative,
    P_wPositive, P_wNegative,
};

namespace BlockType{

    class BlockType{
    public:
        std::string lSpriteName, rSpriteName;
        int lSpriteNum, rSpriteNum;
        Map * map;

        BlockType(){}

        virtual void renderLeft(Renderer * ren, int x, int y, double alpha = 1.0);
        virtual void renderRight(Renderer * ren, int z, int w, double alpha = 1.0);

        virtual void collide(Object * object, enum P_Dir dir, vec4int pos){}
        virtual void overlay(Object * object, vec4int pos){}

        virtual Json::Value toJson();
        virtual void fromJson(Json::Value json);
    };

    class Air:public BlockType{
    public:
        Air():BlockType(){
            lSpriteName = "block"; lSpriteNum = 0;
            rSpriteName = "block"; rSpriteNum = 0;
        }
    };

    class StarsBG:public Air{
    public:
        StarsBG():Air(){
            lSpriteName = "stars"; lSpriteNum = 0;
            rSpriteName = "stars"; rSpriteNum = 0;
        }
        virtual void renderLeft(Renderer * ren, int x, int y, double alpha = 1.0);
        virtual void renderRight(Renderer * ren, int z, int w, double alpha = 1.0);
    };

    class Solid:public BlockType{
    public:
        Solid():BlockType(){
            lSpriteName = "block"; lSpriteNum = 1;
            rSpriteName = "block"; rSpriteNum = 1;
        }
        virtual void collide(Object * object, enum P_Dir dir, vec4int pos);
    };

    class Spike:public Solid{
    public:
        Spike():Solid(){
            lSpriteName = "block"; lSpriteNum = 2;
            rSpriteName = "block"; rSpriteNum = 2;
        }
    };

    class Mist:public Air{
    public:
        Mist():Air(){
            lSpriteName = "block"; lSpriteNum = 3;
            rSpriteName = "block"; rSpriteNum = 3;
        }
    };

    class Metal:public Solid{
    public:
        Metal():Solid(){
            lSpriteName = "block"; lSpriteNum = 4;
            rSpriteName = "block"; rSpriteNum = 4;
        }
    };

    class Chroley:public Solid{
    public:
        Chroley():Solid(){
            lSpriteName = "block"; lSpriteNum = 5;
            rSpriteName = "block"; rSpriteNum = 5;
        }
    };
}

#endif
