#ifndef CUSTOMDIFFICULTY_H_INCLUDED
#define CUSTOMDIFFICULTY_H_INCLUDED

#include "MainFunction.h"
#include "ButtonObject.h"
#include "ImgObject.h"
#include "TextObject.h"

const SDL_Rect CUSTOMDIFF_BACKGROUND = {0,0,770,360};

GameSet CustomDifficulty(std::string &main_state, SDL_Renderer *&renderer);
namespace CustomDiffFunc{
    void SetRect();
    void LoadMedia(SDL_Renderer *&renderer);
}

bool CheckGameSet(SDL_Renderer *&renderer);
void GetTextInput(TextObject &text, const int MAX_CHAR, SDL_Rect &rect, SDL_Texture *&texture, SDL_Renderer *&renderer);

#endif // CUSTOMDIFFICULTY_H_INCLUDED
