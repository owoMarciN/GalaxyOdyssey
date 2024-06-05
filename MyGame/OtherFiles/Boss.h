#ifndef BOSS_H_
#define BOSS_H_

#include "AnimatedTexture.h"
//#include "BezierPath.h"
#include "Bullets.h"

class Boss : public GameEntity {
private:

    Timer* mTimer;

    Texture * mTexture;
    float mSpeed;
    int mDirection;
    
    Uint32 mLastFiredTime = 0;  // Time when the last bullet was fired
    const Uint32 mFireDelay = 500;
    
public:

    static const int MAX_BULLETS = 3;
    std::unique_ptr<Bullet[]> mBullet;

    int mHP;
    int mDamage;
    int mPoints;
    
private:
    void HandleMovement();
    void HandleFiring();

public:
    Boss();
    ~Boss();
    void LoseHP(int change);
    void Update();
    void Render();
};

const Vector2 mBounds = {100, 1180};

#endif
