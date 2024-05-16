#ifndef DEATH_SCREEN_H_
#define DEATH_SCREEN_H_

#include "InputManager.h"
#include "Texture.h"
#include <memory>
//#include "Enemy.h"

class DeathScreen : public GameEntity{
private:

    InputManager * mInput;
    
    GameEntity * mDeathSurface;
    Texture * mDeath;

    //Enemy * mEnemy;
    //
public:

    DeathScreen();
    ~DeathScreen();

    void Update();
    void Render();

};

#endif