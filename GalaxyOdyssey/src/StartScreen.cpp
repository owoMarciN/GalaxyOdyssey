#include "StartScreen.h"

StartScreen::StartScreen(){

    mInput = InputManager::Instance();

    mTopBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f, Graphics::Instance()->SCREEN_HEIGHT*0.35f));
    mTitle = new Texture("GALAXY ODYSSEY", "Arcades.ttf", 72, {230,230,230});
    mTitle->Parent(mTopBar);
    mTitle->Pos(VEC2_ZERO);
    mTopBar->Parent(this);

    mPlay = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f, Graphics::Instance()->SCREEN_HEIGHT*0.55f)); 
    mBackGround = new Texture("StartScreen.png");
    mPlayButton = new Texture("PLAY", "Karmatic_Arcade.ttf", 32, {230,230,230});
    mScoreBoard = new Texture("SCORES", "Karmatic_Arcade.ttf", 32, {230,230,230});
    mExitButton = new Texture("EXIT", "Karmatic_Arcade.ttf", 32, {230,230,230});
    mCursor = new Texture("--", "Karmatic_Arcade.ttf", 32, {230,230,230});

    mBackGround->Parent(mPlay);
    mPlayButton->Parent(mPlay);
    mScoreBoard->Parent(mPlay);
    mExitButton->Parent(mPlay);
    mCursor->Parent(mPlay);

    mBackGround->Pos(Vector2(0.0f, -36.0f));
    mPlayButton->Pos(Vector2(-5.0f, -20.0f));
    mScoreBoard->Pos(Vector2(-5.0f, 60.0f));
    mExitButton->Pos(Vector2(-5.0f, 135.0f));
    mCursor->Pos(Vector2(-120.0f, -22.0f));
    mCursorStart = mCursor->Pos(local);
    mCursorOffset = Vector2(0.0f, 78.0f);

    mBackGround->Scale(VEC2_ONE*1.5f);
    SelectMode = 0;

    mPlay->Parent(this);

    mBottomBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.85f, Graphics::Instance()->SCREEN_HEIGHT*0.95f));
    mCreator = new Texture("Created by Marcin Basisty", "Karmatic_Arcade.ttf", 18, {255, 255, 255});

    mCreator->Parent(mBottomBar);
    mCreator->Pos(VEC2_ZERO);

    mBottomBar->Parent(this);
}

StartScreen::~StartScreen(){
    mInput = nullptr;

    delete mTitle;
    mTitle = nullptr;

    delete mBackGround;
    mBackGround = nullptr;

    delete mPlayButton;
    mPlayButton = nullptr;

    delete mScoreBoard;
    mScoreBoard = nullptr;

    delete mExitButton;
    mExitButton = nullptr;

    delete mCursor;
    mCursor = nullptr;

    delete mPlay;
    mPlay = nullptr;

    delete mCreator;
    mCreator = nullptr;

    delete mTopBar;
    mTopBar = nullptr;

    delete mBottomBar;
    mBottomBar = nullptr;
}

void StartScreen::ChangeMode(int mode) {
    SelectMode += mode;
    if (SelectMode < 0)
        SelectMode = 1;
    else if (SelectMode > 1 && SelectMode < 2)
        SelectMode = 2;
    else if (SelectMode > 2)
        SelectMode = 0;
    mCursor->Pos(mCursorStart + mCursorOffset * SelectMode);
}

void StartScreen::Update() {
    if (mInput->KeyPressed(SDL_SCANCODE_S))
        ChangeMode(1);
    else if (mInput->KeyPressed(SDL_SCANCODE_W))
        ChangeMode(-1);
}

int StartScreen::SelectedMode() {
    return SelectMode;
}

void StartScreen::Render() {
    mBackGround->Render();
    mTitle->Render();
    mPlayButton->Render();
    mScoreBoard->Render();
    mExitButton->Render();
    mCursor->Render();
    mCreator->Render();
}