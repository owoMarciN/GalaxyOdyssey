#include "Texture.h"

Texture::Texture(std::string file_name){
    mGraphics = Graphics::Instance();
    mTex = AssetManager::Instance()->GetTexture(file_name);
    SDL_QueryTexture(mTex, nullptr, nullptr, &mWidth, &mHeight);

    mClipped = false;
    mRenderRect.w = mWidth;
    mRenderRect.h = mHeight;
}

Texture::Texture(std::string file_name, int x , int y, int w, int h){
    mGraphics = Graphics::Instance();
    mTex = AssetManager::Instance()->GetTexture(file_name);

    mClipped = true;
    mWidth = w;
    mHeight = h;
    mRenderRect.w = mWidth;
    mRenderRect.h = mHeight;

    mClippedRect.x = x;
    mClippedRect.y = y;
    mClippedRect.w = mWidth;
    mClippedRect.h = mHeight;
}

Texture::~Texture(){
    mTex = nullptr;
    mGraphics = nullptr;
}

void Texture::Render(){
    Vector2 pos = Pos(world);
    Vector2 scale = Scale(world);
    mRenderRect.x = (int)(pos.x - (mWidth*scale.x*0.5f));
    mRenderRect.y = (int)(pos.y - (mHeight*scale.y*0.5f));

    mRenderRect.w = (int)(mWidth*scale.x);
    mRenderRect.h = (int)(mHeight*scale.y);
    mGraphics->DrawTexture(mTex, (mClipped) ? &mClippedRect : nullptr, &mRenderRect, Rotation(world));
}

Texture::Texture(std::string text, std::string fontpath, int size, SDL_Color color){
    mGraphics = Graphics::Instance();
    mTex = AssetManager::Instance()->GetText(text, fontpath, size, color);
    mClipped = false;

    SDL_QueryTexture(mTex, nullptr, nullptr, &mWidth, &mHeight);

    mRenderRect.w = mWidth;
    mRenderRect.h = mHeight;
}
