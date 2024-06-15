#include "AssetManager.h"

AssetManager * AssetManager::sInstance = nullptr;

AssetManager::AssetManager(){

}

AssetManager::~AssetManager(){
    
    for(auto &tex : mTextures)
        if(tex.second != nullptr)
            SDL_DestroyTexture(tex.second);
    mTextures.clear();

    for(auto &text : mText){
        if(text.second != nullptr){
            SDL_DestroyTexture(text.second);
        }
    }
    mText.clear();

    for(auto &font : mFonts){
        if(font.second != nullptr){
            TTF_CloseFont(font.second);
        }
    }
    mFonts.clear();

   for(auto &music : mMusic) {
		if(music.second != nullptr) {
			Mix_FreeMusic(music.second);
		}
	}
	mMusic.clear();

	//Freeing all loaded sound effects
	for(auto &sfx : mSFX) {
		if(sfx.second != nullptr) {
			Mix_FreeChunk(sfx.second);
		}
	}
	mSFX.clear();
}

AssetManager * AssetManager::Instance(){
    if(sInstance == nullptr)
        sInstance = new AssetManager();
    return sInstance;
}

void AssetManager::Release(){
    delete sInstance;
    sInstance = nullptr;
}

SDL_Texture * AssetManager::GetTexture(std::string file_name){
    std::string fullpath = SDL_GetBasePath();
    fullpath.append("./Assets/Textures/" + file_name);

    if(mTextures[fullpath] == nullptr)
        mTextures[fullpath] = Graphics::Instance()->loadTexture(fullpath);

    return mTextures[fullpath];
}

TTF_Font * AssetManager::GetFont(std::string file_name, int size){
    std::string fullpath = SDL_GetBasePath();
    fullpath.append("./Assets/TTF/" + file_name);

    std::string key = fullpath + (char)size;

    if(mFonts[key] == nullptr){
        mFonts[key] = TTF_OpenFont(fullpath.c_str(), size);
        if(mFonts[key] == nullptr)
            std::cout << "Font Loading Error: Font: " << file_name.c_str() << " Error: " << TTF_GetError() << '\n';
    }
    return mFonts[key];
}

SDL_Texture * AssetManager::GetText(std::string text, std::string file_name, int size, SDL_Color color){
    TTF_Font * font = GetFont(file_name, size);
    std::string key = text + file_name + (char)size + (char)color.r + (char)color.g + (char)color.b;
    if(mText[key] == nullptr)
        mText[key] = Graphics::Instance()->CreateTextTexture(font, text, color);
    return mText[key];
}

Mix_Music* AssetManager::GetMusic(std::string filename) {
	//Get the full path of the WAV file
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("./Assets/MP3/" + filename);
	//If the file has not been already loaded, load it and add it to the mMusic map
	if(mMusic[fullPath] == nullptr) {
		mMusic[fullPath] = Mix_LoadMUS(fullPath.c_str());
		//Error handling for file loading
		if(mMusic[fullPath] == nullptr)
			printf("Music Loading Error: File-%s Error-%s", filename.c_str(), Mix_GetError());
	}
	//returning the cached file from the map
	return mMusic[fullPath];
}

Mix_Chunk* AssetManager::GetSFX(std::string filename) {
		//Get the full path of the WAV file
		std::string fullPath = SDL_GetBasePath();
		fullPath.append("./Assets/WAV/" + filename);
		//If the file has not been already loaded, load it and add it to the mSFX map
		if(mSFX[fullPath] == nullptr) {
			mSFX[fullPath] = Mix_LoadWAV(fullPath.c_str());
			//Error handling for file loading
			if(mSFX[fullPath] == nullptr)
				printf("SFX Loading Error: File-%s Error-%s", filename.c_str(), Mix_GetError());
		}
		//returning the cached file from the map
		return mSFX[fullPath];
	}