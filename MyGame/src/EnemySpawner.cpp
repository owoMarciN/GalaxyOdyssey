#include "EnemySpawner.h"

EnemySpawner * EnemySpawner::sInstance = nullptr;

EnemySpawner * EnemySpawner::Instance(){
    if(sInstance == nullptr)
        sInstance = new EnemySpawner();
    return sInstance;
}

void EnemySpawner::Release(){
    delete sInstance;
    sInstance = nullptr;
}

EnemySpawner::EnemySpawner(){
    mWaveCounter = 0;
}

EnemySpawner::~EnemySpawner(){
    mWave.clear();
    mNextWave.clear();
}

void EnemySpawner::CreateFormation(){
    ResetCounter();
    switch(mWaveCounter){
        case 0:
        case 4: Flood(); break;
        case 1: Annihilation(); break;
        case 2: SamuelsSpear(); break;
        case 3: HeavensDoor(); break;
    }
}

bool EnemySpawner::CheckEnemyActivity(){
    for(auto &row : mWave)
        for(auto &enemy : row)
            if(enemy->Active())
                return false;
    return true;
}

void EnemySpawner::UpdateFormation(){
    mWave = mNextWave;
    mNextWave.clear();
    mWaveCounter++;
}

std::vector<std::vector<Enemy *>> EnemySpawner::GetCurrentWave(){
    UnexpectedAttack();
    EnemyFormation();
    return mWave;
}

void EnemySpawner::UnexpectedAttack(){
    if(mWave.empty()){
        CreateFormation();
        UpdateFormation();
    }

    if(CheckEnemyActivity()){
        CreateFormation();
        UpdateFormation();
    }
}

void EnemySpawner::ResetCounter(){
    mCounter = 3;
}

void EnemySpawner::EnemyFormation(){
    for(int i = 0; i < MAX_ROWS-1; i++){
        for(int j = 0; j < MAX_COLUMNS; j++){
            if(mWave[i][j]->Active() && mWave[i+1][j]->Active() && mWave[i][j]->mType != Enemy::BETA){
                mWave[i][j]->NoCollisions(false);
            }
            else{
                mWave[i][j]->NoCollisions(true);
            }
        }
    }
}

void EnemySpawner::Flood(){
    for(int i = 0; i < MAX_ROWS; i++){
        mNextWave.push_back(std::vector<Enemy *>());
        for(int j = 0; j < MAX_COLUMNS; j++){
            if(mWaveCounter == 4 && i == 0){
                mNextWave[i].push_back(new Enemy(mCounter, Enemy::GAMMA));
                mCounter++;
            }
            else if(mWaveCounter >= 7 && i == 1 && j > 0 && j < 4){
                mNextWave[i].push_back(new Enemy(mCounter, Enemy::BETA));
                mCounter++;
            }
            else{
                mNextWave[i].push_back(new Enemy(mCounter));
                mCounter++;
            }
        }
    }
}

void EnemySpawner::Annihilation(){
    mNextWave.push_back(std::vector<Enemy *>());
    mNextWave[0].push_back(new Enemy(mCounter));
    mCounter++;
    for(int i = 0; i < 3; i++){
        mNextWave[0].push_back(new Enemy(mCounter, Enemy::BETA));
        mCounter++;
    }
    mNextWave[0].push_back(new Enemy(mCounter));
    mCounter++;
    mNextWave[0][0]->Active(false);
    mNextWave[0][4]->Active(false);

    mNextWave.push_back(std::vector<Enemy *>());
    mNextWave[1].push_back(new Enemy(mCounter));
    mCounter++;
    mNextWave[1].push_back(new Enemy(mCounter));
    mCounter++;

    mNextWave[1].push_back(new Enemy(mCounter, Enemy::GAMMA));
    mCounter++;

    mNextWave[1].push_back(new Enemy(mCounter));
    mCounter++;
    mNextWave[1].push_back(new Enemy(mCounter));
    mCounter++;

    mNextWave.push_back(std::vector<Enemy *>());
    mNextWave[2].push_back(new Enemy(mCounter));
    mCounter++;
    for(int i = 0; i < 3; i++){
        mNextWave[2].push_back(new Enemy(mCounter));
        mNextWave[2][i+1]->Active(false);
        mCounter++;
    }
    mNextWave[2].push_back(new Enemy(mCounter));
    mCounter++;
}

void EnemySpawner::SamuelsSpear(){
    for(int i = 0; i < MAX_ROWS; i++){
        mNextWave.push_back(std::vector<Enemy *>());
        for(int j = 0; j < MAX_COLUMNS; j++){
            switch(i){
                case 0: mNextWave[i].push_back(new Enemy(mCounter)); mCounter++; break;
                case 1: mNextWave[i].push_back(new Enemy(mCounter, Enemy::BETA)); mCounter++; break;
                default: mNextWave[i].push_back(new Enemy(mCounter, Enemy::GAMMA)); mCounter++; break;
            }
        }
    }
    for(int i = 0; i < MAX_ROWS; i++){
        for(int j = 0; j < MAX_COLUMNS; j++){
            if(i >= 1 && (j < i || j > 4 - i)){
                mNextWave[i][j]->Active(false);
            }
        }
    }
}

void EnemySpawner::HeavensDoor(){
    for(int i = 0; i < MAX_ROWS; i++){
        mNextWave.push_back(std::vector<Enemy *>());
        for(int j = 0; j < MAX_COLUMNS; j++){
            switch(j){
                case 1:
                case 3: mNextWave[i].push_back(new Enemy(mCounter, Enemy::GAMMA)); mCounter++; break;
                default: mNextWave[i].push_back(new Enemy(mCounter)); mCounter++; break;
            }
        }
    }
}

int EnemySpawner::CurrentWave(){
    return mWaveCounter;
}