#ifndef GAME_H
#define GAME_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#define RGB_MODE_MENU -1
#define RGB_MODE_STORY 0
#define RGB_MODE_SETTINGS 1
#define RGB_MODE_QUIT 2


class Game {
    public:
      //data members
        unsigned width, height, //screen resolution
                 fps; //frames per second
        Settings settings;
      //for menu
        std::map<std::string, std::vector<Button*> > menus;
        int cur_button;
        std::string cur_menu
     //for other
        bool paused = false;
        RGB::map cur_map;

        Game(unsigned width=800, unsigned height=600, unsigned fps=60) :
            width(width), height(height), fps(fps),
            cur_button(0), menu("main")
        {
            init();
            start();
        }

        ~Game(){
            std::map<std::string, std::vector<Button*> >::iterator it
                                                                = menus.begin();
            for (; it != menus.end(); it++){
                delete[] it->second;
            }
        }

        /*
        void init():
            init sdl / opengl
            init menus
            read from settings file
        */

        void init();
        void initSDLDpenGL();
        void initMenu();
        void readSettings();

        void start();

        int runMenu();
        int runStory();

        void runEndless();

        void limitFramerate(Uint32 start);
        void writeSettings();

        //secondary concerns:
        void startBattle();
        void startCoop();
};

#endif
