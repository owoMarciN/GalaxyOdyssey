#include "Graphics.h"

Graphics * Graphics::sInstance = NULL;
bool Graphics::sInitialized = false;

Graphics * Graphics::Instance(){
    if(sInstance == NULL)
        sInstance = new Graphics;
    return sInstance;
}

void Graphics::Release(){
    delete sInstance;
    sInstance = NULL;
    sInitialized = false;
}

bool Graphics::Initialized(){
    return sInitialized;
}

Graphics::Graphics(){
    sInitialized = Init();
}

Graphics::~Graphics(){
    SDL_DestroyWindow(mWindow);
    mWindow = NULL;

    SDL_DestroyRenderer(mRenderer);
    mRenderer = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool Graphics::Init(){
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){
        std::cout << "SDL Initialization Error: " << SDL_GetError();
        return false;
    }
    mWindow = SDL_CreateWindow("My first Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if(mWindow == NULL){
        std::cout << "Window creation Error: " << SDL_GetError();
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_SOFTWARE);
    if(mRenderer == NULL){
        std::cout << "SDL Create Renderer Error: " << SDL_GetError();
        return false;
    }

    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0x00);

    int flags = IMG_INIT_JPG;
    if(!IMG_Init(flags) && flags){
        std::cout << "IMG Initialization Error: " << IMG_GetError();
        return false;
    }

    if(TTF_Init() == -1){
        std::cout << "TTF Inicialization Error: " << TTF_GetError() << '\n';
        return false;
    }
    
    return true;
}

SDL_Texture * Graphics::loadTexture(std::string path){
    SDL_Texture * tex = NULL;
    SDL_Surface * surface = IMG_Load(path.c_str());
    if(surface == NULL){
        std::cout << "IMG Load Error: Path(" << path <<") - Error(" << IMG_GetError() << ")\n";
        return tex;
    }

    tex = SDL_CreateTextureFromSurface(mRenderer, surface);

    if(tex == NULL){
        std::cout << "SDL Create Texture Error: " << SDL_GetError() << '\n';
        SDL_FreeSurface(surface);
        return tex;
    }

    SDL_FreeSurface(surface);
    return tex;
}

void Graphics::ClearBackBuffer(){
    SDL_RenderClear(mRenderer);
}

void Graphics::Render(){
    SDL_RenderPresent(mRenderer);
}

void Graphics::DrawTexture(SDL_Texture * tex, SDL_Rect * clip, SDL_Rect * rend, float angle, SDL_RendererFlip flip){
    SDL_RenderCopyEx(mRenderer, tex, clip, rend, angle, NULL, flip);
}

SDL_Texture * Graphics::CreateTextTexture(TTF_Font * font, std::string text, SDL_Color color){
    SDL_Surface * surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if(surface == NULL){
        std::cout << "Text Render Error: " << TTF_GetError() << '\n';
        return NULL;
    }
    SDL_Texture * Tex = SDL_CreateTextureFromSurface(mRenderer, surface);
    if(Tex == NULL){
        std::cout << "Text Texture Creation Error: " << SDL_GetError() << '\n';
        SDL_FreeSurface(surface);
        return NULL;
    }
    SDL_FreeSurface(surface);
    return Tex;
}

void Graphics::DrawLine(float x_0, float y_0, float x_1, float y_1){

    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(mRenderer, x_0, y_0, x_1, y_1);
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

}