#include "AssetManager.h"

AssetManager * AssetManager::sInstance = NULL;

AssetManager::AssetManager(){

}

AssetManager::~AssetManager(){
    for(auto tex : mTextures)
        if(tex.second != NULL)
            SDL_DestroyTexture(tex.second);
    mTextures.clear();

    for(auto text : mText){
        if(text.second != NULL){
            SDL_DestroyTexture(text.second);
        }
    }
    mText.clear();

    for(auto font : mFonts){
        if(font.second != NULL){
            TTF_CloseFont(font.second);
        }
    }
    mFonts.clear();

   for(auto music : mMusic) {
		if(music.second != NULL) {
			Mix_FreeMusic(music.second);
		}
	}

	mMusic.clear();

	//Freeing all loaded sound effects
	for(auto sfx : mSFX) {
		if(sfx.second != NULL) {
			Mix_FreeChunk(sfx.second);
		}
	}

	mSFX.clear();
}

AssetManager * AssetManager::Instance(){
    if(sInstance == NULL)
        sInstance = new AssetManager();
    return sInstance;
}

void AssetManager::Release(){
    delete sInstance;
    sInstance = NULL;
}
SDL_Texture * AssetManager::GetTexture(std::string file_name){
    std::string fullpath = SDL_GetBasePath();
    fullpath.append("./Assets/" + file_name);

    if(mTextures[fullpath] == nullptr)
        mTextures[fullpath] = Graphics::Instance()->loadTexture(fullpath);

    return mTextures[fullpath];
}

TTF_Font * AssetManager::GetFont(std::string file_name, int size){
    std::string fullpath = SDL_GetBasePath();
    fullpath.append("./Assets/" + file_name);

    std::string key = fullpath + (char)size;

    if(mFonts[key] == NULL){
        mFonts[key] = TTF_OpenFont(fullpath.c_str(), size);
        if(mFonts[key] == NULL)
            std::cout << "Font Loading Error: Font: " << file_name.c_str() << " Error: " << TTF_GetError() << '\n';
    }
    return mFonts[key];
}

SDL_Texture * AssetManager::GetText(std::string text, std::string file_name, int size, SDL_Color color){
    TTF_Font * font = GetFont(file_name, size);
    std::string key = text + file_name + (char)size + (char)color.r + (char)color.g + (char)color.b;
    if(mText[key] == NULL)
        mText[key] = Graphics::Instance()->CreateTextTexture(font, text, color);
    return mText[key];
}

Mix_Music* AssetManager::GetMusic(std::string filename) {

	//Get the full path of the WAV file
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Assets/" + filename);

	//If the file has not been already loaded, load it and add it to the mMusic map
	if(mMusic[fullPath] == NULL) {

		mMusic[fullPath] = Mix_LoadMUS(fullPath.c_str());
		//Error handling for file loading
		if(mMusic[fullPath] == NULL)
			printf("Music Loading Error: File-%s Error-%s", filename.c_str(), Mix_GetError());
	}

	//returning the cached file from the map
	return mMusic[fullPath];
}

Mix_Chunk* AssetManager::GetSFX(std::string filename) {

		//Get the full path of the WAV file
		std::string fullPath = SDL_GetBasePath();
		fullPath.append("Assets/" + filename);

		//If the file has not been already loaded, load it and add it to the mSFX map
		if(mSFX[fullPath] == NULL) {

			mSFX[fullPath] = Mix_LoadWAV(fullPath.c_str());
			//Error handling for file loading
			if(mSFX[fullPath] == NULL)
				printf("SFX Loading Error: File-%s Error-%s", filename.c_str(), Mix_GetError());
		}

		//returning the cached file from the map
		return mSFX[fullPath];
	}