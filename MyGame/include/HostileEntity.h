#ifndef HOSTILE_ENTITY_H_
#define HOSTILE_ENTITY_H_

#include "AnimatedTexture.h"
#include "BezierPath.h"
#include "Bullets.h"

class HostileEntity : public GameEntity{
protected:

    enum STATES{FLY, FORMATION, DEAD};
    static std::vector<std::vector<Vector2>> sPaths;
    static unsigned int sPathsNumber;

    Timer * mTimer;

    STATES mCurrState;
    unsigned int mCurrPath;
    unsigned int mCurrWayPoint;
    const float EPSIOLON = 5.0f;

    float mSpeed;
    int mHP;

public:

    unsigned int mScore;
    bool mInPosition;
    bool mNoCollisions;

protected:

    virtual void HandleFlyState();
    virtual void HandleFormationState();
    virtual void HandleDeadState();
    virtual void HandleFiring();
    void HandleStates();

public:

    static void createPaths(Vector2 vec1, Vector2 vec2, Vector2 vec3, Vector2 vec4, int samples);
    static void CreateEnemyPaths();

    
    HostileEntity();
    virtual ~HostileEntity();

    void LoseHP(int change);
    int GetHP();

    void InPosition(bool inPos);
    bool InPosition();

    void NoCollisions(bool noCol);
    bool NoCollisions();

    STATES currState();

    virtual void Update();
    virtual void Render();
};

#endif