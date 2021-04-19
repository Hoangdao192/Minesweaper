#ifndef SETGAMEDIFFICULTY_H_INCLUDED
#define SETGAMEDIFFICULTY_H_INCLUDED

#include "MainFunction.h"
#include "ButtonObject.h"
#include "ImgObject.h"
#include "TextObject.h"
#include "CustomDifficulty.h"

const GameSet VERYEASY = {10,10,10,15,2};
const GameSet EASY = {15,10,10,13,3};
const GameSet MEDIUM = {40,15,15,10,4};
const GameSet HARD = {150,20,20,7,10};

const int DIFFSETTING_BUTTONSPACE = 10;
const SDL_Rect DIFFBUTTON_RECT = {0,0,400,100};
const SDL_Rect DIFBACKGROUND_RECT = {0,0,490,410};

const int DIFSETTING_MAXBUTTON = 5;

namespace SetDiffFunc{
    void SetRect();
    void InitButton(SDL_Renderer *&renderer);
    void LoadMedia(SDL_Renderer *&renderer);
}
GameSet GetDifficulty();
#endif // SETGAMEDIFFICULTY_H_INCLUDED
