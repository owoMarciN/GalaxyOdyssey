#ifndef BULLETS_H_
#define BULLETS_H_

#include "AnimatedTexture.h"
#include "Timer.h"

class Bullet : public GameEntity{
public:

    enum BULLETTYPE{NORMAL, P_SPECIAL, E_NORMAL, E_BOUNCING, E_TRACKING};
    int mDamage;

private:

    const int OFF_SCREEN_BUFFER = 10;
    Timer * mTimer;

    float mSpeed;
    Texture * mBulletTex;
    BULLETTYPE mCurrType;

    float DirectionX;
    float DirectionY;
    Vector2 PrevDirection;

    int mCountBounces;

    Vector2 mPlayerPos;
    
public:

    Bullet(int damage, BULLETTYPE bType);
    ~Bullet();

    void FireBullet(Vector2 pos);
    void GetPlayerPos(Vector2 pos);
    void Reload();
    void Update();
    void Render();

};

#endif