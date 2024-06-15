#ifndef ENEMY_SPAWNER_H_
#define ENEMY_SPAWNER_H_

#include "Enemy.h"
#include "Boss.h"

class EnemySpawner{
private:

    static EnemySpawner * sInstance;
    std::vector<std::vector<Enemy *>> mWave;
    std::vector<std::vector<Enemy *>> mNextWave;
    int mCounter;

public:

    static EnemySpawner * Instance();
    static const int MAX_COLUMNS = 5;
    static const int MAX_ROWS = 3;
    int mWaveCounter;

private:

    void EnemyFormation();
    void ResetCounter();
    bool CheckEnemyActivity();
    void CreateFormation();
    void UpdateFormation();

    void UnexpectedAttack();
    void Flood();
    void Annihilation();
    void SamuelsSpear();
    void HeavensDoor();

public:

    std::vector<std::vector<Enemy *>> GetCurrentWave();
    int CurrentWave();
    EnemySpawner();
    ~EnemySpawner();
    static void Release();

};

#endif