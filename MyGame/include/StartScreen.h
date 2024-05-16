#ifndef START_SCREEN_H_
#define START_SCREEN_H_

#include "InputManager.h"
#include "AnimatedTexture.h"

class StartScreen : public GameEntity{
private:

    InputManager * mInput;

    GameEntity * mTopBar;
    Texture * mPlayerOne;
    Texture * mPlayerTwo;
    Texture * mHiScore;

    GameEntity * mPlay;
    Texture * mPlayButton;
    Texture * mExitButton;

    GameEntity * mDownBar;
    Texture * mCreator;

    Texture * mCursor;
    Vector2 mCursorStart;
    Vector2 mCursorOffset;
    int SelectMode;

    SDL_Color color = {230, 230, 230};
    
public:

    StartScreen();
    ~StartScreen();

    int SelectedMode();
    void ChangeMode(int mode);
    void Update();
    void Render();

};


#endif