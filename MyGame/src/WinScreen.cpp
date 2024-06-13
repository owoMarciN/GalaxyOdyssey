#include "WinScreen.h"

WinScreen::WinScreen(){
    mInput = InputManager::Instance();
    
    mWinScreen = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f, Graphics::Instance()->SCREEN_HEIGHT*0.5f));

    mBackground = new Texture("DeathSurface.jpg");
    mWin = new Texture("YOU'VE MADE IT!" , "Karmatic_Arcade.ttf", 72, {100, 255, 200});

    mBackToMenu = new Texture("PRESS --ENTER-- TO CONTINUE" , "Karmatic_Arcade.ttf", 32, {100, 255, 200});

    mBackground->Parent(mWinScreen);
    mWin->Parent(mWinScreen);
    mBackToMenu->Parent(mWinScreen);

    mBackground->Pos(VEC2_ZERO);
    mWin->Pos(Vector2(0.0f, -200.0f));
    mBackToMenu->Pos(Vector2(0.0f, 100.0f));

    mWinScreen->Parent(this);
}

//English 124p
WinScreen::~WinScreen(){
    mInput = nullptr;

    delete mWin;
    mWin = nullptr;

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
    mWin->Render();
    mBackToMenu->Render();
}