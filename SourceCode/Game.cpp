#include "Game.h"

//  Bảng các ô vuông
std::vector<std::vector<SquareObject>> minefield;
//  Kích thước 1 ô vuông
int square_size;
//  Số ô vuông trên 1 dòng hoặc 1 cột
int board_row = 10;
int board_col = 10;
//  Số bom
int bom = 10;
//  Thời gian đếm ngược
int count_down_time = 10;
//  Số lần trợ giúp
int help_time = 2;
//  Chế độ chơi
int game_mode = 0;
//  Tắt tiếng
bool game_mute;


TextObject flagremain_text;
TextObject time_text;
TextObject helptime_text;

//  Vị trí và kích thước của bảng
SDL_Rect game_board;
//  Lá cờ
SDL_Rect game_flagbutton_rect;
//  Số cờ còn lại
SDL_Rect game_numberflag_rect;
//  Đồng hồ
SDL_Rect game_clockbutton_rect;
//  Thời gian
SDL_Rect game_time_rect;
//  Trợ giúp
SDL_Rect game_helpbutton_rect;
//  Số lần trợ giúp
SDL_Rect game_helpremain_rect;
//  Cài đặt
SDL_Rect game_settingbutton_rect;
//  Màn hình Kết thúc game
SDL_Rect gameover_rect;
//  Nút chơi lại
SDL_Rect gameover_restart_rect;
//  Nút qua về menu
SDL_Rect gameover_backtomenu_rect;

//const int DIFSETTING_MAXBUTTON = 5;

std::vector<ButtonObject> game_button;

void MainGame::SetGameRect(){
    //////////////////////////////////////////////////////////////////////////////////
    //  Tính toán kích thước theo kích thước chuẩn : Game chạy ở màn hình cao 1080px
    //////////////////////////////////////////////////////////////////////////////////

    //  Kích thước ô vuông chuẩn là 90px: kích thước 1 ô vuông khi bảng có 100 ô vuông, độ phân giải game 1920x1080
    const int SC_WIDTH = GetScWidth();
    const int SC_HEIGHT = GetScHeight();

    font_size_0 = 300*SC_HEIGHT/1080;
    font_size_1 = 100*SC_HEIGHT/1080;
    font_size_2 = 100*SC_HEIGHT/1080;

    //  Tính toán kích thước của Bảng để vừa với màn hình
    int border_w = SC_WIDTH - 5*SC_HEIGHT/1080;
    int border_h = SC_HEIGHT - SC_HEIGHT*165/1080;
    if (board_row < board_col) square_size = border_h/board_row;
    else square_size = border_w/board_col;
    while(!(square_size*board_col <= border_w && square_size*board_row <= border_h))
        --square_size;

    //  Vị trí và kích thước của bảng
    game_board = {
                (SC_WIDTH - board_col*square_size)/2,
                SC_HEIGHT*160/1080,
                square_size*board_col,
                square_size*board_row
            };

    //  Kích thước và vị trí Lá cờ
    game_flagbutton_rect =      {
                                game_board.x,
                                game_board.y - 115*SC_HEIGHT/1080 -20*SC_HEIGHT/1080,
                                100*SC_HEIGHT/1080,
                                100*SC_HEIGHT/1080
                            };

    //  Lấy kích thước của chữ được vẽ ra
    SDL_Surface *surface = GetTextSurface(std::to_string(bom), "Font_menu.ttf", font_size_1, background_color);
    //  Kích thước và vị trí của Số cờ còn lại
    game_numberflag_rect =  {
                            game_flagbutton_rect.x + game_flagbutton_rect.w,
                            game_board.y - surface->h + 10*SC_HEIGHT/1080 - 20*SC_HEIGHT/1080,
                            surface->w,
                            surface->h - 20*SC_HEIGHT/1080
                        };
    SDL_FreeSurface(surface);

    //  Kích thước và vị trí vẽ Đồng hồ
    game_clockbutton_rect   =   {
                                game_board.x + 260*SC_HEIGHT/1080,
                                game_board.y - 115*SC_HEIGHT/1080-20*SC_HEIGHT/1080,
                                100*SC_HEIGHT/1080,
                                100*SC_HEIGHT/1080
                            };
    //  Lấy kích thước của chữ được vẽ ra
    surface = GetTextSurface("00:00", "Font_menu.ttf", font_size_1, background_color);
    //  Vị trí vẽ thời gian
    game_time_rect = {
                    game_clockbutton_rect.x + game_clockbutton_rect.w,
                    game_board.y - surface->h + 10*SC_HEIGHT/1080- 20*SC_HEIGHT/1080,
                    surface->w,
                    surface->h - 20*SC_HEIGHT/1080
                };
    SDL_FreeSurface(surface);

    //  Kích thước và vị trí vẽ Nút Cài đặt
    game_settingbutton_rect =   {
                                game_board.x + 780*SC_HEIGHT/1080,
                                game_board.y - 115*SC_HEIGHT/1080-20*SC_HEIGHT/1080,
                                100*SC_HEIGHT/1080,
                                100*SC_HEIGHT/1080
                            };

    //  Kích thước và vị trí màn hình kết thúc game
    gameover_rect =    {
                            (SC_WIDTH - 600*SC_HEIGHT/1080)/2,
                            (SC_HEIGHT - 200*SC_HEIGHT/1080)/2,
                            600*SC_HEIGHT/1080,
                            200*SC_HEIGHT/1080
                        };
    //  Chơi lại
    gameover_restart_rect =     {
                                    gameover_rect.x,
                                    gameover_rect.y + gameover_rect.h + 10*SC_HEIGHT/1080,
                                    290*SC_HEIGHT/1080,
                                    100*SC_HEIGHT/1080
                                };
    //  Quay về Menu
    gameover_backtomenu_rect =  {
                                    gameover_rect.x + gameover_restart_rect.w + 20*SC_HEIGHT/1080,
                                    gameover_rect.y + gameover_rect.h + 10*SC_HEIGHT/1080,
                                    290*SC_HEIGHT/1080,
                                    100*SC_HEIGHT/1080
                                };

    //  Trợ giúp
    game_helpbutton_rect =  {
                            game_time_rect.x + game_time_rect.w + 20*SC_HEIGHT/1080,
                            game_settingbutton_rect.y,
                            game_settingbutton_rect.w,
                            game_settingbutton_rect.h
                        };

    //  Số lần trợ giúp còn lại
    surface = GetTextSurface(std::to_string(help_time), "Font_menu.ttf", font_size_1, background_color);
    game_helpremain_rect =   {
                            game_helpbutton_rect.x + game_helpbutton_rect.w + 10*SC_HEIGHT/1080,
                            game_helpbutton_rect.y + 10*SC_HEIGHT/1080,
                            surface->w,
                            surface->h - 20*SC_HEIGHT/1080
                        };
    SDL_FreeSurface(surface);
}

