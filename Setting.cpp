#include "Setting.h"

//  Button Độ phân giải
ButtonObject resolution_button;
//  Button quay lại
ButtonObject back_button;
//  Button tắt tiếng
ButtonObject mute_button;
//  Các độ phân giải
ButtonObject res_button[SC_RESOLUTION];

//  Thông báo xác nhận thay đổi Resolution
ImgObject resolutionapply_note;

//  Button quay lại
SDL_Rect back_button_rect;
//  Button độ phân giải
SDL_Rect resolution_button_rect;
//  chữ Resolution
SDL_Rect resolution_text_rect;
//  Button Tắt tiếng
SDL_Rect mute_button_rect;
//  Xác nhận thay đổi Độ phân giải
SDL_Rect resolution_apply_rect;
//  Đồng ý
SDL_Rect resolution_yes_rect;
//  Hủy bỏ
SDL_Rect resolution_no_rect;

//  Cài đặt
void SettingMenuFunc::SetRect(){
    const int SC_WIDTH = GetScWidth();
    const int SC_HEIGHT = GetScHeight();
    //  "Chữ Resolution"
    resolution_text_rect =  {
                                SC_HEIGHT/5,
                                200*SC_HEIGHT/1080,
                                RESOLUTIONTEXT_RECT.w*SC_HEIGHT/1080,
                                RESOLUTIONTEXT_RECT.h*SC_HEIGHT/1080
                            };
    //  Button "1920x1080"
    resolution_button_rect =    {
                                    resolution_text_rect.x + resolution_text_rect.w - 30*SC_HEIGHT/1080 - RESOLUTIONBUTTON_RECT.w*SC_HEIGHT/1080,
                                    resolution_text_rect.y + (resolution_text_rect.h - (RESOLUTIONBUTTON_RECT.h+5)*SC_HEIGHT/1080)/2,
                                    RESOLUTIONBUTTON_RECT.w*SC_HEIGHT/1080,
                                    RESOLUTIONBUTTON_RECT.h*SC_HEIGHT/1080
                                };
    mute_button_rect =  {
                            SC_HEIGHT/5,
                            resolution_text_rect.y + resolution_text_rect.h + 20*SC_HEIGHT/1080,
                            417*SC_HEIGHT/1080,
                            108*SC_HEIGHT/1080
                        };
    back_button_rect =  {
                            (SC_WIDTH - 600*SC_HEIGHT/1080)/2,
                            mute_button_rect.y + 400*SC_HEIGHT/1080,
                            600*SC_HEIGHT/1080,
                            100*SC_HEIGHT/1080
                        };

}

void SettingMenuFunc::InitButton(SDL_Renderer *&renderer){
    const int SC_WIDTH = GetScWidth();
    const int SC_HEIGHT = GetScHeight();
    bool mute = GetMute();
    //  Độ phần giải
    std::string current_resolution = std::to_string(SC_WIDTH) + "x" + std::to_string(SC_HEIGHT);
    resolution_button.rect = resolution_button_rect,
    resolution_button.texture_focus = LoadImg(current_resolution+ ".png", renderer);
    resolution_button.texture_normal = LoadImg(current_resolution + ".png", renderer);

    //  Tắt tiếng
    mute_button.rect = mute_button_rect;
    if (!mute)
    {
        mute_button.texture_focus = LoadImg("mute_no.png", renderer);
        mute_button.texture_normal = LoadImg("mute_no.png", renderer);
    } else
    {
        mute_button.texture_focus = LoadImg("mute_yes.png", renderer);
        mute_button.texture_normal = LoadImg("mute_yes.png", renderer);
    }

    //  Quay lại
    back_button.rect = back_button_rect;
    back_button.texture_focus = LoadImg("back.png", renderer);
    back_button.texture_normal = LoadImg("back.png", renderer);
}

