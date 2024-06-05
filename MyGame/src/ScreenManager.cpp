#include "ScreenManager.h"

ScreenManager * ScreenManager::sInstance = NULL;

ScreenManager * ScreenManager::Instance(){
    if(sInstance == nullptr)
        sInstance = new ScreenManager();
    return sInstance;
}

void ScreenManager::Release(){
    delete sInstance;
    sInstance = nullptr;
}

ScreenManager::ScreenManager(){
    Quit = false;
    mScoreFile = "./ScoreBoard.txt";

    mStartScreen = new StartScreen();
    mPlayScreen = new PlayScreen();
    mDeathScreen = new DeathScreen();

    mInput = InputManager::Instance();
    mAudioMgr = AudioManager::Instance();

    //mAudioMgr->PlayMusic("MenuMusic.mp3");

    mCurrentScreen = START;
}

ScreenManager::~ScreenManager(){
    mInput = nullptr;

    mAudioMgr = nullptr;
    
    delete mStartScreen;
    mStartScreen = nullptr;

    delete mPlayScreen;
    mPlayScreen = nullptr;

    delete mDeathScreen;
    mDeathScreen = nullptr;

}

void ScreenManager::Update(){

    if(!mPlayScreen->mPlayer->Active() && mPlayScreen != nullptr){
        delete mPlayScreen;
        mPlayScreen = nullptr;
        mCurrentScreen = DEATH;
    }

    if(mPlayScreen == nullptr)
        mPlayScreen = new PlayScreen();

    switch(mCurrentScreen){
        case START:
            mStartScreen->Update();

            // if(!Mix_PlayingMusic())
            //     mAudioMgr->PlayMusic("MenuMusic.mp3");
            
            if(mInput->KeyPressed(SDL_SCANCODE_RETURN) && !mStartScreen->SelectedMode()){
                //mAudioMgr->PauseMusic();
                mCurrentScreen = PLAY;
            }
            else if(mInput->KeyPressed(SDL_SCANCODE_RETURN) && mStartScreen->SelectedMode())
                Quit = true;
            break;
        case PLAY:
            mPlayScreen->Update();
            if(mInput->KeyPressed(SDL_SCANCODE_ESCAPE)){
                mCurrentScreen = START;
            }
        case SCOREBOARD:
            break;
        case DEATH:
            mDeathScreen->Update();
            
            // if(!Mix_PlayingMusic())
            //     mAudioMgr->PlayMusic("DeathSound.mp3");

            SBUpdate(mPlayScreen->GetScore());
            if(mInput->KeyPressed(SDL_SCANCODE_RETURN) && mDeathScreen->SelectedMode() == 0){
                mCurrentScreen = PLAY;
            }
            else if(mInput->KeyPressed(SDL_SCANCODE_RETURN) && mDeathScreen->SelectedMode() == 1){
                mCurrentScreen = START;

            }
            else if(mInput->KeyPressed(SDL_SCANCODE_ESCAPE)){
                Quit = true;
            }
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
        case SCOREBOARD:
            break;
        case DEATH:
            mDeathScreen->Render();
            break;
    }
}

void ScreenManager::SBUpdate(int newScore){
    if(newScore > 0){
        std::ofstream mFile(mScoreFile, std::ofstream::in | std::ofstream::out);
        if(mFile.is_open()){
            std::cerr << "[Error]: File doesn't exists!\n";
        }
        mFile.close();
    }
}

void ScreenManager::CleanFileBuffer(std::fstream mFile){

}