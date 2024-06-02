#ifndef SCREEN_MANAGER_H_
#define SCREEN_MANAGER_H_

#include "StartScreen.h"
#include "PlayScreen.h"
#include "DeathScreen.h"
#include <fstream>

class ScreenManager{
public:

    enum SCREENS{START = 0, PLAY, SCOREBOARD, DEATH};
    SCREENS mCurrentScreen;
    
private:

    static ScreenManager * sInstance;
    InputManager * mInput;
    AudioManager * mAudioMgr;
    StartScreen * mStartScreen;
    PlayScreen * mPlayScreen;
    DeathScreen * mDeathScreen;

    std::string mScoreFile;
    
public:

    bool Quit;
    static ScreenManager * Instance();
    static void Release();
    void Update();
    void Render();

private:

    ScreenManager();
    ~ScreenManager();

    void SBUpdate(int newScore);
    void CleanFileBuffer(std::fstream mFile);

};

#endif