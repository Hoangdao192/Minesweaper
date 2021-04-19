#include "CustomDifficulty.h"

ImgObject customdiff_background;

ButtonObject rowinput_button;
ButtonObject colinput_button;
ButtonObject bominput_button;
ButtonObject helpinput_button;
ButtonObject yes_button;
ButtonObject no_button;

GameSet custom_difficulty;

void GetTextInput(TextObject &text, const int MAX_CHAR, SDL_Rect &rect, SDL_Texture *&texture, SDL_Renderer *&renderer){
    const int SC_HEIGHT = GetScHeight();
    ///////////////////////////////////////////////
    //  Hàm lấy văn bản nhập vào
    //  Hàm thực hiện:
    //      1.  Vẽ nền đè để xóa chuỗi input cũ
    //      2.  Lấy kí tự vừa nhập
    //      3.  Cộng kí tự vào chuỗi input
    //      4.  Viết ra chuỗi input mới
    //      5.  Quay lại bước 1
    ///////////////////////////////////////////////
    text.SetColor(80,80,0);
    text.SetFont("Font_menu.ttf", 50*SC_HEIGHT/1080);
    text.SetRect(rect.x+20, rect.y+20);

    SDL_Color color = {80,80,0,0};
    bool quit = false;
    while (!quit){
        if (SDL_WaitEvent(&g_event) != 0)
        {
            switch (g_event.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;

                //  Thoát nhập văn bản
                case SDL_MOUSEBUTTONDOWN:
                    if (CheckMouse(rect) == false){
                        if (text.text_.size() == 0) text.text_ = " ";
                        if (text.text_.back() == '_') text.text_.pop_back();
                        SDL_RenderCopy(renderer, texture, NULL, &rect);
                        text.Draw(renderer);
                        quit = true;
                        continue;
                    }
                    break;

                //  Backspace
                case SDL_KEYDOWN:
                    if (g_event.key.keysym.sym == SDLK_BACKSPACE && text.text_.size() > 1)
                    {
                        text.text_.pop_back();
                        text.text_.pop_back();
                    }
                    break;

                //  Nhập văn bản
                case SDL_TEXTINPUT:
                    //  Lấy chuỗi đã nhập
                    std::string text_input = g_event.text.text;
                    //  Xóa kí tự không phải số
                    for (int i = 0; i < text_input.size(); ++i)
                        if (text_input[i] < '0' || text_input[i] > '9') text_input.erase(i,1);
                    //  Thêm kí tự vào cuối chuỗi input
                    if (text.text_.size() < MAX_CHAR)
                    {
                        if (text.text_.back() == '_') text.text_.pop_back();
                        text.text_ += text_input;
                    }
                    break;
            }
            //  Vẽ chuỗi đã nhập
            if (text.text_.size() == 0) text.text_ = " ";
            SDL_RenderCopy(renderer, texture, NULL, &rect);
            //  Thêm dấu '_' để đánh dấu đang nhập văn bản
            if (text.text_.back() != '_')
                text.text_.push_back('_');
            text.Draw(renderer);
        }
    }
}
//  Độ khó tùy chỉnh
void CustomDiffFunc::SetRect(){
    const int SC_WIDTH = GetScWidth();
    const int SC_HEIGHT = GetScHeight();
    //  Nền
    customdiff_background.rect =    {
                                        (SC_WIDTH - CUSTOMDIFF_BACKGROUND.w*SC_HEIGHT/1080)/2,
                                        (SC_HEIGHT - CUSTOMDIFF_BACKGROUND.h*SC_HEIGHT/1080)/2,
                                        CUSTOMDIFF_BACKGROUND.w*SC_HEIGHT/1080,
                                        CUSTOMDIFF_BACKGROUND.h*SC_HEIGHT/1080
                                    };

    rowinput_button.rect =  {
                                customdiff_background.rect.x + 50*SC_HEIGHT/1080,
                                customdiff_background.rect.y + 85*SC_HEIGHT/1080,
                                300*SC_HEIGHT/1080,
                                100*SC_HEIGHT/1080
                            };

    colinput_button.rect =  {
                                customdiff_background.rect.x + 420*SC_HEIGHT/1080,
                                customdiff_background.rect.y + 85*SC_HEIGHT/1080,
                                300*SC_HEIGHT/1080,
                                100*SC_HEIGHT/1080
                            };

    bominput_button.rect =  {
                                customdiff_background.rect.x + 120*SC_HEIGHT/1080,
                                rowinput_button.rect.y + rowinput_button.rect.h + 35*SC_HEIGHT/1080,
                                200*SC_HEIGHT/1080,
                                100*SC_HEIGHT/1080
                            };
    helpinput_button.rect = {
                                colinput_button.rect.x,
                                bominput_button.rect.y,
                                200*SC_HEIGHT/1080,
                                100*SC_HEIGHT/1080
                            };

    yes_button.rect =   {
                            customdiff_background.rect.x,
                            customdiff_background.rect.y + customdiff_background.rect.h + 5*SC_HEIGHT/1080,
                            100*SC_HEIGHT/1080,
                            100*SC_HEIGHT/1080
                        };

    no_button.rect =    {
                            customdiff_background.rect.x + 110*SC_HEIGHT/1080,
                            customdiff_background.rect.y + customdiff_background.rect.h + 5*SC_HEIGHT/1080,
                            100*SC_HEIGHT/1080,
                            100*SC_HEIGHT/1080
                        };

}

