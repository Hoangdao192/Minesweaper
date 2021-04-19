#ifndef SETGAMEMODE_H_INCLUDED
#define SETGAMEMODE_H_INCLUDED

#include "MainFunction.h"
#include "ButtonObject.h"
#include "ImgObject.h"

const int GAMEMODE_BUTTONSPACE = 10;
const SDL_Rect GAMEMODE_BUTTONRECT = {0,0,400,100};
const SDL_Rect GAMEMODE_BACKGROUNDRECT = {0,0,490,410};

namespace GameModeFunc{
    void SetRect();
    void LoadMedia(SDL_Renderer *&renderer);
}


#endif // SETGAMEMODE_H_INCLUDED