void MainGame::InitButton(SDL_Renderer *&renderer){
    /////////////////////////
    //  Khởi tạo các Button
    /////////////////////////
    game_button.resize(4);
    for (int i = 0; i < 4; ++i)
    {
        game_button[i].texture_focus = LoadImg("game_button" + std::to_string(i)+".png", renderer);
        game_button[i].texture_normal = LoadImg("game_button" + std::to_string(i)+".png", renderer);
    }

    //  Lá cờ
    game_button[0].rect = game_flagbutton_rect;
    //  Đồng hồ
    game_button[1].rect = game_clockbutton_rect;
    //  Cài đặt
    game_button[2].rect = game_helpbutton_rect;
    //  Trợ giúp
    game_button[3].rect = game_settingbutton_rect;

    //Load ảnh
    square_normal1 = LoadImg("square1.png", renderer);
    square_normal2 = LoadImg("square2.png", renderer);
    square_open1 = LoadImg("square_open1.png", renderer);
    square_open2 = LoadImg("square_open2.png", renderer);
    bom1 = LoadImg("bom1.png", renderer);
    bom2 = LoadImg("bom2.png", renderer);
    flag1 = LoadImg("flag1.png", renderer);
    flag2 = LoadImg("flag2.png", renderer);
}

void MainGame::CreateText(){
    flagremain_text.SetColor(255,255,255);
    flagremain_text.SetFont("Font_menu.ttf", font_size_1);
    flagremain_text.SetRect(game_numberflag_rect.x, game_numberflag_rect.y);

    time_text.SetColor(255,255,255);
    time_text.SetFont("Font_menu.ttf", font_size_1);
    time_text.SetRect(game_time_rect.x, game_time_rect.y);

    helptime_text.SetColor(255,255,255);
    helptime_text.SetFont("Font_menu.ttf", font_size_1);
    helptime_text.SetRect(game_helpremain_rect.x, game_helpremain_rect.y);
}

