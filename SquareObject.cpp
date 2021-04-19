#include "SquareObject.h"

SquareObject::SquareObject(){
    rect = {0,0,0,0};
    point = 0;
    is_open = false;
    is_bom = false;
    set_flag = false;
    texture_normal = NULL;
    texture_open = NULL;
}

SquareObject::~SquareObject(){
    if (texture_normal != NULL)
    {
        SDL_DestroyTexture(texture_normal);
        texture_normal = NULL;
    }
    if (texture_open != NULL)
    {
        SDL_DestroyTexture(texture_open);
        texture_open = NULL;
    }
}

void SquareObject::Draw(SDL_Renderer *&renderer){
    if (!set_flag)
        SDL_RenderCopy(renderer, texture_normal, NULL, &rect);
    else SDL_RenderCopy(renderer, texture_flag, NULL, &rect);
}

void SquareObject::Focus(SDL_Renderer *&renderer){
    if (CheckMouse(rect))
    {
        SDL_SetRenderDrawColor(renderer, 255,0,0,0);
        SDL_RenderDrawRect(renderer, &rect);
    }
    else Draw(renderer);

}

void SquareObject::Open(SDL_Renderer *&renderer){
    is_open = true;
    SDL_RenderCopy(renderer, texture_open, NULL, &rect);
    if (point > 0 && point < 9) DrawPoint(renderer);
}

void SquareObject::SetBom(SDL_Renderer *&renderer){
    is_bom = true;
    point = 9;
    srand((int) time(0));
    int bom_img = 1+rand()%2;

    std::string path = "bom"+std::to_string(bom_img)+".png";
    texture_open = LoadImg(path, renderer);
}

void SquareObject::SetFlag(SDL_Renderer *&renderer){
    set_flag = true;
    PlayMusic("set_flag.mp3");
    Draw(renderer);
}

void SquareObject::DeleteFlag(SDL_Renderer *&renderer){
    set_flag = false;
    Draw(renderer);
}

void SquareObject::DrawPoint(SDL_Renderer *&renderer){
    //  Chọn màu
    if (point < 9 && point > 0)
        point_text.SetColor(POINT_COLOR[point-1].r, POINT_COLOR[point-1].g, POINT_COLOR[point-1].b);
    else point_text.SetColor(0,0,0);

    //  Lấy điểm
    point_text.SetFont(SQUAREPOINT_FONT, SQUAREPOINT_SIZE*rect.w/SQUARESIZE_MAX);
    point_text.SetText(std::to_string(point));
    point_text.CreateTexture(renderer);
    //  Tính vị trí và vẽ
    int x = rect.x + (rect.w - point_text.GetRect().w)/2;
    int y = rect.y + (rect.w - point_text.GetRect().h)/2;
    point_text.SetRect(x,y);
    point_text.Draw(renderer);
}
