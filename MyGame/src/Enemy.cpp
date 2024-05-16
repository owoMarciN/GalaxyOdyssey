#include "Enemy.h"

std::vector<std::vector<Vector2>> Enemy::sPaths;

void Enemy::createPaths(){
    int currPath = 0;
    BezierPath * path = new BezierPath;
    path->AddCurve({Vector2(Graphics::SCREEN_WIDTH*0.1f, 100.0f), Vector2(Graphics::SCREEN_WIDTH*0.1f, 0.0f), Vector2(500.0f, 310.0f), Vector2(100.0f, 300.0f)}, 20);
    sPaths.push_back(std::vector<Vector2>());
    path->Sample(&sPaths[currPath]);

    delete path;
    path = NULL;
}

Enemy::Enemy(int path) 
    : mBullet(new Bullet[MAX_BULLETS]){
    mHP = 1000;
    mDamage = 1;
    mTimer = Timer::Instance();
    mCurrPath = path;
    mCurrState = FLY;
    mCurrWayPoint = 0;
    Pos(sPaths[mCurrPath][mCurrWayPoint]);

    mTexture = new Texture("Boss.png");
    mTexture->Parent(this);
    mTexture->Pos(VEC2_ZERO);

    mSpeed = 100.0f;
    for (int i = 0; i < MAX_BULLETS; i++) {
        mBullet[i].Rotate(-180);
        mBullet[i].Scale(VEC2_ONE * 0.5f);
    }
}

Enemy::~Enemy(){
    mTimer = NULL;

    delete mTexture;
    mTexture = NULL;
}

void Enemy::HandleDeadState(){
    
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

}

void Enemy::HandleDiveState(){

}


void Enemy::HandleStates(){
    switch(mCurrState){
        case FLY:
            HandleFlyState();
            break;
        case FORMATION:
            HandleFormationState();
            break;
        case DIVE:
            HandleDiveState();
            break;
        case DEAD:
            HandleDeadState();
            break;
    }
}

void Enemy::Update(){
    if (Active()) {
        HandleStates();
        HandleFiring();
    }
    for (int i = 0; i < MAX_BULLETS; i++)
        mBullet[i].Update();        
}

void Enemy::Render(){
    if(Active()){
        mTexture->Render();
        for (int i = 0; i < MAX_BULLETS; i++)
            mBullet[i].Render();
        for(int i = 0; i < sPaths[mCurrPath].size()-1; i++){
            Graphics::Instance()->DrawLine(sPaths[mCurrPath][i].x, sPaths[mCurrPath][i].y, sPaths[mCurrPath][i+1].x, sPaths[mCurrPath][i+1].y);
        }
    }
}

void Enemy::HandleFiring() {
    if(Active()) {
        Uint32 currentTime = SDL_GetTicks();
        if(currentTime - mLastFiredTime >= mFireDelay){
            for(int i = 0; i < MAX_BULLETS; i++) {
                if(!mBullet[i].Active()) {
                    mBullet[i].FireBullet(Pos());
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