void NewGame(std::string &main_state, SDL_Renderer *&renderer){
    ////////////////////////////////////////////
    //  Khởi tạo một game mới theo kiểu chơi đã chọn
    ////////////////////////////////////////////

    GameSet game_difficulty = GetDifficulty();
    game_mode = GetGameMode();
    board_row = game_difficulty.board_row;
    board_col = game_difficulty.board_col;
    bom = game_difficulty.bom;
    count_down_time = game_difficulty.count_down_time;
    help_time = game_difficulty.help_time;

    //  Game đang diễn ra
    main_state = MAIN_HAPPEN;
    //  Tính toán kích thước và load ảnh
    MainGame::SetGameRect();
    //  Khởi tạo các Button
    MainGame::InitButton(renderer);
    MainGame::CreateText();

    //  Khởi chạy game theo chế độ chơi
    switch(game_mode){
        case 0: NewGameClassic(main_state, renderer); break;
        case 1: NewGameCountDown(main_state, renderer); break;
    }
}

void NewGameCountDown(std::string &main_state, SDL_Renderer *&renderer){
    //////////////////////////////////////////////////
    //  Kiểu chơi Đếm ngược
    //////////////////////////////////////////////////
    SDL_RenderClear(renderer);
    //  Số ô đã mở
    int open_square = 0;
    //  Số cờ còn lại
    int flag_remain = bom;
    //  Số lần trợ giúp còn lại
    int help_remain = help_time;

    //  Khởi tạo các ô vuông
    InitSquareValue();

    //  Vẽ nền
    DrawBackground(renderer);

    //  Vẽ các Nút bấm
    for (int i = 0; i < 4; ++i)
        game_button[i].Draw(renderer);

    // Vẽ số cờ ban đầu
    DrawFlagRemain(flag_remain, renderer);

    // Vẽ thời gian ban đầu 00:00
    DrawTime(0, renderer);

    // Vẽ số lần trợ giúp ban đầu
    SDL_Color color = {255,255,255,0};
    DrawSquare(game_helpremain_rect, background_color, renderer);
    PrintText(std::to_string(help_remain), "Font_menu.ttf", font_size_1, color, game_helpremain_rect.x, game_helpremain_rect.y, renderer);

    //  Vẽ bảng ô vuông
    DrawBoard(renderer);

    //////////////////////////////////////////////////////////////////////////////////////////////
    //  Đánh dấu lần mở ô đầu tiên, dùng để khởi tạo một vài thành phần
    //  Khi người chơi mở 1 ô đầu tiên, thực hiện:
    //      1.  Khởi tạo ngẫu nhiên vị trí các quả bom (trừ khu vực xung quanh ô đầu tiên được mở)
    //      2.  Bắt đầu tính thời gian chơi
    //////////////////////////////////////////////////////////////////////////////////////////////
    bool first_click = false;
    int time_available = count_down_time;
    int startime, currtime ;

    //  Vòng lặp chính
    int old_row = 0;
    int old_col = 0;
    SDL_Event window_event;
    bool quit = false;
    while (CheckQuitCurrent(quit, main_state) == false){
        if (SDL_WaitEventTimeout(&window_event, 10) != 0)
            switch(window_event.type)
            {
                //  Thoát game
                case SDL_QUIT:
                    main_state = MAIN_EXIT;
                    break;

                //  Khi di chuột
                case SDL_MOUSEMOTION:
                    //  Focus ô vuông
                    if (IsMouseInBoard())
                    {
                        //  Unfocus
                        if (!minefield[old_row][old_col].is_open)
                            minefield[old_row][old_col].Draw(renderer);
                        int row, col;
                        GetCoordMinefield(row, col);
                        //  Focus
                        if (!minefield[row][col].is_open)
                            minefield[row][col].Focus(renderer);
                        old_row = row;
                        old_col = col;
                    }
                    //  Focus button
                    game_button[3].Focus(renderer);
                    game_button[2].Focus(renderer);
                    break;

                //  Khi nhấn chuột
                case SDL_MOUSEBUTTONDOWN:
                {
                    //  Nhấn chuột trái (mở ô)
                    if (window_event.button.button == SDL_BUTTON_LEFT)
                    {
                        if (IsMouseInBoard())
                        {
                            int row, col;
                            GetCoordMinefield(row, col);
                            //  Khi mở 1 ô đầu tiên
                            if (!first_click){
                                //  Đặt bộ đếm thời gián
                                startime = time(0);
                                currtime = (int) time(0);

                                first_click = true;
                                //  Sinh bom ngẫu nhiên
                                SetBom(row,col,renderer);
                            }

                            //  Mở 1 vùng khi bấm vào ô trống (ô không có bom xung quanh)
                            if (minefield[row][col].point == 0){
                                time_available = count_down_time;
                                 PlayMusic("first_open.mp3");
                                OpenField(row,col,open_square, renderer);
                            }

                            //  Mở 1 ô bình thường (ô có bom xung quanh)
                            else if (minefield[row][col].point > 0 && minefield[row][col].point < 9)
                            {
                                time_available = count_down_time;
                                PlayMusic("open.mp3");
                                OpenSquareNormal(row,col, open_square, renderer);
                            }

                            //  Mở 1 ô có bom
                            else if (minefield[row][col].point == 9)
                            {
                                DrawAllBom(renderer);
                                GameOver(main_state, false, renderer);
                                quit = true;
                            }
                        }
                        else
                        {
                            //  Bấm vào nút Cài đặt
                            if (game_button[3].Click())
                            {
                                startime = (int) time(0) - (currtime - startime);
                                QuickSettingMenu(main_state, renderer);
                            }
                            else if (game_button[2].Click() && help_remain > 0 && first_click)
                            {
                                time_available = count_down_time;
                                --help_remain;
                                GameHelp(open_square, help_remain, renderer);
                            }
                        }
                    }

                    //  Nhấn chuột phải (Đặt cờ, xóa cờ)
                    else if (window_event.button.button == SDL_BUTTON_RIGHT)
                        if (IsMouseInBoard())
                        {
                            //  Lấy vị trí hàng và cột của ô được mở
                            int row, col;
                            GetCoordMinefield(row, col);
                            //  Ô chưa được mở
                            if (minefield[row][col].is_open == false)
                            {
                                //  Ô chưa đặt cờ và số cờ > 0
                                if (minefield[row][col].set_flag == false && flag_remain > 0 && first_click)
                                    {
                                        --flag_remain;
                                        minefield[row][col].SetFlag(renderer);
                                    }
                                else minefield[row][col].DeleteFlag(renderer);
                            }

                        }
                }
            }
        if (time_available == 0){
            GameOver(main_state, false, renderer);
            quit = true;
        }
        //  Người chơi thắng cuộc khi mở hết các ô không có bom
        if (open_square == board_col*board_row - bom)
        {
            GameOver(main_state, true, renderer);
            break;
        }

        //  Bắt đầu tính thời gian khi mở ô lần đầu, hiển thị thời gian
        if (first_click && (int)time(0) - currtime > 0)
        {
            --time_available;
            currtime = (int) time (0);
            DrawTime(time_available, renderer);
        }

        SDL_RenderPresent(renderer);
    }
}

