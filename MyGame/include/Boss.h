#ifndef BOSS_H_
#define BOSS_H_

#include "HostileEntity.h"

class Boss : public HostileEntity{
private:

    enum ATTACK{NORMAL, SERIES_TRACKING, SERIES_BOUNCING};
    Texture * mBossTex;
    ATTACK mCurrentAttack;

    Uint32 mLastFiredNormal = 0;  // Time when the last bullet was fired
    const Uint32 mNormalDelay = 700;

    Uint32 mLastFiredSeries = 0;
    const Uint32 mSeriesDelay = 200;

    Uint32 mLastMove = 0;
    const Uint32 mMoveDelay = 5000;
    
public:

    static const int MAX_BULLETS;
    std::vector<Bullet*> mBullet;

public:

    Boss(int path);
    ~Boss();
    void HandleFormationState();
    void HandleFiring();
    void Update();
    void Render();

};

#endif
