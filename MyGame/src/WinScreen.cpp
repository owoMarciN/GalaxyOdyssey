#include "WinScreen.h"

WinScreen::WinScreen(){
    mInput = InputManager::Instance();
    
    mWinScreen = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f, Graphics::Instance()->SCREEN_HEIGHT*0.5f));

    mBackground = new Texture("WinScreen.png");

    mBackToMenu = new Texture("PRESS --ENTER-- TO CONTINUE" , "Karmatic_Arcade.ttf", 32, {255, 255, 200});

    mBackground->Parent(mWinScreen);
    mBackToMenu->Parent(mWinScreen);

    mBackground->Pos(VEC2_ZERO);
    mBackToMenu->Pos(Vector2(0.0f, 100.0f));

    mWinScreen->Parent(this);
}

WinScreen::~WinScreen(){
    mInput = nullptr;

    delete mBackground;
    mBackground = nullptr;

    delete mBackToMenu;
    mBackToMenu = nullptr;

    delete mWinScreen;
    mWinScreen = nullptr;
}

void WinScreen::Update(){

}

void WinScreen::Render(){
    mBackground->Render();
    mBackToMenu->Render();
}