#include "MainVariable.h"

bool CheckQuitCurrent(bool quit, const std::string &main_state){
    if (quit == true
    || main_state.compare(MAIN_EXIT) == 0
    || main_state.compare(MAIN_RESTART) == 0
    || main_state.compare(MAIN_NEWGAME) == 0
    || main_state.compare(MAIN_MENU) == 0)
    return true;
    return false;
}

void DrawBackground(SDL_Renderer *&renderer){
    //  Vẽ nền
    SDL_Rect rect = {0, 0, GetScWidth(), GetScHeight()};
    SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g, background_color.b, 0);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}

bool CheckMouse(SDL_Rect rect){
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    if (mouse_x < rect.x || mouse_x > rect.x+rect.w) return false;
    if (mouse_y < rect.y || mouse_y > rect.y+rect.h) return false;
    return true;
}

void PlayMusic(std::string file){
    file = "Media/Sound/" + file;

    if (!GetMute()){
        //Mix_FreeMusic(g_music);
        g_music = Mix_LoadMUS(file.c_str());
        if (g_music == NULL){
            std::cout << "\nCannot load file " << file;
            std::cout << "\nProgram exit";
            exit(0);
        }
        Mix_PlayMusic(g_music,1);
    }
}

SDL_Texture *LoadImg(std::string image, SDL_Renderer *renderer){

     image = "Media/Image/" + image;

    SDL_Surface *load_img = IMG_Load(image.c_str());
    if (load_img == NULL){
        std::cout << "\nCannot load file " << image;
        std::cout << "\nExit";
        exit(0);
    }

    SDL_Texture *temp_texture = SDL_CreateTextureFromSurface(renderer, load_img);
    SDL_FreeSurface(load_img);

    return temp_texture;
}

void ApplyTexture(SDL_Texture *texture, SDL_Renderer *renderer, SDL_Rect rect){
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_RenderPresent(renderer);
}

SDL_Surface *GetTextSurface(std::string value, std::string font, int font_size, SDL_Color color){

    font = "Font/" + font;

    //  Load font từ bộ nhớ
    TTF_Font *font_opened = TTF_OpenFont(font.c_str(), font_size);
    //  Tạo một surface
    SDL_Surface *text_Surface = TTF_RenderText_Solid(font_opened, value.c_str(), color);
    TTF_CloseFont(font_opened);
    return text_Surface;
}

void PrintText(std::string value, std::string font, int font_size, SDL_Color color, int x, int y, SDL_Renderer *renderer){
    //static std::string font_path = GetAppDir() + "\\Font\\";
    //font = font_path + font;

    SDL_Surface *text_surface = GetTextSurface(value, font, font_size, color);
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_Rect rect = {x, y, text_surface->w, text_surface->h};

    SDL_RenderCopy(renderer, text_texture, NULL, &rect);
    SDL_RenderPresent(renderer);
    //ApplyTexture(text_texture, renderer, {x, y, text_surface->w, text_surface->h});

    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
}

void BlurScreen(const int &sc_width, const int &sc_height, SDL_Renderer *&renderer){
    ////////////////////////////////////////
    //  Làm mờ màn hình
    ////////////////////////////////////////
    SDL_Surface *blur_screen = SDL_CreateRGBSurface(0, sc_width, sc_height, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ABGR32, blur_screen->pixels, blur_screen->pitch);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, blur_screen);
    SDL_SetTextureColorMod(texture, 10,10,10);

    ApplyTexture(texture, renderer, {0,0,blur_screen->w, blur_screen->h});
    SDL_FreeSurface(blur_screen);
    SDL_DestroyTexture(texture);
}

SDL_Texture *ScreenCapture(SDL_Renderer *&renderer, SDL_Rect rect){
    /////////////////////////////////////////////////////////////
    //  Hàm chụp ảnh màn hình tại vị trí và kích thước cho trước
    /////////////////////////////////////////////////////////////
    SDL_Surface *screen = SDL_CreateRGBSurface(0, rect.w, rect.h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_RenderReadPixels(renderer, &rect, SDL_PIXELFORMAT_ARGB8888, screen->pixels, screen->pitch);
    SDL_Texture *read_texture = SDL_CreateTextureFromSurface(renderer, screen);
    SDL_FreeSurface(screen);
    return read_texture;
}



