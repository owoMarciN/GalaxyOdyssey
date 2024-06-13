#ifndef WIN_SCREEN_H_
#define WIN_SCREEN_H_

#include "Texture.h"
#include "InputManager.h"

class WinScreen : GameEntity{
private:

    InputManager * mInput;
    
    GameEntity * mWinScreen;
    Texture * mBackground;
    Texture * mWin;

    Texture * mBackToMenu;

public:

    WinScreen();
    ~WinScreen();

    void Update();
    void Render();

};

#endif