#ifndef PLAY_SCREEN_H_
#define PLAY_SCREEN_H_

#include "Player.h"
//#include "Boss.h"
#include "Enemy.h"

class PlayScreen : public GameEntity{
public:

    Player * mPlayer;

private:

    InputManager * mInput;

    GameEntity * mTopBar;
    Texture * mScoreLabel;
    Texture * mScoreTex;

    Texture * mHpBarOuter;
    Texture * mHpBarInner;

    GameEntity * mBackGround;
    Texture * mCosmos;

    unsigned int mScore;

    Vector2 mHP;
    Vector2 newPos;
    
    int MAX_COLUMNS = 5;
    int MAX_ROWS = 3;
    std::vector<std::vector<Enemy *>> mEnemy;
    std::vector<std::vector<Enemy *>> mNextEnemy;

    int mWaveCounter;
    
    //
public:

    PlayScreen();
    ~PlayScreen();

    int GetScore();
    void UpdateScore(unsigned int score);
    void Reset();
    void Update();
    void Render();

private:

    void HandleEnemyCollision();
    void HandlePlayerCollision();
    void EnemyFormation();

    void CreateEnemyPaths();
    std::vector<std::vector<Enemy *>> CreateEnemies(std::vector<std::vector<Enemy *>> &M);
    bool CheckEnemyActivity();
    void RespawnEnemies();

    void UnexpectedAttack();
    void SamuelsSpear();
    void Flood();
    void Annihilation();
    
    void GodHasSinned();

    int ProbabilityCalc();

};

#endif