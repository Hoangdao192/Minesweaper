
#include "MainFunction.h"
#include "Menu.h"
#include "Game.h"
#include <fstream>
#include <sstream>
#include <string>

std::string g_main_state = MAIN_MENU;

//  Khởi tạo SDL, TTF, IMG, MIXER ...
void Init();

//  Hủy các con trỏ và thoát game
void Quit();

int main(int argc, char* argv[]){

    std::fstream settingfile;
    settingfile.open("setting", std::ios::in | std::ios::out);
    std::string line;
    std::getline(settingfile, line);
    std::stringstream ss(line);
    int *SC_WIDTH = GetScWidthReference();
    int *SC_HEIGHT = GetScHeightReference();
    bool *mute = GetMuteReference();
    ss >> *SC_WIDTH >> *SC_HEIGHT >> *mute;

    Init();
    int height = GetScHeight(), width = GetScWidth();
    while (g_main_state.compare(MAIN_EXIT) != 0 && g_event.type != SDL_QUIT){
        if (g_main_state.compare(MAIN_MENU) == 0) MainMenu(g_main_state, g_renderer);
        else if (g_main_state.compare(MAIN_NEWGAME) == 0) NewGame(g_main_state, g_renderer);
        else if (g_main_state.compare(MAIN_EXIT) == 0) break;
        else if (g_main_state.compare(MAIN_RESTART) == 0)
        {
            SDL_DestroyWindow(g_window);
            SDL_DestroyRenderer(g_renderer);

            g_window = SDL_CreateWindow(WINDOW_TITLE.c_str(), 20, 20, GetScWidth(), GetScHeight(), SDL_WINDOW_SHOWN);
            g_renderer = SDL_CreateRenderer (g_window, -1, SDL_RENDERER_ACCELERATED);
            SDL_RenderSetLogicalSize(g_renderer, GetScWidth(), GetScHeight());

            g_main_state = MAIN_MENU;
        }
    }

    settingfile.clear();
    settingfile.seekg(0, std::ios::beg);
    settingfile << GetScWidth() << " " << GetScHeight() << " " <<  GetMute();
    settingfile.close();

    Quit();
    return 0;
}

void Quit(){
    SDL_DestroyWindow(g_window);
    SDL_DestroyRenderer(g_renderer);
    g_window = NULL;
    g_renderer = NULL;
    Mix_FreeMusic(g_music);
    SDL_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
}

void Init(){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) std::cout << "SDL_Init failed" << std::endl;

    g_window = SDL_CreateWindow(WINDOW_TITLE.c_str(), 20, 20, GetScWidth(), GetScHeight(), SDL_WINDOW_SHOWN);
    if (g_window == NULL) std::cout << "SDL_CreateWindow failed" << std::endl;

    g_renderer = SDL_CreateRenderer (g_window, -1, SDL_RENDERER_ACCELERATED);
    if (g_renderer == NULL) std::cout << "SDL_CreateRenderer failed" << std::endl;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
    SDL_RenderSetLogicalSize(g_renderer, GetScWidth(), GetScHeight());
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}