void NewGameClassic(std::string &main_state, SDL_Renderer *&renderer){
    ///////////////////////////////
    //  Kiểu chơi cổ điển
    ///////////////////////////////
    //  Game đang diễn ra
    main_state = MAIN_HAPPEN;

    SDL_RenderClear(renderer);

    //  Số ô vuông đã mở
    int open_square = 0;
    //  Số cờ còn lại
    int flag_remain = bom;
    //  Số lần giúp đỡ
    int help_remain = help_time;

    //  Khởi tạo các ô vuông
    InitSquareValue();

    DrawBackground(renderer);

    //  Vẽ các Nút bấm
    //  0: Cờ
    //  1: Đồng hồ
    //  2: Trợ giúp
    //  3: Cài đặt
    for (int i = 0; i < 4; ++i)
        game_button[i].Draw(renderer);

    // Vẽ số cờ ban đầu
    DrawFlagRemain(flag_remain, renderer);

    // Vẽ thời gian ban đầu 00:00
    DrawTime(0, renderer);

    //  Vẽ số lần trợ giúp ban đầu
    DrawSquare(helptime_text.GetRect(), background_color, renderer);
    helptime_text.SetText(std::to_string(help_remain));
    helptime_text.Draw(renderer);

    //  Vẽ bảng ô vuông
    DrawBoard(renderer);

    //////////////////////////////////////////////////////////////////////////////////////////////
    //  Đánh dấu lần mở ô đầu tiên
    //  Khi người chơi mở 1 ô đầu tiên, thực hiện:
    //      1.  Khởi tạo ngẫu nhiên vị trí các quả bom (trừ khu vực xung quanh ô đầu tiên được mở)
    //      2.  Bắt đầu tính thời gian chơi
    //////////////////////////////////////////////////////////////////////////////////////////////
    bool first_click = false;

    //  Thời gian chơi
    int startime, currtime;

    //  Vòng lặp chính
    int old_row = 0;
    int old_col = 0;
    SDL_Event window_event;
    bool quit = false;
    while (CheckQuitCurrent(quit, main_state) == false)
    {
        if (SDL_WaitEventTimeout(&window_event, 10) != 0)
        switch(window_event.type)
        {
            //  Thoát game
            case SDL_QUIT:
            {
                main_state = MAIN_EXIT;
                break;
            }

            //  Khi di chuột
            case SDL_MOUSEMOTION:
                    //  Focus ô vuông
                    if (IsMouseInBoard())
                    {
                        //  Unfocus
                        if (!minefield[old_row][old_col].is_open){
                            minefield[old_row][old_col].Draw(renderer);
                        }
                        int row, col;
                        GetCoordMinefield(row, col);
                        //  Focus
                        if (!minefield[row][col].is_open)
                            minefield[row][col].Focus(renderer);
                        old_row = row;
                        old_col = col;
                    }
                    //  Focus button
                    game_button[3].Focus(renderer);
                    game_button[2].Focus(renderer);
                    break;

            //  Khi nhấn chuột
            case SDL_MOUSEBUTTONDOWN:
            {
                //  Nhấn chuột trái (mở ô)
                if (window_event.button.button == SDL_BUTTON_LEFT)
                {
                    if (IsMouseInBoard())
                    {
                        int row, col;
                        GetCoordMinefield(row, col);

                        //  Khi mở 1 ô đầu tiên
                        if (!first_click){
                            //  Đặt bộ đếm thời gian
                            startime = time(0);
                            currtime = (int) time(0);

                            first_click = true;
                            //  Sinh bom ngẫu nhiên
                            SetBom(row,col,renderer);
                        }

                        //  Mở 1 vùng khi bấm vào ô trống (ô không có bom xung quanh)
                        if (minefield[row][col].point == 0)
                        {
                            PlayMusic("first_open.mp3");
                            OpenField(row,col,open_square, renderer);
                        }

                        //  Mở 1 ô bình thường (ô có bom xung quanh)
                        else if (minefield[row][col].point > 0 && minefield[row][col].point < 9)
                        {
                            PlayMusic("open.mp3");
                            OpenSquareNormal(row,col, open_square, renderer);
                        }

                        //  Mở 1 ô có bom
                        else if (minefield[row][col].point == 9 && !minefield[row][col].set_flag)
                        {
                            DrawAllBom(renderer);
                            GameOver(main_state, false, renderer);
                            quit = true;
                        }
                    }
                    else
                    {
                        //  Cài đặt
                        if (game_button[3].Click())
                        {
                            QuickSettingMenu(main_state, renderer);
                            startime = (int) time(0) - (currtime - startime);
                        }
                        else if (game_button[2].Click() && help_remain > 0 && first_click){
                            --help_remain;
                            GameHelp(open_square, help_remain, renderer);
                        }
                    }
                }

                //  Nhấn chuột phải (Đặt cờ, xóa cờ)
                else if (window_event.button.button == SDL_BUTTON_RIGHT)
                    if (IsMouseInBoard() == true)
                    {
                        //  Lấy vị trí hàng và cột của ô được mở
                        int row, col;
                        GetCoordMinefield(row, col);

                        if (!minefield[row][col].is_open)
                        {
                            if (!minefield[row][col].set_flag && flag_remain > 0 && first_click)
                                {
                                    --flag_remain;
                                    minefield[row][col].SetFlag(renderer);
                                    DrawFlagRemain(flag_remain, renderer);
                                }
                            else minefield[row][col].DeleteFlag(renderer);
                        }

                    }
            }
        }

        //  Người chơi chiến thắng khi mở hết các ô không có bom
        if (open_square == board_row*board_col-bom)
        {
            GameOver(main_state, true, renderer);
            break;
        }

        //  Bắt đầu tính thời gian khi mở ô lần đầu, hiển thị thời gian
        if (first_click && (int)time(0) - currtime > 0)
        {
            currtime = (int) time (0);
            DrawTime(currtime - startime, renderer);

        }
        SDL_RenderPresent(renderer);
    }
}

