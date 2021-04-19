#ifndef MAINFUNCTION_H_INCLUDED
#define MAINFUNCTION_H_INCLUDED

#include "MainVariable.h"
#include "ImgObject.h"

struct GameSet{
    int bom = 0;
    int board_col = 0;
    int board_row = 0;
    int count_down_time = 0;
    int help_time = 0;
};

bool CheckQuitCurrent(bool quit_current, const std::string &main_state);

void DrawBackground(SDL_Renderer *&renderer);

bool CheckMouse(SDL_Rect rect);
//  Hàm phát nhạc
void PlayMusic(std::string file);
//  Hàm load file ảnh từ bộ nhớ
SDL_Texture *LoadImg(std::string image, SDL_Renderer *renderer);
//  Hàm xuất một texture ra màn hình
void ApplyTexture(SDL_Texture *texture, SDL_Renderer *renderer, SDL_Rect rect);
//  Hàm lấy *surface của một chuỗi kí tự khi in ra màn hình
SDL_Surface *GetTextSurface(std::string value, std::string font, int font_size, SDL_Color color);
//  Hàm viết chữ lên màn hình
void PrintText(std::string value, std::string font, int font_size, SDL_Color color, int x, int y, SDL_Renderer *renderer);
//  Hàm làm mờ màn hình
void BlurScreen(const int &SC_WIDTH, const int &sc_height, SDL_Renderer *&renderer);
//  Hàm đọc màn hình
SDL_Texture *ScreenCapture(SDL_Renderer *&renderer, SDL_Rect rect);

//  Đặt chế độ chơi
void SetGameMode(std::string &main_state, SDL_Renderer *&renderer);
int GetGameMode();
//  Đặt độ khó
void SetGameDifficulty(std::string &main_state, SDL_Renderer *&renderer);
//  Khởi tạo game mới
void NewGame(std::string &main_state, SDL_Renderer *&renderer);
//  Menu Chính
void MainMenu(std::string &main_state, SDL_Renderer *&renderer);
//  Menu Cài đặt
void SettingMenu(std::string &main_state, SDL_Renderer *&renderer);
//  Menu Cài đặt nhanh
void QuickSettingMenu(std::string &main_state, SDL_Renderer *&renderer);

#endif // MAINFUNCTION_H_INCLUDED
