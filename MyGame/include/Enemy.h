#ifndef ENEMY_H_
#define ENEMY_H_

#include "AnimatedTexture.h"
#include "BezierPath.h"
#include "Bullets.h"

class Enemy : public GameEntity{
public:

    enum STATES{FLY, FORMATION, DEAD};
    enum ENEMYTYPES{ALPHA, BETA, GAMMA};

private:

    static std::vector<std::vector<Vector2>> sPaths;
    static unsigned int sPathsNumber;

    Timer * mTimer;

    Texture * mEnemyTex;
    STATES mCurrState;
    unsigned int mCurrPath;
    unsigned int mCurrWayPoint;
    const float EPSIOLON = 5.0f;

    float mSpeed;

    Uint32 mLastFiredTime = 0;  // Time when the last bullet was fired
    const Uint32 mFireDelay = 1000;

public:

    //Create GET functions
    ENEMYTYPES mType;
    int mHP;
    unsigned int mScore;
    bool mInPosition;
    bool mNoCollisions;

    void GetPlayerPos(Vector2 pos);

    static const int MAX_BULLETS = 3;
    std::vector<Bullet*> mBullet;

protected:

    virtual void HandleFlyState();
    virtual void HandleFormationState();
    virtual void HandleDeadState();
    void HandleStates();

public:

    static void createPaths(Vector2 vec1, Vector2 vec2, Vector2 vec3, Vector2 vec4, int samples);
    static bool sPathsEmpty();

    Enemy(int path, ENEMYTYPES mEnemy = ALPHA);
    virtual ~Enemy();

    void HandleFiring();

    void LoseHP(int change);

    void InPosition(bool inPos);
    bool InPosition();

    void NoCollisions(bool noCol);
    bool NoCollisions();

    STATES currState();

    void Update();
    void Render();

};

#endif