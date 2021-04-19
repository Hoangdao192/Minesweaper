#include "ImgObject.h"

ImgObject::ImgObject(){
    rect = {0,0,0,0};
    texture = NULL;
    surface = NULL;
}

ImgObject::~ImgObject(){
    if (texture != NULL){
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
    if (surface != NULL){
        SDL_FreeSurface(surface);
        surface = NULL;
    }
}

void ImgObject::Draw(SDL_Renderer *&renderer){
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_RenderPresent(renderer);
}

bool ImgObject::LoadFile(std::string path, SDL_Renderer *&renderer){
    path = "Media/Image/" + path;

    surface = IMG_Load(path.c_str());
    if (surface == NULL){
        std::cout << "\nCannot load file " << path;
        std::cout << "\nExit";
        return false;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    return true;
}
