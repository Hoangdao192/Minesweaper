#ifndef IMGOBJECT_H_INCLUDED
#define IMGOBJECT_H_INCLUDED

#include "MainFunction.h"

class ImgObject{
    public:
        ImgObject();
        ~ImgObject();
        SDL_Texture *texture;
        SDL_Surface *surface;
        SDL_Rect rect;
        void Draw(SDL_Renderer *&renderer);
        bool LoadFile(std::string path, SDL_Renderer *&renderer);
};


#endif // IMGOBJECT_H_INCLUDED
