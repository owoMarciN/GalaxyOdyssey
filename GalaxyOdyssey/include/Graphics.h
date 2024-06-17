#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

class Graphics{
public:

    static const int SCREEN_HEIGHT = 720;
    static const int SCREEN_WIDTH = 1280;

private:
    
    static Graphics * sInstance;
    static bool sInitialized;
    
    SDL_Window * mWindow;
    SDL_Surface * mIcon;
    SDL_Renderer * mRenderer;

public:

    static Graphics * Instance();
    static bool Initialized();
    static void Release();
    void Render();

    SDL_Texture * loadTexture(std::string path);
    void ClearBackBuffer(); // Clearing Canvas
    
    void DrawTexture(SDL_Texture * tex, SDL_Rect * clip = NULL, SDL_Rect * rend = NULL, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void DrawLine(float x_0, float y_0, float x_1, float y_1);
    SDL_Texture * CreateTextTexture(TTF_Font * font, std::string text, SDL_Color color);

private:

    Graphics();
    ~Graphics();
    bool Init();
    
};

#endif