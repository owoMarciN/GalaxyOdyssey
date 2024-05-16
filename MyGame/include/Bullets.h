#ifndef BULLETS_H_
#define BULLETS_H_

#include "AnimatedTexture.h"
#include "MathHelper.h"
#include "Timer.h"
#include <memory>

class Bullet : public GameEntity{
private:

    enum BULLETTYPE{NORMAL, P_SPECIAL, E_NORMAL, E_BOUNCING};
    const int OFF_SCREEN_BUFFER = 10;
    Timer * mTimer;
    float mSpeed;
    Texture * mBullet;
    int mDamage;
    
public:

    Bullet();
    // Bullet(int damage = 20, float rotation = 0, BULLETTYPE bType = NORMAL);
    ~Bullet();

    void FireBullet(Vector2 pos);
    void Reload();
    void Update();
    void Render();

};

#endif