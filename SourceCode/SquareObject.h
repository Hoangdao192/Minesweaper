#ifndef SQUAREOBJECT_H_INCLUDED
#define SQUAREOBJECT_H_INCLUDED

#include "MainFunction.h"
#include "TextObject.h"

class SquareObject{
    public:
        short point;
        TextObject point_text;
        bool set_flag, is_open, is_bom;
        SDL_Rect rect;
        SDL_Texture *texture_normal;
        SDL_Texture *texture_open;
        SDL_Texture *texture_flag;

        SquareObject();
        ~SquareObject();
        void Draw(SDL_Renderer *&renderer);
        void Focus(SDL_Renderer *&renderer);
        void Open(SDL_Renderer *&renderer);
        void DrawPoint(SDL_Renderer *&renderer);
        void SetBom(SDL_Renderer *&renderer);
        void SetFlag(SDL_Renderer *&renderer);
        void DeleteFlag(SDL_Renderer *&renderer);
};

#endif // SQUAREOBJECT_H_INCLUDED
