#ifndef BUTTONOBJECT_H_INCLUDED
#define BUTTONOBJECT_H_INCLUDED

#include "MainFunction.h"

class ButtonObject{
    public:
        SDL_Rect rect;
        SDL_Texture *texture_normal;
        SDL_Texture *texture_focus;
        bool is_clicked = false;
        bool is_focus = false;

        void Draw(SDL_Renderer *&renderer);
        void Focus(SDL_Renderer *&renderer);
        bool Click();
        ButtonObject();
        ~ButtonObject();
};


#endif // BUTTONOBJECT_H_INCLUDED

