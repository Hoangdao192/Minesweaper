
#include "Quick_setting.h"

SDL_Rect quickmenu_rect;
int quickmenu_button_space;

std::vector<ButtonObject> quickmenu_button;
const int QUICKMENU_MAXBUTTON = 6;
//  0: Chơi tiếp
//  1: Chơi lại
//  2: Độ khó
//  3: Cài đặt
//  4: Quay về menu
//  5: Thoát


void QuickSettingFunc::SetQuickSetttingRect(){
    const int SC_WIDTH = GetScWidth();
    const int SC_HEIGHT = GetScHeight();
    quickmenu_button_space = 10*SC_HEIGHT/1080;
    quickmenu_rect =   {
                            (SC_WIDTH - 492*SC_HEIGHT/1080)/2,
                            SC_HEIGHT/4,
                            492*SC_HEIGHT/1080,
                            100*SC_HEIGHT/1080
                        };
}

void QuickSettingFunc::InitButton(SDL_Renderer *&renderer){
    quickmenu_button.resize(QUICKMENU_MAXBUTTON);
    for (int i = 0; i < QUICKMENU_MAXBUTTON; ++i)
    {
        quickmenu_button[i].rect =  {
                                        quickmenu_rect.x,
                                        quickmenu_rect.y + quickmenu_rect.h*i + quickmenu_button_space*i,
                                        quickmenu_rect.w,
                                        quickmenu_rect.h
                                    };
        quickmenu_button[i].texture_normal = LoadImg("quickmenu_button"+std::to_string(i)+".png", renderer);
        quickmenu_button[i].texture_focus = LoadImg("quickmenu_button"+std::to_string(i)+".png", renderer);
    }
}

void QuickSettingMenu(std::string &main_state, SDL_Renderer *&renderer){
     /////////////////////////////////////////////////////////////////////////
    //  Hiển thị menu cài đặt nhanh khi nhấn vào biểu tượng cài đặt
    /////////////////////////////////////////////////////////////////////////
    const int SC_WIDTH = GetScWidth();
    const int SC_HEIGHT = GetScHeight();

    QuickSettingFunc::SetQuickSetttingRect();
    QuickSettingFunc::InitButton(renderer);


    //  Lưu lại màn hình hiện tại
    SDL_Surface *old_surface = SDL_CreateRGBSurface(0, SC_WIDTH, SC_HEIGHT, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, old_surface->pixels, old_surface->pitch);
    //  Làm mờ màn hình hiện tại
    BlurScreen(SC_WIDTH, SC_HEIGHT, renderer);

    //  Vẽ Button
    for (int i = 0; i < QUICKMENU_MAXBUTTON; ++i)
        quickmenu_button[i].Draw(renderer);
    bool mute = false;

    //  Vòng lặp chính
    bool quit = false;
    while (CheckQuitCurrent(quit, main_state) == false)
    {
        if (SDL_WaitEventTimeout(&g_event,10) != 0)
        switch (g_event.type)
        {
            case SDL_QUIT:
                main_state = MAIN_EXIT;
                break;

            //  Khi nhấn vào các tùy chọn
            case SDL_MOUSEBUTTONDOWN:
                //  Chơi tiếp
                if (quickmenu_button[0].Click()) quit = true;
                //  Chơi lại
                else if (quickmenu_button[1].Click())
                {
                    quit = true;
                    main_state = MAIN_NEWGAME;
                }
                //  Cài đặt độ khó
                else if (quickmenu_button[2].Click()) SetGameDifficulty(main_state, renderer);
                //  Mở menu Cài đặt
                else if (quickmenu_button[3].Click()) SettingMenu(main_state, renderer);
                //  Quay về màn hình chính
                else if (quickmenu_button[4].Click()) main_state = MAIN_MENU;
                //  Thoát game
                else if (quickmenu_button[5].Click())
                {
                    quit = true;
                    main_state = MAIN_EXIT;
                }
                break;

            //  Khi di chuột vào các tùy chọn
            case SDL_MOUSEMOTION:
                for (int i = 0; i < QUICKMENU_MAXBUTTON; ++i)
                    quickmenu_button[i].Focus(renderer);
                break;
        }
        SDL_RenderPresent(renderer);
    }

    //  Trả lại màn hình cũ và xóa con trỏ
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, old_surface);
    ApplyTexture(texture, renderer, {0,0,SC_WIDTH, SC_HEIGHT});
    SDL_FreeSurface(old_surface);
    SDL_DestroyTexture(texture);
}
