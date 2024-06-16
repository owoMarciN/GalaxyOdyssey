#ifndef SCREEN_MANAGER_H_
#define SCREEN_MANAGER_H_

#include "StartScreen.h"
#include "PlayScreen.h"
#include "DeathScreen.h"
#include "ScoreBoard.h"
#include "WinScreen.h"

class ScreenManager{
public:

    enum SCREENS{START, PLAY, SCOREBOARD, DEATH, WIN};
    SCREENS mCurrentScreen;
    
private:

    static ScreenManager * sInstance;

    InputManager * mInput;
    AudioManager * mAudioMgr;

    StartScreen * mStartScreen;
    PlayScreen * mPlayScreen;
    ScoreBoard * mScoreBoard;
    DeathScreen * mDeathScreen;
    WinScreen * mWinScreen;

    bool mQuit;
    
public:

    static ScreenManager * Instance();
    static void Release();
    bool ExitEvent();
    void Update();
    void Render();

private:

    ScreenManager();
    ~ScreenManager();

    void ExitEvent(bool quit);
    void PlayScreenEvent();

};

#endif