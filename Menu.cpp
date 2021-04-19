#include "Menu.h"

//  Tên game
SDL_Rect menu_title_rect;
//  Button
SDL_Rect menu_button_rect;
//  Background
SDL_Rect menu_buttonbackground_rect;
//  Khoảng cách giữa các Button
int menu_buttonspace;

ImgObject menu_background;
ImgObject menu_title;

//  Các nút bấm
std::vector<ButtonObject> menu_button;


void MainMenuFunc::SetMenuRect(){
    /////////////////////////////////////////////////////////
    //  Hàm tính toán kích thước và tọa độ của các thành phần trong menu
    //  Tính toán dựa vào kích thước chuẩn là 1080px
    /////////////////////////////////////////////////////////
    const int SC_HEIGHT = GetScHeight();
    const int SC_WIDTH = GetScWidth();
    //  Game title
    menu_title.rect =   {
                            (SC_WIDTH - MENUTITLE_IMG.w*SC_HEIGHT/1080)/2,
                            SC_HEIGHT/4,
                            MENUTITLE_IMG.w*SC_HEIGHT/1080,
                            MENUTITLE_IMG.h*SC_HEIGHT/1080
                        };
    //  Button
    menu_button_rect =  {
                            (SC_WIDTH - MENUBUTTON_IMG.w*SC_HEIGHT/1080)/2,
                            menu_title.rect.y + (MENUTITLE_IMG.h+80)*SC_HEIGHT/1080,
                            MENUBUTTON_IMG.w*SC_HEIGHT/1080,
                            MENUBUTTON_IMG.h*SC_HEIGHT/1080
                        };

    //  Background
    menu_background.rect =    {
                                        (SC_WIDTH - MENUBACKGROUND_IMG.w*SC_HEIGHT/1080)/2,
                                        menu_button_rect.y - 25*SC_HEIGHT/1080,
                                        MENUBACKGROUND_IMG.w*SC_HEIGHT/1080,
                                        MENUBACKGROUND_IMG.h*SC_HEIGHT/1080
                                    };
    //  Khoảng cách giữa các Button
    menu_buttonspace = MENUBUTTON_SPACE*SC_HEIGHT/1080;
}

void MainMenuFunc::InitButton(SDL_Renderer *&renderer){
    /////////////////////////////////////////////////
    //  Khởi tạo các giá trị cho các Nút bấm
    //      -   Khởi tạo tọa độ và kích thước
    //      -   Khởi tạo hình ảnh
    /////////////////////////////////////////////////

    menu_button.resize(MENU_MAXBUTTON);
    for (int i = 0; i < MENU_MAXBUTTON; ++i)
    {
        menu_button[i].rect =   {
                                    menu_button_rect.x,
                                    menu_button_rect.y + menu_button_rect.h*i + menu_buttonspace*i,
                                    menu_button_rect.w,
                                    menu_button_rect.h
                                };
        menu_button[i].texture_normal = LoadImg("menu_button"+std::to_string(i)+".png", renderer);
        menu_button[i].texture_focus = LoadImg("menu_button"+std::to_string(i)+".png",  renderer);
    }
}

void MainMenu(std::string &main_state, SDL_Renderer *&renderer){

    //  Tính toán tọa độ và kích thước
    MainMenuFunc::SetMenuRect();
    //  Khởi tạo các Button
    MainMenuFunc::InitButton(renderer);
    //  Vẽ nền
    DrawBackground(renderer);

    //  Vẽ tên game và nền
    menu_background.LoadFile("menu_background.png", renderer);
    menu_title.LoadFile("game_title.png", renderer);
    menu_background.Draw(renderer);
    menu_title.Draw(renderer);

    for (int i = 0; i < MENU_MAXBUTTON; ++i)
        menu_button[i].Draw(renderer);

    main_state = MAIN_HAPPEN;
    bool quit = false;
    while (CheckQuitCurrent(quit, main_state) == false)
    {
        if (SDL_WaitEvent(&g_event) != 0)
        {
            switch (g_event.type)
            {
                //  Thoát chương trình
                case SDL_QUIT: main_state = MAIN_EXIT; break;

                //  Button focus
                case SDL_MOUSEMOTION:
                    for (int i = 0; i < MENU_MAXBUTTON; ++i)
                        menu_button[i].Focus(renderer);
                    break;

                //  Khi nhấn chuột
                case SDL_MOUSEBUTTONDOWN:
                    //  Tạo ván mới
                    if (menu_button[0].Click())
                        SetGameDifficulty(main_state, renderer);

                    //  Thay đổi chế độ chơi
                    else if (menu_button[1].Click()){
                        SetGameMode(main_state, renderer);
                    }
                    //  Mở Cài đặt
                    else if (menu_button[2].Click()){
                        SettingMenu(main_state, renderer);
                    }
                    //  Thoát chương trình
                    else if (menu_button[3].Click())
                    {
                        main_state = MAIN_EXIT;
                        SDL_Delay(100);
                    }
                    break;
            }
        }
        SDL_RenderPresent(renderer);
    }
}
