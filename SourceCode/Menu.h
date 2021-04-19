#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "MainFunction.h"
#include "ButtonObject.h"

const SDL_Rect MENUTITLE_IMG = {0,0,964,107};
const SDL_Rect MENUBUTTON_IMG = {0,0,492,100};
const SDL_Rect MENUBACKGROUND_IMG = {0,0,560,370};
const int MENUBUTTON_SPACE = 10;
const int MENU_MAXBUTTON = 4;
//0: Chơi mới
//1: Chế độ chơi
//2: Cài đặt
//3: Thoát

namespace MainMenuFunc {
    void SetMenuRect();
    void InitButton(SDL_Renderer *&renderer);
}

#endif // MENU_H_INCLUDED
