#ifndef PLAYER_H_
#define PLAYER_H_

#include "InputManager.h"
#include "Bullets.h"

class Player : public GameEntity{
private:

    Timer * mTimer;
    InputManager * mInput;
    /////
    Texture *  mShip;
    float mSpeed;

    Uint32 mLastFiredTime = 0;  // Time when the last bullet was fired
    const Uint32 mFireDelay = 400;

public:

    static const int MAX_BULLETS = 3;
    std::unique_ptr<Bullet[]> mBullet;

    std::unique_ptr<Bullet> mSpecialAttack;

    int mScore;

    //AudioManager * mAudio;
    
public:

    int mHP;
    int mDamage;
    
private:

    void HandleMovement();
    void HandleFiring();

public:

    Player();
    ~Player();
    int Score();
    void LoseHP(int change);
    void AddScore(int change);
    void Update();
    void Render();

};

const Vector2 mBoundsX = {30, 1250};
const Vector2 mBoundsY = {700, 380};

#endif