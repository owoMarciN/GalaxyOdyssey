#ifndef ENEMY_H_
#define ENEMY_H_

#include "HostileEntity.h"

class Enemy : public HostileEntity{
private:

    Texture * mEnemyTex;
    AnimatedTexture  * mDestruction;

public:

    enum ENEMYTYPES{ALPHA, BETA, GAMMA};
    ENEMYTYPES mType;
    
    static const int MAX_BULLETS;
    std::vector<Bullet*> mBullet;

    Uint32 mLastFiredTime = 0;  // Time when the last bullet was fired
    const Uint32 mFireDelay = 1000;
    
public:
    
    Enemy(int path, ENEMYTYPES mEnemy = ALPHA);
    virtual ~Enemy();

    void HandleFiring();
    bool DestructionDone();
    void Update();
    void Render();

};

#endif