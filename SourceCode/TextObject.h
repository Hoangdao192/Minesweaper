#ifndef TEXTOBJECT_H_INCLUDED
#define TEXTOBJECT_H_INCLUDED

#include "MainFunction.h"

class TextObject{
    public:
        void Draw(SDL_Renderer *&renderer);
        void SetRect(int x, int y){rect_.x = x; rect_.y = y;}
        void SetColor(int color_r, int color_g, int color_b) {color_ = {color_r, color_g, color_b};}
        void SetFont(std::string font, int font_size){font_ = font; size_ = font_size;}
        void SetText(std::string text);
        std::string text_;
        std::string GetText(){return text_;};
        TextObject(std::string text = " ", std::string font = "Font_menu.ttf", int font_size = 50, int color_r = 0, int color_g = 0, int color_b = 0);
        ~TextObject();
        SDL_Rect GetRect(){return rect_;};
        void CreateTexture(SDL_Renderer *&renderer);
    private:
        SDL_Color color_;
        SDL_Rect rect_;
        int size_;
        std::string font_;
        SDL_Texture *texture;
    //protected:

};

#endif // TEXTOBJECT_H_INCLUDED
