#include "MainVariable.h"

static int SCREEN_WIDTH = 1920;
static int SCREEN_HEIGHT = 1080;
static bool MUTE = false;

int GetScHeight(){
    return SCREEN_HEIGHT;
}
int GetScWidth(){
    return SCREEN_WIDTH;
}
bool GetMute(){
    return MUTE;
}
int *GetScHeightReference(){
    return &SCREEN_HEIGHT;
}
int *GetScWidthReference(){
    return &SCREEN_WIDTH;
}
bool *GetMuteReference(){
    return &MUTE;
}
