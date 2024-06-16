#ifndef START_SCREEN_H_
#define START_SCREEN_H_

#include "InputManager.h"
#include "AnimatedTexture.h"

class StartScreen : public GameEntity{
private:

    InputManager * mInput;
    
    GameEntity * mTopBar;
    Texture * mTitle;

    GameEntity * mPlay;
    Texture * mBackGround;
    Texture * mPlayButton;
    Texture * mScoreBoard;
    Texture * mExitButton;

    GameEntity * mBottomBar;
    Texture * mCreator;
    Texture * mCursor;

    Vector2 mCursorStart;
    Vector2 mCursorOffset;
    int SelectMode;

public:

    StartScreen();
    ~StartScreen();

    int SelectedMode();
    void ChangeMode(int mode);
    void Update();
    void Render();

};


#endif