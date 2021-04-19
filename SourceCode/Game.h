#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "MainFunction.h"
#include <sstream>
#include <vector>
#include "SquareObject.h"
#include "ButtonObject.h"
#include "TextObject.h"
#include "SetGameDifficulty.h"



namespace MainGame  {
    //  Tính toán các kích thước
    void SetGameRect();
    //  Khởi tạo các Button
    void InitButton(SDL_Renderer *&renderer);

    void CreateText();
}

//  Khởi tạo game theo giá trị của game_mode(kiểu chơi)
//  Kiểu chơi Đếm ngược
void NewGameCountDown(std::string &main_state, SDL_Renderer *&renderer);
//  Kiểu chơi cổ điển
void NewGameClassic(std::string &main_state, SDL_Renderer *&renderer);
//  Giúp đỡ
void GameHelp(int &open_square, const int &total_help, SDL_Renderer *&renderer);

//  Trả về chỉ sô hàng và cột của ô vuông
void GetCoordMinefield(int &row, int &col);
//  Khởi tạo giá trị cho các ô vuông
void InitSquareValue();
//  Sinh bom ngẫu nhiên
void SetBom(int no_row, int no_col, SDL_Renderer *&renderer);
//  Tính số bom xung quanh 1 ô
void SetPoint(int bom_row, int bom_col);
//  Trả về true nếu con trỏ chuột nằm trong bảng
bool IsMouseInBoard();

//  Vẽ cờ
void DrawFlag(int row, int col, int flag_remain, SDL_Renderer *&renderer);
//  Vẽ số cờ còn lại
void DrawFlagRemain(int flag_remain, SDL_Renderer *&renderer);
//  Xóa cờ
void DeleteFlag( int row, int col, SDL_Renderer *&renderer);
//  Vẽ thời gian
void DrawTime(int second, SDL_Renderer *&renderer);
//  Vẽ bom
void DrawAllBom(SDL_Renderer *&renderer);

void DrawSquare(const SDL_Rect &rect, const SDL_Color &color, SDL_Renderer *&renderer);
//  Vẽ bảng ô vuông
void DrawBoard(SDL_Renderer *&renderer);

//  Mở ra 1 vùng khi mở trúng ô trống
void OpenField(int row, int col, int &open_square, SDL_Renderer *&renderer);
//  Mở một ô bình thường
void OpenSquareNormal(int row, int col, int &open_square, SDL_Renderer *&renderer);
//  Khởi tạo màn hình kết thúc game
void GameOver(std::string &main_state, bool win, SDL_Renderer *&renderer);
#endif // GAME_H_INCLUDED
