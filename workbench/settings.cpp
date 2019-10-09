#include "settings.h"

//video
int Settings::width=128;
int Settings::height=128;
int Settings::fps=60;

//audio
int Settings::sfx=50;
int Settings::music=50;

//ctrl
int Settings::up=SDLK_w;
int Settings::down=SDLK_s;
int Settings::left=SDLK_a;
int Settings::right=SDLK_d;
int Settings::pause=SDLK_p;
int Settings::quit=SDLK_ESCAPE;
int Settings::nextLevel=SDLK_q;
int Settings::reset=SDLK_r;
    
//gameSettings
string Settings::tileset="default";
string Settings::skin="default";

void Settings::loadSettings(){  //settings.dat
    //
}

void  checkSettings(){
    //if something doesn't check out, print an error and load default
}

void writeSettings(){//settings.dat
    return;
}
