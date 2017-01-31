#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <stdexcept>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>

const int ERRBUFSIZE=1024;
extern char msg[ERRBUFSIZE];

class SDL_Exception: public std::exception{
public:
    virtual const char* what() throw(){
        snprintf(msg, ERRBUFSIZE, "SDL Error: %s", SDL_GetError());
        return msg;
    }
};

class IMG_Exception: public SDL_Exception{
public:
    virtual const char* what() throw(){
        snprintf(msg, ERRBUFSIZE, "SDL_Image Error: %s", IMG_GetError());
        return msg;
    }
};

#endif


