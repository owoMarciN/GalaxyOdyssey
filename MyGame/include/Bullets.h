#ifndef BULLETS_H_
#define BULLETS_H_

#include "AnimatedTexture.h"
#include "MathHelper.h"
#include "Timer.h"
#include <vector>

class Bullet : public GameEntity{
public:

    enum BULLETTYPE{NORMAL, P_SPECIAL, E_NORMAL, E_BOUNCING};
    int mDamage;

private:

    const int OFF_SCREEN_BUFFER = 10;
    Timer * mTimer;

    float mSpeed;
    Texture * mBullet;
    BULLETTYPE mCurrType;

    float DirectionX;
    float DirectionY;

    int mCountBounces;
    
public:

    //Bullet();
    Bullet(int damage, float speed, float rotation, BULLETTYPE bTypeBullet);
    ~Bullet();

    void FireBullet(Vector2 pos);
    void Reload();
    void Update();
    void Render();

};

#endif