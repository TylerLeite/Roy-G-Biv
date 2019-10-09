#include "game.h"

/** GAME **/
Game::Game(int width, int height, int fps) :
    curLvl(1), 
    width(810), height(1440), fps(60), paused(false),
    fade_xpar(0)
{

//Boring SDL and OpenGL setup stuff
  //Initialize SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetVideoMode(width, height, 32, SDL_OPENGL); //Game window size, 32 bit colors, SDL_OpenGL for rendering
    SDL_EnableKeyRepeat(1, 2); //Make it possible to detect keys held down
  //Memory size allocation for OpenGL
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  //End memory size allocation
    SDL_WM_SetCaption(GAME_TITLE, nullptr); //Game window title
    glClearColor(0, 0, 0, 0); //Clear color for screen refreshing (Red, Green, Blue, Alpha)
    glViewport(0,0, width,height); //Portion of the window to display [(Upper left), (Lower right)]
    //glShadeModel(GL_SMOOTH); //Sets OpenGL shading to gradients
    glMatrixMode(GL_PROJECTION); //Tells openGL that this will be a 2d game
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST); //Disabling 3d-specific OpenGL operations
  //Blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
//End of boring SDL and OpenGL stuff

    srand(time(nullptr)); //Seeds the RNG for future use

}

void Game::start(){
    bool quit = false;
    Uint32 start;
    
    map.loadMap("maps/map_1.map");
    
    while (!quit){ //Game loop start
        start = SDL_GetTicks();
        
        quit = !map.input(paused);
        
        update();
        
        int status = map.checkStatus();
        if (status != 0){
            paused = true;
            fade(RGB_FADE_OUT);
            
            if (status == 1){
                curLvl++;
                WriteMsg::write("You have completed the level, press the any key to start the next one.");
            } else if (status == -1){
                WriteMsg::write("You have died");
            }
            
            stringstream waffen; //ignore name
            waffen << "maps/map_" << curLvl << ".map";
            string filen = waffen.str();
            map.loadMap(filen.c_str());
            
            fade(RGB_FADE_IN);
            ipaused = false;
        }
        render();
		
	  //Limit the framerate
        if (1000/fps > (SDL_GetTicks()-start)){
            SDL_Delay(1000/fps-(SDL_GetTicks()-start));
        }
    } //Game loop stop

    SDL_Quit();
}

void Game::update(){
    map.update();
}

void Game::render(){
    glClear(GL_COLOR_BUFFER_BIT); //Clear window
    glPushMatrix(); //Clear matrix
    glOrtho(0, width, height, 0, -1, 1); //Set matrix

    map.render();
    //renderSpriteAt("graphics/skins/default/stopped_down_0.png", 4, 4);

    glPopMatrix(); //Place Matrix
    SDL_GL_SwapBuffers();
}


/*
The goal of the game is to get all tiles to be Red. You do this by
walking. It's just that easy. Stepping on a tile will adjust a tile's
color in the following order: Violet -> Indigo -> Blue -> Green ->
Yellow -> Orange -> Red. If you step on a red tile, it's game-over.
The tile will disappear and you will fall into oblivion. Then you
will die. Alone. You control your character (Roy himself) with W, A,
S, and D to move Up, Down, Left, and Right respectively. Once all the
tiles are Red, you must walk to the exit (hint: it looks a bit like
this -> E) (other hint: for those slightly dull, this means that you
don't JUST need all the tiles to be red, you need to end up next to
the exit) (other other hint: Press any key to return to the menu).
*/

//Ricardo Cruz is a horrible programmer, but I stold this from him so I
//guess i should give credit anyway
void Game::fade(bool in){
    unsigned textture = 0;
    
    for (float i=0; i <= 100; i++){
        float alpha;
        if (in){
            alpha = 1.0f - i/100.0f;
        } else {
            alpha = i/100.0f;
        }
        
        cout << alpha <<"\n";
        
        glClear(GL_COLOR_BUFFER_BIT); //Clear window
        glPushMatrix(); //Clear matrix
        glOrtho(0, width, height, 0, -1, 1); //Set matrix
        
        glColor4f(0.0f, 1.0f, 0.0f, alpha);
        glBegin(GL_QUADS);
            glVertex2f(16,     32);
            glVertex2f(16, 16);
            glVertex2f(32, 32);
            glVertex2f(16,     16);
        glEnd();
        
        SDL_Delay(10);
        
        glPopMatrix(); //Place Matrix
        SDL_GL_SwapBuffers();
    }
} 
