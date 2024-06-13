#include "GameManager.h"

GameManager * GameManager::sInstance = NULL;

GameManager * GameManager::Instance(){
    if(sInstance == NULL)
        sInstance = new GameManager();
    return sInstance;
}

void GameManager::Release(){
    delete sInstance;
    sInstance = NULL;
}

GameManager::GameManager(){
    mQuit = false;
    mGraphics = Graphics::Instance();
    if(!Graphics::Initialized())
        mQuit = true;

    mAssetMgr = AssetManager::Instance();
    mInputMgr = InputManager::Instance();
    mAudioMgr = AudioManager::Instance();
    mTimer = Timer::Instance();

    mScreenMgr = ScreenManager::Instance();
}

GameManager::~GameManager(){
    ScreenManager::Release();
    mScreenMgr = NULL;
    
    AudioManager::Release();
	mAudioMgr = NULL;

    AssetManager::Release();
    mAssetMgr = NULL;

    Graphics::Release();
    mGraphics = NULL;

    InputManager::Release();
    mInputMgr = NULL;
    
    Timer::Release();
    mTimer = NULL;
}

void GameManager::EarlyUpdate(){
    mScreenMgr->Update();
    mInputMgr->Update();
}

void GameManager::Update() {
	//GameEntity Updates should happen here
    mTimer->Reset();
}

void GameManager::LateUpdate() {
	//Any collision detection should happen here
	mInputMgr->UpdatePrevInput();
}

void GameManager::Render() {
	//Clears the last frame's render from the back buffer
	mGraphics->ClearBackBuffer();

	//All other rendering is to happen here
    mScreenMgr->Render();

	//Renders the current frame
	mGraphics->Render();
}

void GameManager::Run(){
    while(!mQuit){
        mTimer->Update();
        while(SDL_PollEvent(&mEvents) != 0){
            if(mScreenMgr->ExitEvent())
                mQuit = true;
            switch(mEvents.type){
                case SDL_QUIT: 
                    mQuit = true;
                    break;
            } 
        }
        if(mTimer->DeltaTime() >= (1.0f / FRAME_RATE)){ 
            EarlyUpdate();
            Update();
            LateUpdate();
            Render();
        }
    }
}