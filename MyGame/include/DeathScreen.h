#ifndef DEATH_SCREEN_H_
#define DEATH_SCREEN_H_

#include "InputManager.h"
#include "Texture.h"

class DeathScreen : public GameEntity{
private:

    InputManager * mInput;
    
    GameEntity * mDeathSurface;
    Texture * mBackground;
    Texture * mDeath;

    Texture * mRestart;
    Texture * mMenu;
    Texture * mCursor;

    Vector2 mCursorStart;
    Vector2 mCursorOffset;

    int SelectMode;

public:

    DeathScreen();
    ~DeathScreen();
    int SelectedMode();
    void ChangeMode(int mode);
    void Update();
    void Render();

};

#endif