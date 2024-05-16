#include "ScreenManager.h"

ScreenManager * ScreenManager::sInstance = NULL;

ScreenManager * ScreenManager::Instance(){
    if(sInstance == NULL)
        sInstance = new ScreenManager();
    return sInstance;
}

void ScreenManager::Release(){
    delete sInstance;
    sInstance = nullptr;
}

ScreenManager::ScreenManager(){
    Quit = false;
    mStartScreen = new StartScreen();
    // mPlayScreen = new PlayScreen();
    //mDeathScreen = new DeathScreen();
    mInput = InputManager::Instance();
    mCurrentScreen = START;
}

ScreenManager::~ScreenManager(){
    mInput = NULL;
}

void ScreenManager::Update(){
    switch(mCurrentScreen){
        case START:
            mStartScreen->Update();
            if(mInput->KeyPressed(SDL_SCANCODE_RETURN) && !mStartScreen->SelectedMode()){
                mCurrentScreen = PLAY;
                mPlayScreen = new PlayScreen();
            }
            else if(mInput->KeyPressed(SDL_SCANCODE_RETURN) && mStartScreen->SelectedMode())
                Quit = true;
            break;
        case PLAY:
            mPlayScreen->Update();
            if(mInput->KeyPressed(SDL_SCANCODE_ESCAPE)){
                mPlayScreen->~PlayScreen();
                mCurrentScreen = START;
            }
        case DEATH:
            //mDeathScreen->Update();
            break;
    }
}

void ScreenManager::Render(){
    switch(mCurrentScreen){
        case START:
            mStartScreen->Render();
            break;
        case PLAY:
            mPlayScreen->Render();
            break;
        case DEATH:
            //mDeathScreen->Render();
            break;
    }
}