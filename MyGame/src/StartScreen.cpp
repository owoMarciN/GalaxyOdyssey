#include "StartScreen.h"

StartScreen::StartScreen(){

    mInput = InputManager::Instance();

    mTopBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f, 80.0f));
    mPlayerOne = new Texture("1UP", "Karmatic_Arcade.ttf", 32, {200, 0, 0});
    mHiScore = new Texture("HI-SCORE", "Karmatic_Arcade.ttf", 32, {200, 0, 0});
    mPlayerTwo = new Texture("2UP", "Karmatic_Arcade.ttf", 32, {200, 0, 0});

    mPlayerOne->Parent(mTopBar);
    mHiScore->Parent(mTopBar);
    mPlayerTwo->Parent(mTopBar);

    mPlayerOne->Pos(Vector2(-Graphics::Instance()->SCREEN_WIDTH*0.35f, 0.0f));
    mHiScore->Pos(Vector2(-10.0f, 0.0f));
    mPlayerTwo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.35f, 0.0f));

    mTopBar->Parent(this);  

    mPlay = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f, Graphics::Instance()->SCREEN_HEIGHT*0.55f));  
    mPlayButton = new Texture("PLAY", "Karmatic_Arcade.ttf", 32, color);
    mExitButton = new Texture("EXIT", "Karmatic_Arcade.ttf", 32, color);
    mCursor = new Texture("--", "Karmatic_Arcade.ttf", 32, color);

    mPlayButton->Parent(mPlay);
    mExitButton->Parent(mPlay);
    mCursor->Parent(mPlay);

    mPlayButton->Pos(Vector2(-10.0f, -15.0f));
    mExitButton->Pos(Vector2(-10.0f, 60.0f));
    mCursor->Pos(Vector2(-100.0f, -17.0f));
    mCursorStart = mCursor->Pos(local);
    mCursorOffset = Vector2(0.0f, 77.0f);
    SelectMode = 0;

    mPlay->Parent(this);

    mDownBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.85f, Graphics::Instance()->SCREEN_HEIGHT*0.95f));
    mCreator = new Texture("Created by Marcin Basisty", "Karmatic_Arcade.ttf", 18, {255, 255, 255});

    mCreator->Parent(mDownBar);
    mCreator->Pos(VEC2_ZERO);

    mDownBar->Parent(this);
}

StartScreen::~StartScreen(){
    delete mPlayerOne;
    mPlayerOne = NULL;
    
    delete mHiScore;
    mHiScore = NULL;

    delete mPlayerTwo;
    mPlayerTwo = NULL;

    delete mTopBar;
    mTopBar = NULL;

    delete mPlayButton;
    mPlayButton = NULL;

    delete mExitButton;
    mExitButton = NULL;

    delete mCursor;
    mCursor = NULL;

    delete mPlay;
    mPlay = NULL;

    delete mCreator;
    mCreator = NULL;

    delete mDownBar;
    mDownBar = NULL;

}

void StartScreen::ChangeMode(int mode){
    SelectMode += mode;
    if(SelectMode < 0)
        SelectMode = 1;
    else if(SelectMode > 1)
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
    mPlayerOne->Render();
    mPlayerTwo->Render();
    mHiScore->Render();

    mPlayButton->Render();
    mExitButton->Render();
    mCursor->Render();

    mCreator->Render();
}