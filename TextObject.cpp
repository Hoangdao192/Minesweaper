#include "TextObject.h"

TextObject::TextObject(std::string text, std::string font, int font_size, int color_r, int color_g, int color_b){
    texture = NULL;
    rect_ = {0,0,0,0};
    color_ = {color_r,color_g,color_b,0};
    text_ = text;
    font_ = font;
    size_ = font_size;
}

TextObject::~TextObject(){
    if (texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}

void TextObject::CreateTexture(SDL_Renderer *&renderer){
    if (texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
    //  Load font từ bộ nhớ
    TTF_Font *font_opened = TTF_OpenFont((FONT_PATH+font_).c_str(), size_);
    //  Tạo một surface
    SDL_Surface *text_surface = TTF_RenderText_Solid(font_opened, text_.c_str(), color_);
    TTF_CloseFont(font_opened);
    //  Đặt Rect
    rect_.w = text_surface->w;
    rect_.h = text_surface->h;
    //  Tạo texture
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);

    SDL_FreeSurface(text_surface);
}

void TextObject::SetText(std::string text){
    text_ = text;
}

void TextObject::Draw(SDL_Renderer *&renderer){
    CreateTexture(renderer);
    SDL_RenderCopy(renderer, texture, NULL, &rect_);
    SDL_RenderPresent(renderer);
}
