#include "game.h"

void Game::init(){
    initSDLOpenGL();
    initMenu();
    //readSettings();
}

void Game::initSDLOpenGL(){
  //initialize SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetVideoMode(width, height, 32, SDL_OPENGL);
    SDL_EnableKeyRepeat(1, 2);

  //memory size allocation for OpenGL
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
    SDL_WM_SetCaption(GAME_TITLE, nullptr);
    glClearColor(0, 0, 0, 0);
    glViewport(0,0, width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);

  //blending (needed for transparency)
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );

    srand(time(nullptr)); //seeds the RNG for future use
}

void Game::initMenu(){
    std::string name;
    std::vector<Button*> buttons;
    //main menu
    name = "main"
    buttons.push_back(new Button(0, 0, 200, 50, "story")); //x, y, width, height
    buttons.push_back(new Button(0, 60, 200, 50, "exit"));

    menus.insert(std::pair<std::string, std::vector<Button*> >(name, buttons));
    buttons.clear();

    //other menus
}

void Game::start(){
    bool quit = false;
    Uint32 start = 0;
    int mode = RGB_MODE_MENU;

    while (!quit){ //game loop start
        start = SDL_GetTicks();

        if (mode == RGB_MODE_MENU){
            mode = runMenu();
        } else {
            switch (mode){
                case RGB_MODE_STORY:
                    runStory();
                    break;
                case RGB_QUIT_MODE:
                    quit = true;
                    false;
                default:
                    break;
            }
        }
		
        limitFramerate(start);
    } //end game loop

    SDL_Quit();
}

int Game::runMenu(){
    //update
    if (cur_menu == "main"){
        std::string input = Input::pollMenuInput();
        if (input == "up"){
            cur_button--;
        } else if (input == "down"){
            cur_button++;
        } else if (input == "enter"){
            if (button->name == "story"){
                return RGB_MODE_STORY;
            } else if (button->name == "settings"){
                return RGB_MODE_SETTINGS;
            } else if (button->name == "quit"){
                return RGB_QUIT_MODE;
            }
        }
    }

    //render
    glClear(GL_COLOR_BUFFER_BIT); //Clear window
    glPushMatrix(); //Clear matrix
    glOrtho(0, width, height, 0, -1, 1); //Set matrix

    for (int i = 0; i < menus[cur_menu].size(); i++){
        menus[cur_menu][i]->render();
    }

    glPopMatrix(); //Place Matrix
    SDL_GL_SwapBuffers();
}

void Game::runStory(){
    //TODO: other stuff
    int status = map.checkStatus();

    if (paused){
        return;
    }
    
    switch (status){
        case RGB_STATUS_SETUP:
            stringstream waffen; //ignore name
            waffen << "maps/map_" << curLvl << ".map";
            string filen = waffen.str();
            map.loadMap(filen.c_str());
            break;
        case RGB_STATUS_PLAYING:
            break;
        case RGB_STATUS_WON:
            break;
        case RGB_STATUS_LOST:
            break
        default:
            break;
    }
}

void Game::runEndless(){
    return;
}

void Game::limitFramerate(Uint32 start){
    if (1000/fps > (SDL_GetTicks()-start)){
        SDL_Delay(1000/fps-(SDL_GetTicks()-start));
    }
}

void Game::readSettings(){
    return;
}

