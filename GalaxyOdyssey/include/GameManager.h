#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include "Timer.h"
#include "InputManager.h"
#include "ScreenManager.h"

class GameManager{
private:

    static const int FRAME_RATE = 120;

    static GameManager * sInstance;
    static bool mQuit;

    Graphics * mGraphics;
    Timer * mTimer;
    AssetManager * mAssetMgr;
    InputManager * mInputMgr;
    AudioManager * mAudioMgr;
    
    SDL_Event mEvents;
    ScreenManager *  mScreenMgr;

public:

    static GameManager * Instance();
    static void Release();
    void Run();

private:

    GameManager();
    ~GameManager();
    void EarlyUpdate();
    void Update();
    void LateUpdate();
    void Render();

};

#endif