#ifndef SCREEN_MANAGER_H_
#define SCREEN_MANAGER_H_

#include "StartScreen.h"
#include "PlayScreen.h"
//#include "DeathScreen.h"

class ScreenManager{
private:

    enum SCREENS{START = 0, PLAY, DEATH};
    SCREENS mCurrentScreen;

    static ScreenManager * sInstance;
    InputManager * mInput;
    StartScreen * mStartScreen;
    PlayScreen * mPlayScreen;
    //DeathScreen * mDeathScreen;
    
public:

    bool Quit;
    static ScreenManager * Instance();
    static void Release();
    void Update();
    void Render();

private:

    ScreenManager();
    ~ScreenManager();

};

#endif