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

Enemy::Enemy(int path, ENEMYTYPES mEnemy){

    mTimer = Timer::Instance();

    switch(mEnemy){
        case ALPHA:
            mType = ALPHA;
            mHP = 60;
            mScore = 300;
            mSpeed = 100.0f;
            for(int i = 0; i < MAX_BULLETS; i++){
                mBullet.push_back(new Bullet(1, -170.0f, -90, Bullet::E_NORMAL));
                mBullet[i]->Scale(VEC2_ONE*0.75f);
            }
            mTexture = new Texture("EnemyType1.png");
            mTexture->Scale(VEC2_ONE*0.25f);
            break;
        case BETA:
            mType = BETA;
            mHP = 30;
            mScore = 500;
            mSpeed = 100.0f;
            //DotProduct(Pos(), mPlayerPos)

            for(int i = 0; i < MAX_BULLETS; i++){
                mBullet.push_back(new Bullet(1, -200.0f, 45, Bullet::E_BOUNCING));
            }

            mTexture = new Texture("EnemyType2.png");
            mTexture->Scale(VEC2_ONE*0.25f);
            break;
        case BOSS:
            mType = BOSS;
            mHP = 1000;
            mScore = 999999;
            mSpeed = 130.0f;
            for(int i = 0; i < MAX_BULLETS; i++){
                mBullet.push_back(new Bullet(1, -200.0f, -90, Bullet::E_NORMAL));
                mBullet[i]->Scale(VEC2_ONE*0.75f);
            }
            mTexture = new Texture("Boss.png");
            mTexture->Scale(VEC2_ONE*0.25f);
            break;
    }
    
    mInPosition = false;
    mNoCollisions = true;

    mCurrPath = path;
    mCurrState = FLY;
    mCurrWayPoint = 0;
    Pos(sPaths[mCurrPath][mCurrWayPoint]);

    mTexture->Parent(this);
    mTexture->Pos(VEC2_ZERO);

}

Enemy::~Enemy(){
    mTimer = nullptr;

    for(auto &bullet : mBullet){
        delete bullet;
        bullet = nullptr;
    }

    delete mTexture;
    mTexture = nullptr;
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
    InPosition(true);
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
    if(Active()) {
        HandleStates();
        HandleFiring();
    }   
    for(auto &bullet : mBullet)
        bullet->Update();     
}

void Enemy::Render(){
    if(Active()){
        mTexture->Render();
    }
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
            for(int i = 0; i < MAX_BULLETS; i++) {
                if(!mBullet[i]->Active()) {
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

void Enemy::GetPlayerPos(Vector2 pos){
    mPlayerPos = pos;
}