void CustomDiffFunc::LoadMedia(SDL_Renderer *&renderer){
    const int SC_HEIGHT = GetScHeight();
    //  Ô nhập số hàng
    rowinput_button.texture_focus = LoadImg("custom_input.png", renderer);
    rowinput_button.texture_normal = LoadImg("custom_input.png", renderer);

    //  Ô nhập số cột
    colinput_button.texture_focus = LoadImg("custom_input.png", renderer);
    colinput_button.texture_normal = LoadImg("custom_input.png", renderer);

    //  Ô nhập số bom
    bominput_button.texture_normal = LoadImg("custom_input2.png", renderer);
    bominput_button.texture_focus = LoadImg("custom_input2.png", renderer);

    helpinput_button.texture_focus = LoadImg("custom_input2.png", renderer);
    helpinput_button.texture_normal = LoadImg("custom_input2.png", renderer);

    //  Đồng ý
    yes_button.texture_normal = LoadImg("yes.png", renderer);
    yes_button.texture_focus = LoadImg("yes.png", renderer);

    //  Hủy bỏ
    no_button.texture_normal = LoadImg("no.png", renderer);
    no_button.texture_focus = LoadImg("no.png", renderer);

    customdiff_background.LoadFile("custom_background.png", renderer);
}

GameSet CustomDifficulty(std::string &main_state, SDL_Renderer *&renderer){
    const int SC_WIDTH = GetScWidth();
    const int SC_HEIGHT = GetScHeight();

    CustomDiffFunc::SetRect();
    CustomDiffFunc::LoadMedia(renderer);

    //  Lưu lại màn hình
    SDL_Surface *old_surface = SDL_CreateRGBSurface(0, SC_WIDTH, SC_HEIGHT, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, old_surface->pixels, old_surface->pitch);
    BlurScreen(SC_WIDTH, SC_HEIGHT, renderer);

    //  Nền
    customdiff_background.Draw(renderer);

    TextObject row_text("ROW","Font_menu.ttf", 50*SC_HEIGHT/1080, 80,80,0);
    TextObject col_text("COL","Font_menu.ttf", 50*SC_HEIGHT/1080, 80,80,0);
    TextObject bom_text("BOM","Font_menu.ttf", 50*SC_HEIGHT/1080, 80,80,0);
    TextObject help_text("HELP", "Font_menu.ttf", 50*SC_HEIGHT/1080, 80,80,0);

    row_text.SetRect(rowinput_button.rect.x, customdiff_background.rect.y + 25*SC_HEIGHT/1080);
    col_text.SetRect(colinput_button.rect.x, customdiff_background.rect.y + 25*SC_HEIGHT/1080);
    bom_text.SetRect(customdiff_background.rect.x + 30*SC_HEIGHT/1080, bominput_button.rect.y + 10*SC_HEIGHT/1080);
    help_text.SetRect(helpinput_button.rect.x+helpinput_button.rect.w + 30*SC_HEIGHT/1080, helpinput_button.rect.y + 10*SC_HEIGHT/1080);

    rowinput_button.Draw(renderer);
    colinput_button.Draw(renderer);
    bominput_button.Draw(renderer);
    helpinput_button.Draw(renderer);
    yes_button.Draw(renderer);
    no_button.Draw(renderer);
    row_text.Draw(renderer);
    col_text.Draw(renderer);
    bom_text.Draw(renderer);
    help_text.Draw(renderer);

    //  Chuỗi người dùng nhập vào
    TextObject rowinput_text(" ", "Font_menu.ttf", 40*SC_HEIGHT/1080, 80,80,0);
    TextObject colinput_text(" ", "Font_menu.ttf", 40*SC_HEIGHT/1080, 80,80,0);
    TextObject bominput_text(" ", "Font_menu.ttf", 40*SC_HEIGHT/1080, 80,80,0);
    TextObject helpinput_text(" ", "Font_menu.ttf", 40*SC_HEIGHT/1080, 80,80,0);
    //  Rect
    SDL_Surface *surface = GetTextSurface("0", "Font_menu.ttf", 40*SC_HEIGHT/1080, background_color);
    rowinput_text.SetRect(rowinput_button.rect.x, rowinput_button.rect.y + (rowinput_button.rect.h - surface->h)/2);
    colinput_text.SetRect(colinput_button.rect.x, colinput_button.rect.y + (colinput_button.rect.h - surface->h)/2);
    bominput_text.SetRect(bominput_button.rect.x, bominput_button.rect.y + (bominput_button.rect.h - surface->h)/2);
    helpinput_text.SetRect(helpinput_button.rect.x, helpinput_button.rect.y + (helpinput_button.rect.h - surface->h)/2);
    SDL_FreeSurface(surface);

    bool quit = false;
    while (!CheckQuitCurrent(quit, main_state)){
        if (SDL_WaitEvent(&g_event))
            switch(g_event.type){
                case SDL_MOUSEMOTION:
                    yes_button.Focus(renderer);
                    no_button.Focus(renderer);
                    break;
                case SDL_QUIT: main_state = MAIN_EXIT; break;
                case SDL_MOUSEBUTTONDOWN:
                    if (rowinput_button.Click()) GetTextInput(rowinput_text, 4, rowinput_button.rect, rowinput_button.texture_normal, renderer);
                    if (colinput_button.Click()) GetTextInput(colinput_text, 4, colinput_button.rect, colinput_button.texture_normal, renderer);
                    if (bominput_button.Click()) GetTextInput(bominput_text, 6, bominput_button.rect, bominput_button.texture_normal, renderer);
                    if (helpinput_button.Click()) GetTextInput(helpinput_text, 5, helpinput_button.rect, helpinput_button.texture_normal, renderer);
                    if (yes_button.Click())
                    {
                        std::stringstream sstext1(rowinput_text.GetText()), sstext2(colinput_text.GetText()), sstext3(bominput_text.GetText());
                        std::stringstream sstext4(helpinput_text.GetText());
                        sstext1 >> custom_difficulty.board_row;
                        sstext2 >> custom_difficulty.board_col;
                        sstext3 >> custom_difficulty.bom;
                        sstext4 >> custom_difficulty.help_time;
                        if (CheckGameSet(renderer))
                            main_state = MAIN_NEWGAME;
                        else {
                            custom_difficulty = {10,10,10,15,2};
                            quit = true;
                        }
                    }
                    if (no_button.Click()){
                        quit = true;
                    }
                    break;
            }
    }

    // Xuất ra màn hình cũ
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, old_surface);
    ApplyTexture(texture, renderer, {0, 0, SC_WIDTH, SC_HEIGHT});
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(old_surface);

    custom_difficulty.count_down_time = 15;
    return custom_difficulty;
}

