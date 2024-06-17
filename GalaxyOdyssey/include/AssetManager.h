#ifndef ASSETMANAGER_H_
#define ASSETMANAGER_H_

#include "Graphics.h"
#include <SDL2/SDL_mixer.h>
#include <map>

class AssetManager{
private:

    static AssetManager * sInstance;
    
    std::map<std::string, SDL_Texture *> mTextures;
    std::map<std::string, SDL_Texture *> mText;
    std::map<std::string, TTF_Font *> mFonts;
    //Used to cache all loaded music files
	std::map<std::string, Mix_Music *> mMusic;
	//Used to cache all loaded sound effect files
	std::map<std::string, Mix_Chunk *> mSFX;

public:

    static AssetManager * Instance();
    static void Release();
    SDL_Texture * GetTexture(std::string file_name);
    SDL_Texture * GetText(std::string text, std::string file_name, int size, SDL_Color color);
    Mix_Chunk* GetSFX(std::string filename);
    Mix_Music* GetMusic(std::string filename);

private:

    TTF_Font * GetFont(std::string file_name, int size);
    AssetManager();
    ~AssetManager();
    
};

#endif