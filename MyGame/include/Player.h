#ifndef PLAYER_H_
#define PLAYER_H_

#include "InputManager.h"
#include "AudioManager.h"
#include "Bullets.h"

class Player : public GameEntity{
private:

    Timer * mTimer;
    InputManager * mInput;
    AudioManager * mAudio;

    Texture *  mShip;
    float mSpeed;
    int mHP;

    Uint32 mLastBulletFired = 0;  // Time when the last bullet was fired
    Uint32 mLastSpecialFired = 0;
    const Uint32 mFireDelay = 400;
    const Uint32 mSpecialLoading = 3000;
    bool mSpecialFired;

public:

    static const int MAX_BULLETS = 3;
    std::vector<Bullet*> mBullet;

    Bullet * mSpecialAttack;
    
private:

    void HandleMovement();
    void HandleFiring();

public:

    Player();
    ~Player();
    void LoseHP(int change);
    void SpecialFired(bool state);
    bool SpecialFired();
    int GetHP();
    void Update();
    void Render();

};

const Vector2 mBoundsX = {30, 1250};
const Vector2 mBoundsY = {700, 380};

#endif