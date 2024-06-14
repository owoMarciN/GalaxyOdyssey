#ifndef PLAY_SCREEN_H_
#define PLAY_SCREEN_H_

#include "Player.h"
#include "EnemySpawner.h"

class PlayScreen : public GameEntity{
private:

    InputManager * mInput;
    EnemySpawner * mEnemySpawner;
    AudioManager * mAudio;
    Timer * mTimer;

    enum GAME_FLOW {
        ENEMY_WAVES,
        BOSSBATTLE
    };

    enum SPECIAL_METER_STATE {
        IDLE,
        SHRINK,
        WAIT,
        GROW
    };

    SPECIAL_METER_STATE mMeterState;
    GAME_FLOW mCurrFlow;

    Player * mPlayer;

    GameEntity * mTopBar;
    Texture * mScoreLabel;
    Texture * mScoreTex;
    Texture * mHpBarOuter;
    Texture * mHpBarInner;
    Texture * mSpecialMeter;
    Texture * mSpecialMeterFrame;

    GameEntity * mBackGround;
    Texture * mCosmos;

    int mScore;

    Vector2 mHP;
    Vector2 newPos;

    std::vector<std::vector<Enemy *>> mEnemy;
    Boss * mBoss;

    Uint32 mTimeFired = 0;  // Time when the last bullet was fired
    const Uint32 mDelay = 150;
    float mCurrentScale = 0.1f; // Initial scale of the meter after shrinking
    const float mMinScale = 0.1f;
    const float mMaxScale = 1.0f; // Maximum scale of the meter
    const float mScaleIncrement = 0.05f; // Amount to grow the meter each mDelay

public:

    PlayScreen();
    ~PlayScreen();

    int GetScore();
    bool PlayerActive();
    bool BossActive();
    void Update();
    void Render();

private:

    void EnemyToPlayerCollision();
    void BossToPlayerCollision();
    void HPcalculator();
    void PlayerToEnemyCollision();
    void PlayerToBossCollision();
    void LoadEnemies();
    void UpdateScore(int score);
    void UpdateSpecial();
    void ChangeGameFlow();
    //void AdjustSpecialMeter();

};

#endif