bool CheckGameSet(SDL_Renderer *&renderer){
    const int SC_WIDTH = GetScWidth();
    const int SC_HEIGHT = GetScHeight();
    bool check = true;
    if (custom_difficulty.board_row > 30) {
        custom_difficulty.board_row = 30;
        check = false;
    }
    if (custom_difficulty.board_col > 30) {
        custom_difficulty.board_col = 30;
        check = false;
    }
    if (custom_difficulty.board_col < 10) {
        custom_difficulty.board_col = 10;
        check = false;
    }
    if (custom_difficulty.board_row < 10) {
        custom_difficulty.board_row = 10;
        check = false;
    }
    if (custom_difficulty.bom > custom_difficulty.board_col*custom_difficulty.board_row - 20) {
        custom_difficulty.bom = custom_difficulty.board_col*custom_difficulty.board_row-20;
        check = false;
    }
    if (custom_difficulty.bom < 10) {
        custom_difficulty.bom = 10;
        check = false;
    }
    if (check) return true;

    SDL_Surface *old_surface = SDL_CreateRGBSurface(0, SC_WIDTH, SC_HEIGHT, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, old_surface->pixels, old_surface->pitch);

    BlurScreen(SC_WIDTH,SC_HEIGHT,renderer);

    SDL_Rect background_rect =  {
                                    (SC_WIDTH - 1000*SC_HEIGHT/1080)/2,
                                    (SC_HEIGHT - 333*SC_HEIGHT/1080)/2,
                                    1000*SC_HEIGHT/1080,
                                    333*SC_HEIGHT/1080
                                };

    SDL_Texture *note = LoadImg("difficulty_note.png", renderer);

    ButtonObject yes;
    yes.rect =  {
                    background_rect.x,
                    background_rect.y + background_rect.h + 10*SC_HEIGHT/1080,
                    100*SC_HEIGHT/1080,
                    100*SC_HEIGHT/1080
                };
    yes.texture_normal = LoadImg("yes.png", renderer);
    yes.texture_focus = LoadImg("yes.png", renderer);

    ButtonObject no;
    no.rect =   {
                    background_rect.x + 110*SC_HEIGHT/1080,
                    background_rect.y + background_rect.h+ 10*SC_HEIGHT/1080,
                    100*SC_HEIGHT/1080,
                    100*SC_HEIGHT/1080
                };
    no.texture_focus = LoadImg("no.png", renderer);
    no.texture_normal = LoadImg("no.png", renderer);

    SDL_RenderCopy(renderer, note, NULL, &background_rect);
    yes.Draw(renderer);
    no.Draw(renderer);

    bool quit = false;
    SDL_Event window_event;
    while (!quit){
        if (SDL_WaitEvent(&window_event) != 0){
            switch(window_event.type){
                case SDL_QUIT: exit(0);
                case SDL_MOUSEMOTION:
                    yes.Focus(renderer);
                    no.Focus(renderer);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (yes.Click()){
                        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, old_surface);
                        ApplyTexture(texture, renderer, {0,0,SC_WIDTH, SC_HEIGHT});
                        SDL_FreeSurface(old_surface);
                        SDL_DestroyTexture(texture);
                        return true;
                    }
                    if (no.Click()){
                        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, old_surface);
                        ApplyTexture(texture, renderer, {0,0,SC_WIDTH, SC_HEIGHT});
                        SDL_FreeSurface(old_surface);
                        SDL_DestroyTexture(texture);
                        return false;
                    }
                    break;
            }

        }
    }
}
