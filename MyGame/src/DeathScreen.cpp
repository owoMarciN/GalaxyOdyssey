#include "DeathScreen.h"


DeathScreen::DeathScreen(){

    mInput = InputManager::Instance();
    mDeathSurface = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f, Graphics::Instance()->SCREEN_HEIGHT*0.5f));
    mDeathSurface->Parent(this);
    mDeath = new Texture("GAME OVER", "Karmatic_Arcade.ttf", 72, {200, 0, 0});
    mDeath->Parent(mDeathSurface);
    mDeath->Pos(VEC2_ZERO);

}

DeathScreen::~DeathScreen(){
    
    mInput = nullptr;
    
    delete mDeath;
    mDeath = nullptr;

    delete mDeathSurface;
    mDeath = nullptr;

}

void DeathScreen::Update(){

}

void DeathScreen::Render(){
    mDeath->Render();
}