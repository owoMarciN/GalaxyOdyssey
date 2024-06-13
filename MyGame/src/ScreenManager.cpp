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
    mStartScreen = new StartScreen();
    mPlayScreen = new PlayScreen();
    mScoreBoard = new ScoreBoard();
    mDeathScreen = new DeathScreen();
    mWinScreen = new WinScreen();

    mInput = InputManager::Instance();
    mAudioMgr = AudioManager::Instance();

    mCurrentScreen = START;

    ExitEvent(false);
}

ScreenManager::~ScreenManager(){
    mInput = nullptr;

    mAudioMgr = nullptr;
    
    delete mStartScreen;
    mStartScreen = nullptr;

    delete mPlayScreen;
    mPlayScreen = nullptr;

    delete mScoreBoard;
    mScoreBoard = nullptr;

    delete mDeathScreen;
    mDeathScreen = nullptr;

    delete mWinScreen;
    mWinScreen = nullptr;
}

void ScreenManager::Update(){
    PlayScreenEvent();
    switch(mCurrentScreen){
        case START:
            mStartScreen->Update();
            // if(!Mix_PlayingMusic())
            //     mAudioMgr->PlayMusic("MenuMusic.mp3");
            // mAudioMgr->ResumeMusic(); 
            if(mInput->KeyPressed(SDL_SCANCODE_RETURN) && mStartScreen->SelectedMode() == 0){
                // mAudioMgr->PauseMusic();
                mCurrentScreen = PLAY;
            }
            else if(mInput->KeyPressed(SDL_SCANCODE_RETURN) && mStartScreen->SelectedMode() == 2)
                ExitEvent(true);
            else if(mInput->KeyPressed(SDL_SCANCODE_RETURN) && mStartScreen->SelectedMode() == 1)
                mCurrentScreen = SCOREBOARD;
            break;
        case PLAY:
            mPlayScreen->Update();
            if(mInput->KeyPressed(SDL_SCANCODE_ESCAPE)){
                mCurrentScreen = START;
            }
        case SCOREBOARD:
            mScoreBoard->Update();
            if(mInput->KeyPressed(SDL_SCANCODE_ESCAPE)){
                mCurrentScreen = START;
            }
            else if(mInput->KeyPressed(SDL_SCANCODE_RETURN)){
                mCurrentScreen = START;
            }
            break;
        case DEATH:
            mDeathScreen->Update();
            // if(!Mix_PlayingMusic())
            //     mAudioMgr->PlayMusic("DeathSound.mp3");
            if(mInput->KeyPressed(SDL_SCANCODE_RETURN) && mDeathScreen->SelectedMode() == 0){
                mCurrentScreen = PLAY;
            }
            else if(mInput->KeyPressed(SDL_SCANCODE_RETURN) && mDeathScreen->SelectedMode() == 1){
                mCurrentScreen = START;
            }
            else if(mInput->KeyPressed(SDL_SCANCODE_ESCAPE)){
                ExitEvent(true);
            }
            break;
        case WIN:
            if(mInput->KeyPressed(SDL_SCANCODE_RETURN)){
                mCurrentScreen = START;
            }
            else if(mInput->KeyPressed(SDL_SCANCODE_ESCAPE)){
                ExitEvent(true);
            }
            break;
    }
}

void ScreenManager::PlayScreenEvent(){
    if(!mPlayScreen->PlayerActive() && mPlayScreen != nullptr){
        mScoreBoard->SetNewScore(mPlayScreen->GetScore());
        delete mPlayScreen;
        mPlayScreen = nullptr;
        mCurrentScreen = DEATH;
    }
    else if(!mPlayScreen->BossActive() && mPlayScreen != nullptr){
        mScoreBoard->SetNewScore(mPlayScreen->GetScore());
        delete mPlayScreen;
        mPlayScreen = nullptr;
        mCurrentScreen = WIN;
    }

    if(mPlayScreen == nullptr)
        mPlayScreen = new PlayScreen();
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
            mScoreBoard->Render();
            break;
        case DEATH:
            mDeathScreen->Render();
            break;
        case WIN:
            mWinScreen->Render();
            break;
    }
}

bool ScreenManager::ExitEvent(){
    return mQuit;
}

void ScreenManager::ExitEvent(bool quit){
    mQuit = quit;
}