#include "SetGameDifficulty.h"

static GameSet difficulty;

int difficulty_button_space;
SDL_Rect difficulty_setting_rect;
SDL_Rect difficulty_background_rect;

std::vector<ButtonObject> difficulty_button;

ImgObject setdiff_background;

GameSet GetDifficulty(){
    return difficulty;
}

void SetDiffFunc::SetRect(){
    const int SC_WIDTH = GetScWidth();
    const int SC_HEIGHT = GetScHeight();

    //  Khoảng trống giữa các Button
    difficulty_button_space = DIFFSETTING_BUTTONSPACE*SC_HEIGHT/1080;

    //  Tọa độ và kích thước chung của các Button
    difficulty_setting_rect =  {
                                    (SC_WIDTH - DIFFBUTTON_RECT.w*SC_HEIGHT/1080)/2,
                                    (SC_HEIGHT - DIFFBUTTON_RECT.h*4*SC_HEIGHT/1080)/2,
                                    DIFFBUTTON_RECT.w*SC_HEIGHT/1080,
                                    DIFFBUTTON_RECT.h*SC_HEIGHT/1080
                                };
    //  Tọa độ và kích thước nền phụ
    setdiff_background.rect =   {
                                    difficulty_setting_rect.x - (DIFBACKGROUND_RECT.w*SC_HEIGHT/1080 - difficulty_setting_rect.w)/2,
                                    difficulty_setting_rect.y - 20*SC_HEIGHT/1080,
                                    DIFBACKGROUND_RECT.w*SC_HEIGHT/1080,
                                    DIFBACKGROUND_RECT.h*SC_HEIGHT/1080
                                };
}

void SetDiffFunc::LoadMedia(SDL_Renderer *&renderer){
    difficulty_button.resize(DIFSETTING_MAXBUTTON);
    for (int i = 0; i < DIFSETTING_MAXBUTTON; ++i)
    {
        difficulty_button[i].rect =     {
                                            difficulty_setting_rect.x,
                                            difficulty_setting_rect.y + difficulty_setting_rect.h*i + difficulty_button_space*i,
                                            difficulty_setting_rect.w,
                                            difficulty_setting_rect.h
                                        };
        difficulty_button[i].texture_normal = LoadImg("dif_settingbutton"+std::to_string(i)+".png", renderer);
        difficulty_button[i].texture_focus = LoadImg("dif_settingbutton"+std::to_string(i)+".png", renderer);
    }

    setdiff_background.LoadFile("difficulty_setting_background.png", renderer);
}

void SetGameDifficulty(std::string &main_state, SDL_Renderer *&renderer){
    const int SC_WIDTH = GetScWidth();
    const int SC_HEIGHT = GetScHeight();
    //  Lưu lại màn hình
    SDL_Surface *old_surface = SDL_CreateRGBSurface(0, SC_WIDTH, SC_HEIGHT, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, old_surface->pixels, old_surface->pitch);
    //  Làm mờ màn hình
    BlurScreen(SC_WIDTH, SC_HEIGHT, renderer);

    SetDiffFunc::SetRect();
    SetDiffFunc::LoadMedia(renderer);
    //  Vẽ nền
    setdiff_background.Draw(renderer);

    //  Vẽ các Button
    for (int i = 0; i < DIFSETTING_MAXBUTTON; ++i)
        difficulty_button[i].Draw(renderer);


    //  Vòng lặp chính
    bool quit = false;
    while (CheckQuitCurrent(quit, main_state) == false)
    {
        if (SDL_WaitEventTimeout(&g_event,10) != 0)
        {
            switch (g_event.type)
            {
                case SDL_QUIT: main_state = MAIN_EXIT; break;

                case SDL_MOUSEMOTION:
                    for (int i = 0; i < DIFSETTING_MAXBUTTON; ++i)
                        difficulty_button[i].Focus(renderer);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (difficulty_button[0].Click())
                    {
                        difficulty = VERYEASY;
                        main_state = MAIN_NEWGAME;
                    }
                    else if (difficulty_button[1].Click())
                    {
                        difficulty = EASY;
                        main_state = MAIN_NEWGAME;
                    }
                    else if (difficulty_button[2].Click())
                    {
                        difficulty = MEDIUM;
                        main_state = MAIN_NEWGAME;
                    }
                    else if (difficulty_button[3].Click())
                    {
                        difficulty = HARD;
                        main_state = MAIN_NEWGAME;
                    }
                    else if (difficulty_button[4].Click()){
                        difficulty = CustomDifficulty(main_state, renderer);
                    }
                    quit = true;
                    break;
            }
        }
        SDL_RenderPresent(renderer);
    }


    // Xuất ra màn hình cũ
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, old_surface);
    ApplyTexture(texture, renderer, {0, 0, SC_WIDTH, SC_HEIGHT});
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(old_surface);
}
