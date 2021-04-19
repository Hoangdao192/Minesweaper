#include "SetGameMode.h"

static int game_mode;

int gamemode_button_space;

ButtonObject mode_classic_button;
ButtonObject mode_countdown_button;

ImgObject gamemode_background;

void GameModeFunc::SetRect(){
    const int SC_HEIGHT = GetScHeight();
    const int SC_WIDTH = GetScWidth();

    gamemode_button_space = GAMEMODE_BUTTONSPACE*SC_HEIGHT/1080;

    mode_classic_button.rect =  {
                                    (SC_WIDTH - GAMEMODE_BUTTONRECT.w*SC_HEIGHT/1080)/2,
                                    (SC_HEIGHT - GAMEMODE_BUTTONRECT.h*4*SC_HEIGHT/1080)/2,
                                    GAMEMODE_BUTTONRECT.w*SC_HEIGHT/1080,
                                    GAMEMODE_BUTTONRECT.h*SC_HEIGHT/1080
                                };
    mode_countdown_button.rect =    {
                                        mode_classic_button.rect.x,
                                        mode_classic_button.rect.y + mode_classic_button.rect.h + gamemode_button_space,
                                        GAMEMODE_BUTTONRECT.w*SC_HEIGHT/1080,
                                        GAMEMODE_BUTTONRECT.h*SC_HEIGHT/1080
                                    };
    gamemode_background.rect =   {
                                    mode_classic_button.rect.x - (GAMEMODE_BACKGROUNDRECT.w*SC_HEIGHT/1080 - mode_classic_button.rect.w)/2,
                                    mode_classic_button.rect.y - 20*SC_HEIGHT/1080,
                                    GAMEMODE_BACKGROUNDRECT.w*SC_HEIGHT/1080,
                                    GAMEMODE_BACKGROUNDRECT.h*SC_HEIGHT/1080
                                };
}

void GameModeFunc::LoadMedia(SDL_Renderer *&renderer){

    mode_classic_button.texture_focus = LoadImg("mode_classic.png", renderer);
    mode_classic_button.texture_normal = LoadImg("mode_classic.png", renderer);

    mode_countdown_button.texture_normal = LoadImg("mode_countdown.png", renderer);
    mode_countdown_button.texture_focus = LoadImg("mode_countdown.png", renderer);

    gamemode_background.LoadFile("difficulty_setting_background.png", renderer);

}

void SetGameMode(std::string &main_state, SDL_Renderer *&renderer){
    const int SC_WIDTH = GetScWidth();
    const int SC_HEIGHT = GetScHeight();

    GameModeFunc::SetRect();
    GameModeFunc::LoadMedia(renderer);

    //  Lưu lại màn hình
    SDL_Surface *old_surface = SDL_CreateRGBSurface(0, SC_WIDTH, SC_HEIGHT, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, old_surface->pixels, old_surface->pitch);

    BlurScreen(SC_WIDTH, SC_HEIGHT, renderer);

    gamemode_background.Draw(renderer);

    //  Vẽ các Button
    mode_classic_button.Draw(renderer);
    mode_countdown_button.Draw(renderer);

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
                    mode_classic_button.Focus(renderer);
                    mode_countdown_button.Focus(renderer);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (mode_classic_button.Click()) game_mode = 0;
                    else if (mode_countdown_button.Click()) game_mode = 1;
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

int GetGameMode(){return game_mode;};