void SettingMenu(std::string &main_state, SDL_Renderer *&renderer){
    ////////////////////////////////////////////////////
    //  Menu cài đặt
    ////////////////////////////////////////////////////
    const int SC_WIDTH = GetScWidth();
    const int SC_HEIGHT = GetScHeight();
    bool *mute = GetMuteReference();

    SettingMenuFunc::SetRect();
    SettingMenuFunc::InitButton(renderer);

    //  Lưu lại cửa sổ cũ
    SDL_Surface *old_surface = SDL_CreateRGBSurface(0, SC_WIDTH, SC_HEIGHT, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, old_surface->pixels, old_surface->pitch);

    DrawBackground(renderer);

    //  In ra chữ Độ phân giải
    SDL_Texture *resolution_texture = LoadImg("resolution.png", renderer);
    SDL_RenderCopy(renderer, resolution_texture, NULL, &resolution_text_rect);

    //  Vẽ các Button
    resolution_button.Draw(renderer);
    mute_button.Draw(renderer);
    back_button.Draw(renderer);

    bool quit = false;
    while(CheckQuitCurrent(quit, main_state) == false)
    {
        if (SDL_WaitEventTimeout(&g_event,10) != 0 )
        {
            switch (g_event.type)
            {
                case SDL_QUIT: main_state = MAIN_EXIT; break;

                //  Khi di chuột vào các tùy chọn
                case SDL_MOUSEMOTION:
                {
                    mute_button.Focus(renderer);
                    resolution_button.Focus(renderer);
                    back_button.Focus(renderer);
                    break;
                }

                //  Khi nhấn vào các tùy chọn
                case SDL_MOUSEBUTTONDOWN:
                {
                    //  Quay về
                    if (back_button.Click())
                        quit = true;
                    //  Tắt tiếng
                    else if (mute_button.Click())
                    {
                        //  Đổi hình ảnh hiển thị
                        if (*mute)
                        {
                            *mute = false;
                            mute_button.texture_focus = LoadImg("mute_no.png", renderer);
                            mute_button.texture_normal = LoadImg("mute_no.png", renderer);
                        }
                        else
                        {
                            *mute = true;
                            mute_button.texture_focus = LoadImg("mute_yes.png", renderer);
                            mute_button.texture_normal = LoadImg("mute_yes.png", renderer);
                        }
                        mute_button.Draw(renderer);
                    }
                    //  Độ phân giải
                    else if (resolution_button.Click())
                    {
                        ResolutionSetting(main_state, renderer);
                    }
                    break;
                }
            }
        }
        SDL_RenderPresent(renderer);
    }

    //  Trả lại màn hình cũ
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, old_surface);
    ApplyTexture(texture, renderer, {0, 0, SC_WIDTH, SC_HEIGHT});
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(old_surface);
}


//  Chỉnh độ phân giải
void ResolutionSettingFunc::SetRect(){
    const int SC_WIDTH = GetScWidth();
    const int SC_HEIGHT = GetScHeight();
     //  Thông báo xác nhận
    resolutionapply_note.rect = {
                                (SC_WIDTH - 600*SC_HEIGHT/1080)/2,
                                (SC_HEIGHT - 200*SC_HEIGHT/1080)/2,
                                RESOLUTIONAPPLY_RECT.w*SC_HEIGHT/1080,
                                RESOLUTIONAPPLY_RECT.h*SC_HEIGHT/1080
                            };
    //  Đồng ý
    resolution_yes_rect =   {
                                resolutionapply_note.rect.x,
                                resolutionapply_note.rect.y + resolutionapply_note.rect.h + 10*SC_HEIGHT/1080,
                                RESOLUTIONAPPLY_BUTTON.w*SC_HEIGHT/1080,
                                RESOLUTIONAPPLY_BUTTON.h*SC_HEIGHT/1080
                            };
    //  Hủy
    resolution_no_rect =    {
                                resolution_yes_rect.x + 600*SC_HEIGHT/1080 - 290*2*SC_HEIGHT/1080 + resolution_yes_rect.w,
                                resolution_yes_rect.y,
                                RESOLUTIONAPPLY_BUTTON.w*SC_HEIGHT/1080,
                                RESOLUTIONAPPLY_BUTTON.h*SC_HEIGHT/1080
                            };
}

void ResolutionSettingFunc::InitButton(SDL_Renderer *&renderer){
    for (int i = 0; i < SC_RESOLUTION; i++){
        //  Tạo vị trí, kích thước và load ảnh
        std::string resolution = std::to_string(WIDTH[i]) + "x" + std::to_string(HEIGHT[i]);
        res_button[i].rect =    {
                                     resolution_button_rect.x,
                                     resolution_button_rect.y + i*resolution_button_rect.h,
                                     resolution_button_rect.w,
                                     resolution_button_rect.h
                                };
        res_button[i].texture_normal = LoadImg(resolution+".png", renderer),
        res_button[i].texture_focus = LoadImg(resolution+".png", renderer),
        res_button[i].Draw(renderer);
    }
}

