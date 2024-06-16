#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "GameEntity.h"
#include "AssetManager.h"

class Texture : public GameEntity{
protected: 

    SDL_Texture * mTex;
    Graphics * mGraphics;

    int mWidth;
    int mHeight;
    bool mClipped;
    SDL_Rect mClippedRect;
    SDL_Rect mRenderRect;

public:

    //Texture(std::string file_name, bool IsGIF);
    Texture(std::string file_name);
    Texture(std::string file_name, int x, int y, int w, int h);
    Texture(std::string text, std::string fontpath, int size, SDL_Color color);
    virtual ~Texture();
    virtual void Render();

};

#endif