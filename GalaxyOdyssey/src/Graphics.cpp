#include "Graphics.h"

Graphics * Graphics::sInstance = nullptr;

bool Graphics::sInitialized = false;

Graphics * Graphics::Instance() {
    if (sInstance == nullptr)
        sInstance = new Graphics;

    return sInstance;
}

bool Graphics::Initialized() {
    return sInitialized;
}

void Graphics::Release() {
    delete sInstance;
    sInstance = nullptr;

    sInitialized = false;
}

Graphics::Graphics() {
    sInitialized = Init();
}

Graphics::~Graphics() {
    SDL_DestroyWindow(mWindow);
    mWindow = nullptr;

    SDL_DestroyRenderer(mRenderer);
    mRenderer = nullptr;

    mIcon = nullptr;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool Graphics::Init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cout << "[ERROR]: SDL2 could not INITIALIZE!\n" << SDL_GetError() << '\n';
        return false;
    }

    mWindow = SDL_CreateWindow("GALAXY ODYSSEY", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (mWindow == nullptr) {
        std::cout << "[ERROR]: Window couldn't be CREATED!\n" << SDL_GetError() << '\n';
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
    if (mRenderer == nullptr) {
        std::cout << "[ERROR]: Renderer couldn't be INITIALIZED!\n" << SDL_GetError() << '\n';
        return false;
    }

    mIcon = IMG_Load("Assets/Textures/Icon.png");
    SDL_SetWindowIcon(mWindow, mIcon);
    SDL_FreeSurface(mIcon);

    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0x00);

    int flags = IMG_INIT_PNG;
    if (!IMG_Init(flags) && flags) {
        std::cout << "[ERROR]: SDL2_IMAGE couldn't be INITIALIZED!\n" << IMG_GetError() << '\n';
        return false;
    }

    if (TTF_Init() == -1) {
        std::cout << "[ERROR]: SDL2_TTF couldn't be INITIALIZED!\n" << TTF_GetError() << '\n';
        return false;
    }

    return true;
}

SDL_Texture * Graphics::loadTexture(std::string path){
    SDL_Texture * mTexture = nullptr;
    SDL_Surface * mSurface = IMG_Load(path.c_str());
    if (mSurface == nullptr) {
        std::cout << "[ERROR]: IMG Load error: Path (" << path << ")\n" << IMG_GetError() << '\n';
        return mTexture;
    }

    mTexture = SDL_CreateTextureFromSurface(mRenderer, mSurface);
    if (mTexture == nullptr)
        std::cout << "[ERROR]: SDL Create texture error: " << SDL_GetError() << '\n';

    SDL_FreeSurface(mSurface);
    return mTexture;
}

void Graphics::ClearBackBuffer(){
    SDL_RenderClear(mRenderer);
}

void Graphics::Render(){
    SDL_RenderPresent(mRenderer);
}

void Graphics::DrawTexture(SDL_Texture * tex, SDL_Rect * clip, SDL_Rect * rend, float angle, SDL_RendererFlip flip){
    SDL_RenderCopyEx(mRenderer, tex, clip, rend, angle, nullptr, flip);
}

SDL_Texture * Graphics::CreateTextTexture(TTF_Font * font, std::string text, SDL_Color color){
    SDL_Texture * mTexture = nullptr;
    SDL_Surface * mSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (mSurface == nullptr) {
        std::cout << "[ERROR]: TTF Load error: " << TTF_GetError() << '\n';
        return mTexture;
    }

    mTexture = SDL_CreateTextureFromSurface(mRenderer, mSurface);

    if (mTexture == nullptr)
        std::cout << "[ERROR]: SDL Create texture error: " << SDL_GetError() << '\n';

    SDL_FreeSurface(mSurface);
    return mTexture;
}

void Graphics::DrawLine(float x_0, float y_0, float x_1, float y_1){
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(mRenderer, x_0, y_0, x_1, y_1);
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}
