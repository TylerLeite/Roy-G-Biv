#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
using std::string;

#include <SDL2/SDL.h"

class Settings{
    public:
      //video
        static int width, height, fps;

      //audio
        static int sfx, music;

      //ctrl
        static int up, down, left, right, 
            pause, quit, nextLevel, reset;
      //gameSettings
        static string tileset, skin;
        
        static void loadSettings();  //settings.dat
        static void checkSettings(); //check if the settings are legit
        static void writeSettings(); //settings.dat
};
#endif

/*
      //video
        static int width=128, height=128, fps=60;

      //audio
        static int sfx=50, music=50;

      //ctrl
        static int up=SDLK_w, down=SDLK_s, left=SDLK_a, right=SDLK_d, 
            pause=SDLK_p, quit=SDLK_ESCAPE, nextLevel=SDLK_q, reset=SDLK_r;
      //gameSettings
        static string tileset="default", skin="default";
*/
