#ifndef ENEMY_SPAWNER_H_
#define ENEMY_SPAWNER_H_

#include "Enemy.h"
#include "Boss.h"

class EnemySpawner{
private:

    static EnemySpawner * sInstance;
    std::vector<std::vector<Enemy *>> mNextWave;
    int mCounter;

public:

    static EnemySpawner * Instance();
    static std::vector<std::vector<Enemy *>> mWave;
    static const int MAX_COLUMNS = 5;
    static const int MAX_ROWS = 3;
    int mWaveCounter;

private:

    bool AllEnemiesDestroyed();
    void CreateFormation();
    void EnemyFormation();
    void UpdateFormation();
    void ResetWaveCounter();
    
    void Flood();
    void Annihilation();
    void SamuelsSpear();
    void HeavensDoor();

public:

    int CurrentWave();

    EnemySpawner();
    ~EnemySpawner();

    static void Release();
    void Update();
    void Render();

};

#endif