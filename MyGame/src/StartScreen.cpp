#include "StartScreen.h"

StartScreen::StartScreen(){

    mInput = InputManager::Instance();

    mTopBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f, Graphics::Instance()->SCREEN_HEIGHT*0.35f));
    mTitle = new Texture("TerraFormers", "Arcades.ttf", 72, {230,230,230});
    mTitle->Parent(mTopBar);
    mTitle->Pos(VEC2_ZERO);
    mTopBar->Parent(this);

    mPlay = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f, Graphics::Instance()->SCREEN_HEIGHT*0.55f));  
    mPlayButton = new Texture("PLAY", "Karmatic_Arcade.ttf", 32, {230,230,230});
    mScoreBoard = new Texture("SCORE", "Karmatic_Arcade.ttf", 32, {230,230,230});
    mExitButton = new Texture("EXIT", "Karmatic_Arcade.ttf", 32, {230,230,230});
    mCursor = new Texture("--", "Karmatic_Arcade.ttf", 32, {230,230,230});

    mPlayButton->Parent(mPlay);
    mScoreBoard->Parent(mPlay);
    mExitButton->Parent(mPlay);
    mCursor->Parent(mPlay);

    mPlayButton->Pos(Vector2(-5.0f, -15.0f));
    mScoreBoard->Pos(Vector2(-5.0f, 60.0f));
    mExitButton->Pos(Vector2(-5.0f, 135.0f));
    mCursor->Pos(Vector2(-100.0f, -22.0f));
    mCursorStart = mCursor->Pos(local);
    mCursorOffset = Vector2(0.0f, 77.0f);
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

    delete mPlayButton;
    mPlayButton = NULL;

    delete mScoreBoard;
    mScoreBoard = NULL;

    delete mExitButton;
    mExitButton = NULL;

    delete mCursor;
    mCursor = NULL;

    delete mPlay;
    mPlay = NULL;

    delete mCreator;
    mCreator = NULL;

    delete mTopBar;
    mTopBar = nullptr;

    delete mBottomBar;
    mBottomBar = NULL;

}

void StartScreen::ChangeMode(int mode){
    SelectMode += mode;
    if(SelectMode < 0)
        SelectMode = 1;
    else if(SelectMode > 1 && SelectMode < 2)
        SelectMode = 2;
    else if(SelectMode > 2)
        SelectMode = 0;
    mCursor->Pos(mCursorStart + mCursorOffset * SelectMode);
}

void StartScreen::Update(){
    if(mInput->KeyPressed(SDL_SCANCODE_S))
        ChangeMode(1);
    else if(mInput->KeyPressed(SDL_SCANCODE_W))
        ChangeMode(-1);
}

int StartScreen::SelectedMode(){
    return SelectMode;
}

void StartScreen::Render(){
    mTitle->Render();
    mPlayButton->Render();
    mScoreBoard->Render();
    mExitButton->Render();
    mCursor->Render();
    mCreator->Render();
}