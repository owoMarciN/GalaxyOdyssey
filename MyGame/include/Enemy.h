#ifndef ENEMY_H_
#define ENEMY_H_

#include "AnimatedTexture.h"
#include "BezierPath.h"
#include "Bullets.h"

class Enemy : public GameEntity{
private:

    static std::vector<std::vector<Vector2>> sPaths;

    enum STATES{FLY, FORMATION, DIVE, DEAD};

    Timer * mTimer;

    Texture * mTexture;
    STATES mCurrState;

    unsigned int mCurrPath;
    unsigned int mCurrWayPoint;
    const float EPSIOLON = 5.0f;

    float mSpeed;

    Uint32 mLastFiredTime = 0;  // Time when the last bullet was fired
    const Uint32 mFireDelay = 500;

public:

    int mHP;
    int mDamage;

    static const int MAX_BULLETS = 3;
    std::unique_ptr<Bullet[]> mBullet;

public:

    static void createPaths();

    Enemy(int path);
    virtual ~Enemy();

    virtual void HandleFlyState();
    virtual void HandleFormationState();
    virtual void HandleDiveState();
    virtual void HandleDeadState();
    void HandleMovement();
    void HandleFiring();

    void HandleStates();
    void LoseHP(int change);
    void Update();
    void Render();

};

#endif