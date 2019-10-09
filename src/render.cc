#include "render.h"

unsigned loadTexture(const string& filen){
    unsigned texture;
    SDL_Surface* tmp = IMG_Load(filen.c_str());
    
    SDL_PixelFormat form = {
        NULL, 32, 4, 
        0, 0, 0, 0, 
        8, 8, 8, 8,
        0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff,
        0, 255
    };
                            
    SDL_Surface* img = SDL_ConvertSurface(tmp, &form, SDL_SWSURFACE); //png
    
    SDL_FreeSurface(tmp); //safe to pass NULL
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, 
                 GL_RGBA, GL_int_INT_8_8_8_8, img->pixels);
    SDL_FreeSurface(img);
    
    return texture;
}

void renderAt(const std::string& filen, int width, int height, 
                       int pos_x, int pos_y){
    //cout << "Rendering file: " << filen << " at (" << posX << ", " << posY << ")\n";

    if (!textures.count(filen)){
        cout << "Storing new texture: " << filen << "\n";
        textures.insert(pair<string, int>(filen, loadTexture(filen)));
    }
    
    int texture = textures[filen];
    
    glEnable(GL_TEXTURE_2D); //enable textures

    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
        glTexCoord2d(0, 0); glVertex2f(posX,                  posY); //bottom left
        glTexCoord2d(1, 0); glVertex2f(posX + width,          posY); //bottom right
        glTexCoord2d(1, 1); glVertex2f(posX + width, posY + height); //top right
        glTexCoord2d(0, 1); glVertex2f(posX,         posY + height); //top left
    glEnd();
    
    glDisable(GL_TEXTURE_2D); //disable textures
}

void renderOn(const std::string& filen, int map_x,  int map_y){
    int posX = map_x*T_WD;
    int posY = map_y*T_HG;
    
    renderSprite(filen, T_WD, T_HG, posX, posY);
}
