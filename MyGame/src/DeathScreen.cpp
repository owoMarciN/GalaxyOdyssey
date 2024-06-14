#include "DeathScreen.h"


DeathScreen::DeathScreen(){

    mInput = InputManager::Instance();

    mDeathSurface = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f, Graphics::Instance()->SCREEN_HEIGHT*0.5f));
    mBackground = new Texture("DeathSurface.jpg");
    mDeath = new Texture("MISSION FAILED!" , "Arcade_Classic.ttf", 96, {255, 0, 0});
    mRestart = new Texture("RESTART", "Arcade_Classic.ttf", 48, {230, 230, 230});
    mMenu = new Texture("MENU", "Arcade_Classic.ttf", 48, {230, 230, 230});
    mCursor = new Texture("--", "Karmatic_Arcade.ttf", 32, {230,230,230});

    mBackground->Parent(mDeathSurface);
    mDeath->Parent(mDeathSurface);
    mRestart->Parent(mDeathSurface);
    mMenu->Parent(mDeathSurface);
    mCursor->Parent(mDeathSurface);

    mBackground->Pos(VEC2_ZERO);
    mDeath->Pos(Vector2(0.0f, -100.0f));
    mRestart->Pos(Vector2(-10.0f, 60.0f));
    mMenu->Pos(Vector2(-10.0f, 135.0f));
    mCursor->Pos(Vector2(-150.0f, 55.0f));
    mCursorStart = mCursor->Pos(local);
    mCursorOffset = Vector2(0.0f, 77.0f);
    SelectMode = 0;

    mDeathSurface->Parent(this);

}

DeathScreen::~DeathScreen(){
    mInput = nullptr;
    
    delete mBackground;
    mBackground = nullptr;

    delete mRestart;
    mRestart = nullptr;

    delete mMenu;
    mMenu = nullptr;

    delete mCursor;
    mCursor = nullptr;

    delete mDeath;
    mDeath = nullptr;

    delete mDeathSurface;
    mDeath = nullptr;

}

void DeathScreen::ChangeMode(int mode){
    SelectMode += mode;
    if(SelectMode < 0)
        SelectMode = 1;
    else if(SelectMode > 1)
        SelectMode = 0;
    mCursor->Pos(mCursorStart + mCursorOffset * SelectMode);
}

void DeathScreen::Update(){
    if(mInput->KeyPressed(SDL_SCANCODE_S))
        ChangeMode(1);
    else if(mInput->KeyPressed(SDL_SCANCODE_W))
        ChangeMode(-1);
}

int DeathScreen::SelectedMode(){
    return SelectMode;
}

void DeathScreen::Render(){
    mBackground->Render();
    mDeath->Render();
    mRestart->Render();
    mMenu->Render();
    mCursor->Render();
}