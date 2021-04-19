#ifndef SETTING_H_INCLUDED
#define SETTING_H_INCLUDED

#include "MainFunction.h"
#include "ButtonObject.h"
#include "ImgObject.h"

const SDL_Rect RESOLUTIONTEXT_RECT = {0,0,731,108};
const SDL_Rect RESOLUTIONBUTTON_RECT = {0,0,300,70};
const SDL_Rect RESOLUTIONAPPLY_RECT = {0,0,600,200};
const SDL_Rect RESOLUTIONAPPLY_BUTTON = {0,0,290,100};

const int SC_RESOLUTION = 5;
const int WIDTH[5] =   {800, 1024, 1280, 1440, 1920};
const int HEIGHT[5] =  {800, 768 , 720 , 900 , 1080};

namespace SettingMenuFunc{
    void SetRect();
    void InitButton(SDL_Renderer *&renderer);
}

namespace ResolutionSettingFunc{
    void SetRect();
    void InitButton(SDL_Renderer *&renderer);
    bool AskResolutionApply(std::string &main_state, SDL_Renderer *&renderer);
}

void ResolutionSetting(std::string &main_state, SDL_Renderer *&renderer);



#endif // SETTING_H_INCLUDED
