#ifndef MAINVARIABLE_H_INCLUDED
#define MAINVARIABLE_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <windows.h>
#include <vector>
#include <sstream>

const std::string MAIN_RESTART = "restart game";
const std::string MAIN_MENU = "menu";
const std::string MAIN_SETTING = "setting";
const std::string MAIN_EXIT = "exit";
const std::string MAIN_NEWGAME = "new game";
const std::string MAIN_HAPPEN = "happening";

const std::string WINDOW_TITLE = "Minesweaper";

static SDL_Window *g_window = NULL;
static SDL_Renderer *g_renderer = NULL;
static Mix_Music *g_music = NULL;
static SDL_Event g_event;

const std::string FONT_PATH = "Font/";


///////////////////////////////////////////////////////
//  Màu sắc trong game
///////////////////////////////////////////////////////
const SDL_Color background_color = {113,117,44,0};  //  Màu nền
const SDL_Color POINT_COLOR[8] =           //  Màu của số bom
{
    {255,0,255,0},  //1
    {128,128,0,0},  //2
    {0,128,0,0},    //3
    {0,0,255,0},    //4
    {0,0,128,0},    //5
    {255,0,0,0},    //6
    {80,80,80,0},   //7
    {155,0,0,0}     //8
};
static SDL_Color square_color_normal[2] =   //  Màu của ô vuông chưa mở
{
    {162,209,73,0},
    {170,215,81,0}
};
static SDL_Color square_color_opened[2] =   //  Màu của ô vuông đã mở
{
    {238,233,233,0},
    {230,210,200,0}
};
static SDL_Texture *square_normal1 = NULL;
static SDL_Texture *square_normal2 = NULL;
static SDL_Texture *square_open1 = NULL;
static SDL_Texture *square_open2 = NULL;
static SDL_Texture *bom1 = NULL;
static SDL_Texture *bom2 = NULL;
static SDL_Texture *flag1 = NULL;
static SDL_Texture *flag2 = NULL;
const SDL_Color text_color_1 = {255,255,255,0};

const int SQUARESIZE_MAX = 91;

//  Font
const std::string SQUAREPOINT_FONT = "Font_menu.ttf";

//  Font size
const int SQUAREPOINT_SIZE = 110;
static int font_size_0 = 300;//*SCREEN_HEIGHT/1080;
static int font_size_1 = 100;//*SCREEN_HEIGHT/1080;
static int font_size_2 = 110;//*SCREEN_HEIGHT/1080;

int GetScHeight();
int GetScWidth();
bool GetMute();
int *GetScHeightReference();
int *GetScWidthReference();
bool *GetMuteReference();

#endif // MAINVARIABLE_H_INCLUDED
