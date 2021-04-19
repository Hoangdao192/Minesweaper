#include "ButtonObject.h"

ButtonObject::ButtonObject(){
    rect = {0,0,0,0};
    texture_normal = NULL;
    texture_focus = NULL;
    is_clicked = false;
    is_focus = false;
}

ButtonObject::~ButtonObject(){
    if (texture_normal != NULL)
    {
        SDL_DestroyTexture(texture_normal);
        texture_normal = NULL;
    }
    if (texture_focus != NULL)
    {
        SDL_DestroyTexture(texture_focus);
        texture_focus = NULL;
    }
}

void ButtonObject::Draw(SDL_Renderer *&renderer){
    SDL_RenderCopy(renderer, texture_normal, NULL, &rect);
    SDL_RenderPresent(renderer);
}

void ButtonObject::Focus(SDL_Renderer *&renderer){
    SDL_SetTextureColorMod(texture_focus, 80,80,80);
    if (CheckMouse(rect))
    {
        is_focus = true;
        SDL_RenderCopy(renderer, texture_focus, NULL, &rect);
        SDL_RenderPresent(renderer);
    }
    else if (is_focus) {
        is_focus = false;
        Draw(renderer);
    }
}

bool ButtonObject::Click(){
    if (CheckMouse(rect))
    {
        PlayMusic("button_click.mp3");
        is_clicked = true;
        return true;
    }
    return false;
}