void ResolutionSetting(std::string &main_state, SDL_Renderer *&renderer){
    int *SC_WIDTH = GetScWidthReference();
    int *SC_HEIGHT = GetScHeightReference();
    //  Lưu lại màn hình cũ
    SDL_Surface *old_surface = SDL_CreateRGBSurface(0, *SC_WIDTH, *SC_HEIGHT, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, old_surface->pixels, old_surface->pitch);

    ResolutionSettingFunc::SetRect();
    ResolutionSettingFunc::InitButton(renderer);

    bool quit = false;
    while(CheckQuitCurrent(quit, main_state) == false){
        if (SDL_WaitEventTimeout(&g_event,10) != 0)
        {
            switch (g_event.type)
            {
                case SDL_QUIT:
                    main_state = MAIN_EXIT;
                    break;

                //  Khi di chuột qua
                case SDL_MOUSEMOTION:
                    for (int i = 0; i < SC_RESOLUTION; i++)
                        res_button[i].Focus(renderer);
                    break;

                //  Khi nhấn chuột
                case SDL_MOUSEBUTTONDOWN:
                    for (int i = 0; i < SC_RESOLUTION; i++)
                    {
                        if (res_button[i].Click())
                        {
                            if (ResolutionSettingFunc::AskResolutionApply(main_state, renderer) == false) break;
                            *SC_HEIGHT = HEIGHT[i];
                            *SC_WIDTH = WIDTH[i];
                            main_state = MAIN_RESTART;
                        }
                    }
                    quit = true;
                    break;
            }
        }
        SDL_RenderPresent(renderer);
    }

    //  Trả lại màn hình cũ
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, old_surface);
    ApplyTexture(texture, renderer, {0, 0, *SC_WIDTH, *SC_HEIGHT});

    //  Xóa các con trỏ
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(old_surface);
}

bool ResolutionSettingFunc::AskResolutionApply(std::string &main_state, SDL_Renderer *&renderer){
    ///////////////////////////////////////////////////////////
    //  Hiện hộp thoại xác nhận khi người chơi muốn thay đổi độ phân giải màn hình
    ///////////////////////////////////////////////////////////
    SDL_Surface *old_surface = SDL_CreateRGBSurface(0, GetScWidth(), GetScHeight(), 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, old_surface->pixels, old_surface->pitch);

    BlurScreen(GetScWidth(), GetScHeight(), renderer);

    //  Viết thông báo
    resolutionapply_note.LoadFile("resolution_accept.png", renderer);
    resolutionapply_note.Draw(renderer);

    ButtonObject yes_button;
    yes_button.rect = resolution_yes_rect;
    yes_button.texture_normal = LoadImg("resolution_yes.png", renderer);
    yes_button.texture_focus = LoadImg("resolution_yes.png", renderer);

    ButtonObject no_button;
    no_button.rect = resolution_no_rect;
    no_button.texture_focus = LoadImg("resolution_no.png", renderer);
    no_button.texture_normal = LoadImg("resolution_no.png", renderer);

    yes_button.Draw(renderer);
    no_button.Draw(renderer);

    bool quit = false;
    while (CheckQuitCurrent(quit, main_state) == false)
    {
        if (SDL_WaitEvent(&g_event) != 0)
        {
            switch(g_event.type)
            {
                case SDL_QUIT:
                    main_state = MAIN_EXIT;
                    break;

                //  Khi di chuột vào button
                case SDL_MOUSEMOTION:
                    yes_button.Focus(renderer);
                    no_button.Focus(renderer);
                    break;

                // Khi nhấn chuột
                case SDL_MOUSEBUTTONDOWN:
                    if (yes_button.Click())
                        return true;
                    quit = true;
                    break;
            }
        }
        SDL_RenderPresent(renderer);
    }

    //  Trả lại màn hình cũ
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, old_surface);
    ApplyTexture(texture, renderer, {0, 0, GetScWidth(), GetScHeight()});

    //  Xóa các con trỏ
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(old_surface);
    return false;
}