void GameHelp(int &open_square, const int &help_remain, SDL_Renderer *&renderer){
    //  Vẽ số lần trợ giúp còn lại
    DrawSquare(helptime_text.GetRect(), background_color, renderer);
    helptime_text.SetText(std::to_string(help_remain));
    helptime_text.Draw(renderer);

    //  Ưu tiên gọi ý ô trống trước
    for (int row = 0; row < board_row; ++row)
        for (int col = 0; col < board_col; ++col)
            if (minefield[row][col].point == 0 && !minefield[row][col].is_open && !minefield[row][col].set_flag)
            {
                OpenField(row, col, open_square, renderer);
                return;
            }
    //  Gợi ý ô bình thường
    for (int row = 0; row < board_row; ++row)
        for (int col = 0; col < board_col; ++col)
            if (minefield[row][col].point < 9 && !minefield[row][col].is_open && !minefield[row][col].set_flag)
            {
                OpenSquareNormal(row, col, open_square, renderer);
                return;
            }
}

void InitSquareValue(){
    /////////////////////////////////////
    //  Khởi tạo mảng 2 chiều các ô vuông
    /////////////////////////////////////
    //  Tạo mảng
    minefield.resize(board_row);
    for (int row = 0; row < board_row; ++row)
        minefield[row].resize(board_col);

    // Khởi tạo giá trị ban đầu cho từng ô vuông
    for (int row = 0; row < board_row; ++row)
        for (int col = 0; col < board_col; ++col){
            minefield[row][col].point = 0;
            minefield[row][col].set_flag = false;
            minefield[row][col].is_open = false;
            minefield[row][col].is_bom = false;
            minefield[row][col].rect =  {
                                            game_board.x + col*square_size,
                                            game_board.y + row*square_size,
                                            square_size,
                                            square_size
                                        };
            if ((row&1 && col&1) || (row%2 == 0 && col%2 == 0)){
                minefield[row][col].texture_normal = square_normal1;
                minefield[row][col].texture_open = square_open1;
                minefield[row][col].texture_flag = flag1;
            }
            else {
                minefield[row][col].texture_normal = square_normal2;
                minefield[row][col].texture_open = square_open2;
                minefield[row][col].texture_flag = flag2;
            }
        }
}

