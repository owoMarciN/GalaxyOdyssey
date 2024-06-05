#include "Enemy.h"

std::vector<std::vector<Vector2>> Enemy::sPaths;
unsigned int Enemy::sPathsNumber = 0;

void Enemy::createPaths(Vector2 vec1, Vector2 vec2, Vector2 vec3, Vector2 vec4, int samples){
    BezierPath * path = new BezierPath;
    path->AddCurve({vec1, vec2, vec3, vec4}, samples);
    sPaths.push_back(std::vector<Vector2>());
    path->Sample(&sPaths[sPathsNumber]);
    sPathsNumber += 1;

    delete path;
    path = NULL;
}

bool Enemy::sPathsEmpty(){
    if(sPaths.empty())
        return 1;
    return 0;
}

Enemy::Enemy(int path, ENEMYTYPES mEnemy){

    mTimer = Timer::Instance();

    switch(mEnemy){
        case ALPHA:
            mType = ALPHA;
            mHP = 30;
            mScore = 300;
            mSpeed = 100.0f;

            for(int i = 0; i < MAX_BULLETS; i++)
                mBullet.push_back(new Bullet(1, -200.0f, 90, Bullet::E_NORMAL));

            mEnemyTex = new Texture("EnemyType1.png");
            mEnemyTex->Scale(VEC2_ONE*0.25f);
            break;
        case BETA:
            mType = BETA;
            mHP = 30;
            mScore = 500;
            mSpeed = 100.0f;

            for(int i = 0; i < MAX_BULLETS; i++)
                mBullet.push_back(new Bullet(1, -250.0f, 0, Bullet::E_BOUNCING));
            
            mEnemyTex = new Texture("EnemyType2.png");
            mEnemyTex->Scale(VEC2_ONE*0.25f);
            break;
        case GAMMA:
            mType = GAMMA;
            mHP = 100;
            mScore = 700;
            mSpeed = 100.0f;

            for(int i = 0; i < MAX_BULLETS; i++)
                mBullet.push_back(new Bullet(1, -240.0f, -90, Bullet::E_TRACKING));
            
            mEnemyTex = new Texture("EnemyType3.png");
            mEnemyTex->Scale(VEC2_ONE*0.06f);
            break;
    }
    
    mInPosition = false;
    mNoCollisions = true;

    mCurrPath = path;
    mCurrState = FLY;
    mCurrWayPoint = 0;
    Pos(sPaths[mCurrPath][mCurrWayPoint]);

    mEnemyTex->Parent(this);
    mEnemyTex->Pos(VEC2_ZERO);

}

Enemy::~Enemy(){
    mTimer = nullptr;

    for(auto &bullet : mBullet){
        delete bullet;
        bullet = nullptr;
    }

    delete mEnemyTex;
    mEnemyTex = nullptr;
}

void Enemy::HandleFlyState(){
    if(((sPaths[mCurrPath][mCurrWayPoint] - Pos())).MagnitudeSqrt() < EPSIOLON)
        mCurrWayPoint++;

    if(mCurrWayPoint < sPaths[mCurrPath].size()){
        Vector2 distance = sPaths[mCurrPath][mCurrWayPoint] - Pos();
        Translate(distance.Normalized() * mTimer->DeltaTime() * mSpeed);
    }
    else{
        mCurrState = FORMATION;
    }
}

void Enemy::HandleFormationState(){
    InPosition(true);
}

void Enemy::HandleDeadState(){

}

void Enemy::HandleStates(){
    switch(mCurrState){
        case FLY:
            HandleFlyState();
            break;
        case FORMATION:
            HandleFormationState();
            break;
        case DEAD:
            HandleDeadState();
            break;
    }
}

Enemy::STATES Enemy::currState(){
    return mCurrState;
}

void Enemy::InPosition(bool inPos){
    mInPosition = inPos;
}

bool Enemy::InPosition(){
    return mInPosition;
}

void Enemy::NoCollisions(bool noCol){
    mNoCollisions = noCol;
}

bool Enemy::NoCollisions(){
    return mNoCollisions;
}

void Enemy::Update(){
    if(Active()){
        HandleStates();
        HandleFiring();
    } 

    for(auto &bullet : mBullet)
        bullet->Update();     
}

void Enemy::Render(){
    if(Active())
        mEnemyTex->Render();

    for(auto &bullet : mBullet)
        bullet->Render();
        // for(unsigned int i = 0; i < sPaths[mCurrPath].size()-1; i++){
        //     Graphics::Instance()->DrawLine(sPaths[mCurrPath][i].x, sPaths[mCurrPath][i].y, sPaths[mCurrPath][i+1].x, sPaths[mCurrPath][i+1].y);
        // }
}

void Enemy::HandleFiring() {
    if(Active() && InPosition() && NoCollisions()){
        Uint32 currentTime = SDL_GetTicks();
        if(currentTime - mLastFiredTime >= mFireDelay){
            for(int i = 0; i < MAX_BULLETS; i++){
                if(!mBullet[i]->Active()){
                    mBullet[i]->FireBullet(Pos());
                    mLastFiredTime = currentTime;
                    break;
                }
            }
        }
    }
}

void Enemy::LoseHP(int change) {
    mHP -= change;
}
