#ifndef PLAY_SCREEN_H_
#define PLAY_SCREEN_H_

#include "Player.h"
//#include "Boss.h"
#include "Enemy.h"

class PlayScreen : public GameEntity{
private:

    InputManager * mInput;
    
    GameEntity * mBackGround;
    std::unique_ptr<Texture> mCosmos;

    std::unique_ptr<Player> mPlayer;
    //std::unique_ptr<Boss> mBoss;
    Enemy * mEnemy;
    //
public:

    PlayScreen();
    ~PlayScreen();

    // int SelectedMode();
    // void ChangeMode(int mode);
    void HandleBossCollision();
    void HandlePlayerCollision();
    void Update();
    void Render();

};



#endif