void DrawSquare(const SDL_Rect &rect, const SDL_Color &color, SDL_Renderer *&renderer){
    /////////////////////////////////////////
    //  Vẽ 1 hình chữ nhật với kích thước và màu đã cho
    /////////////////////////////////////////
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0);
    SDL_RenderFillRect(renderer, &rect);
}

void DrawBoard(SDL_Renderer *&renderer){
    /////////////////////////////////////////////
    //  Vẽ tất cả các ô vuông
    /////////////////////////////////////////////
    for (int row = 0; row < board_row; row++)
        for (int col = 0; col < board_col; col++)
            minefield[row][col].Draw(renderer);
    SDL_RenderPresent(renderer);

    //Đặt kích thước, màu và vẽ đường biên
    SDL_Rect boder_rect =   {
                                game_board.x - 3,
                                game_board.y - 3,
                                board_col*square_size + 6,
                                board_row*square_size + 6
                            };
    SDL_SetRenderDrawColor(renderer, 37,20,45,0);
    SDL_RenderDrawRect(renderer, &boder_rect);
}

void DrawFlagRemain(int flag_remain, SDL_Renderer *&renderer){
    ////////////////////////////////
    //  Vẽ số cờ còn lại
    ////////////////////////////////

    //Đặt màu
    SDL_Color color = {255,255,255,0};
    //  Vẽ nền chữ
    DrawSquare(flagremain_text.GetRect(), background_color, renderer);
    flagremain_text.SetText(std::to_string(flag_remain));
    flagremain_text.Draw(renderer);
    //PrintText(std::to_string(flag_remain), "Font_menu.ttf", font_size_1, color, game_numberflag_rect.x, game_numberflag_rect.y, renderer);
}

void DrawTime(int second, SDL_Renderer *&renderer){
    /////////////////////
    //  Vẽ thời gian
    /////////////////////
    std::string timer;

    int minute = second/60;
    second = second%60;

    //  Định dạng thời gian hiển thị
    if (minute < 10) timer = "0" + std::to_string(minute);
    else timer = std::to_string(minute);
    timer += ":";
    if (second < 10) timer += "0" + std::to_string(second);
    else timer += std::to_string(second);

    //  Hiển thị thời gian
    DrawSquare(time_text.GetRect(), background_color, renderer);
    time_text.SetText(timer);
    time_text.Draw(renderer);
    //PrintText(timer, "Font_menu.ttf", font_size_1, text_color_1, game_time_rect.x, game_time_rect.y, renderer);
}

void OpenField(int row, int col, int &open_square, SDL_Renderer *&renderer){
    //////////////////////////////////////////////////////////////////////
    //  Khi người chơi mở 1 ô trống, các ô nằm kề cạnh cũng được mở theo
    //  Nếu ô nằm kề cạnh cũng là 1 ô trống, tiếp tục mở các ô cạnh ô đó
    //////////////////////////////////////////////////////////////////////

    //  Nếu ô vuông không tồn tại hoặc đã được mở rồi hoặc được đặt cờ
    if (row < 0 || row >= board_row || col < 0 || col >= board_col
        || minefield[row][col].is_open || minefield[row][col].set_flag) return;

    //  Nếu ô vuông là ô thường và chưa được mở
    if (minefield[row][col].point > 0){
        OpenSquareNormal(row,col, open_square, renderer);
        return;
    }

    ////////////////////////////////////////////////////////
    //  Nếu ô vuông là ô trống, mở ô và mở các ô xung quanh
    ////////////////////////////////////////////////////////
    //  Mở ô hiện tại
    OpenSquareNormal(row, col, open_square, renderer);
    //  Mở ô bên phải
    OpenField(row,col+1, open_square, renderer);
    //  Mở ô bên trái
    OpenField(row,col-1, open_square,renderer);
    //  Mở ô bên trên
    OpenField(row-1,col, open_square, renderer);
    //  Mở ô bên dưới
    OpenField(row+1,col, open_square, renderer);
    //  Mở ô trái trên
    OpenField(row-1,col-1, open_square, renderer);
    //  Mở ô trái dưới
    OpenField(row+1,col-1, open_square, renderer);
    //  Mở góc phải trên
    OpenField(row+1,col+1, open_square, renderer);
    //  Mở ô phải dưới
    OpenField(row-1,col+1, open_square, renderer);
}

void OpenSquareNormal(int row, int col, int &open_square, SDL_Renderer *&renderer){
    //////////////////////////////////////////////////////
    //  Mở 1 ô bình thường ko có bom cũng ko phải ô trống
    //////////////////////////////////////////////////////
    if (minefield[row][col].is_open || minefield[row][col].set_flag) return;
    //  Số ô đã mở
    ++open_square;
    minefield[row][col].Open(renderer);
}

void DrawAllBom(SDL_Renderer *&renderer){
    //////////////////////////////////////////
    //  Vẽ tất cả bom
    //////////////////////////////////////////
    //  Hiện tất cả các ô là bom
    for (int row = 0; row < board_row; ++row)
        for (int col = 0; col < board_col; ++col)
            if (minefield[row][col].point >= 9) minefield[row][col].Open(renderer);
}

void GetCoordMinefield(int &row, int &col){
    ////////////////////////////////////////////
    //  Tính toán chỉ số hàng và chỉ số cột của ô vuông được nhấn chuột
    //      dựa vào vị trí con trỏ chuột và vị trí của bảng ô vuông
    ////////////////////////////////////////////
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    col = (mouse_x - game_board.x)/square_size;
    row = (mouse_y - game_board.y)/square_size;
    if (row >= board_row) row = board_row-1;
    if (col >= board_col) col = board_col-1;
}

bool IsMouseInBoard(){
    //////////////////////////////////////
    //  Kiểm tra con trỏ chuột có nằm trong Bảng các ô vuông hay không
    //////////////////////////////////////
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    if (mouse_x <= game_board.x || mouse_x > game_board.x+game_board.w) return false;
    else if (mouse_y <= game_board.y || mouse_y > game_board.y+game_board.h) return false;
    return true;
}

void SetBom(int no_row, int no_col, SDL_Renderer *&renderer){
    ////////////////////////////////
    //  Tạo bom ngẫu nhiên nhưng không được nằm kề ô minefield[no_row][no_col]
    //  (Tránh trường hợp người dùng mở trúng bom ngay ô đầu tiên)
    ////////////////////////////////
    srand((int) time(0));
    int row, col;
    for (int i = 0; i < bom; i++)
    {
        bool set_bom_ok = false;
        while (set_bom_ok == false)
        {
            row = rand()%board_row;
            col = rand()%board_col;

            if (minefield[row][col].point < 9
                && !(row >= no_row-1 && row <= no_row+1
                && col >= no_col-1 && col <= no_col+1))
            {
                minefield[row][col].SetBom(renderer);
                SetPoint(row, col);
                set_bom_ok = true;
            }
        }
    }
}

void SetPoint(int bom_row, int bom_col){
    ////////////////////////////////////
    //  Tính số bom xung quanh 1 ô
    //  (Điểm của các ô nằm cạnh ô có bom minefiel[bom_row][bom_col] sẽ tăng lên 1)
    ////////////////////////////////////
    for (int row = bom_row-1; row <= bom_row+1; row++)
        for (int col = bom_col-1; col <= bom_col+1; col++)
            if (row >= 0 && row < board_row
                && col >= 0 && col < board_col
                && !(row == bom_row && col == bom_col)
                && minefield[row][col].point != 9)
                ++minefield[row][col].point;
}

void GameOver(std::string &main_state, bool win, SDL_Renderer *&renderer){
    //  Làm mờ màn hình
    //BlurScreen(SC_WIDTH, SC_HEIGHT, renderer);

    DrawSquare(gameover_rect, square_color_normal[0], renderer);

    //  Vẽ đường biên
    SDL_SetRenderDrawColor(renderer, 28,28,28,0);
    SDL_RenderDrawRect(renderer, &gameover_rect);
    SDL_RenderPresent(renderer);

    std::string note;
    if (win){
        note = "You win!";
        PlayMusic("game_win.mp3");
    }
    else {
        note = "You lose!";
        PlayMusic("game_lose.mp3");
    }

    //  Vẽ chữ You win hoặc You lose
    SDL_Surface *surface = GetTextSurface(note, "Font_menu.ttf", font_size_2, background_color);
    int x = gameover_rect.x + (gameover_rect.w - surface->w)/2;
    int y = gameover_rect.y + (gameover_rect.h - surface->h)/2;
    PrintText(note, "Font_menu.ttf", 100*GetScHeight()/1080, background_color, x, y, renderer);

    //  Nút khởi động lại
    ButtonObject restart_button;
    restart_button.rect = gameover_restart_rect;
    restart_button.texture_normal = LoadImg("gameover_restart.png", renderer);
    restart_button.texture_focus = LoadImg("gameover_restart.png", renderer);

    //  Nút quay về menu
    ButtonObject backtomenu_button;
    backtomenu_button.rect = gameover_backtomenu_rect;
    backtomenu_button.texture_normal = LoadImg("gameover_menu.png", renderer);
    backtomenu_button.texture_focus = LoadImg("gameover_menu.png", renderer);

    //  Vẽ các Button
    restart_button.Draw(renderer);
    backtomenu_button.Draw(renderer);

    bool quit = false;
    SDL_Event window_event;
    while(!CheckQuitCurrent(quit, main_state))
    {
        if (SDL_WaitEventTimeout(&window_event,10) != 0)
        {
            switch (window_event.type){
                //  Kiểm tra và tạo focus cho button
                case SDL_MOUSEMOTION:
                    restart_button.Focus(renderer);
                    backtomenu_button.Focus(renderer);
                    break;

                //  Thực hiện hành động khi nhấn vào button
                case SDL_MOUSEBUTTONDOWN:
                    if (restart_button.Click()){
                        main_state = MAIN_NEWGAME;
                        quit = true;
                    }
                    else if (backtomenu_button.Click()){
                        main_state = MAIN_MENU;
                        quit = true;
                    }
                    break;

                //  Thoát khỏi trò chơi
                case SDL_QUIT:
                    main_state = MAIN_EXIT;
                    break;
            }
        }
        SDL_RenderPresent(renderer);
    }
}
