#include "Enemy.h"

const int Enemy::MAX_BULLETS = 3;

Enemy::Enemy(int path, ENEMYTYPES mEnemy){
    switch(mEnemy){
        case ALPHA:
            mType = ALPHA;
            mHP = 30;
            mScore = 300;
            mSpeed = 100.0f;

            for(int i = 0; i < MAX_BULLETS; i++)
                mBullet.push_back(new Bullet(1, Bullet::E_NORMAL));

            mEnemyTex = new Texture("EnemyType1.png");
            mEnemyTex->Scale(VEC2_ONE*0.25f);
            break;
        case BETA:
            mType = BETA;
            mHP = 30;
            mScore = 500;
            mSpeed = 115.0f;

            for(int i = 0; i < MAX_BULLETS; i++)
                mBullet.push_back(new Bullet(1, Bullet::E_BOUNCING));
            
            mEnemyTex = new Texture("EnemyType2.png");
            mEnemyTex->Scale(VEC2_ONE*0.25f);
            break;
        case GAMMA:
            mType = GAMMA;
            mHP = 70;
            mScore = 700;
            mSpeed = 120.0f;

            for(int i = 0; i < MAX_BULLETS; i++)
                mBullet.push_back(new Bullet(1, Bullet::E_TRACKING));
            
            mEnemyTex = new Texture("EnemyType3.png");
            mEnemyTex->Scale(VEC2_ONE*0.06f);
            break;
    }

    mCurrPath = path;
    mCurrWayPoint = 0;
    Pos(sPaths[mCurrPath][mCurrWayPoint]);

    mEnemyTex->Parent(this);
    mEnemyTex->Pos(VEC2_ZERO);

    mDestruction = new AnimatedTexture("Explosion_V2.png", 88.0f, 0.0f, 100.0f, 100.0f, 48, 0.6f, AnimatedTexture::horizontal);
    mDestruction->WrapMode(AnimatedTexture::once);
    mDestruction->Pos(Pos());
    mDestruction->Parent(this);
}

Enemy::~Enemy(){
    for(auto &bullet : mBullet){
        delete bullet;
        bullet = nullptr;
    }

    delete mEnemyTex;
    mEnemyTex = nullptr;

    delete mDestruction;
    mDestruction = nullptr;
}

void Enemy::HandleFiring(){
    if(Active() && InPosition() && NoCollisions()){
        Uint32 currentTime = SDL_GetTicks();
        if(currentTime - mLastFiredTime >= mFireDelay){
            for(int i = 0; i < MAX_BULLETS; i++){
                if(!mBullet[i]->Active()){
                    Vector2 pos = Vector2(Pos().x, Pos().y + 30.0f);
                    mBullet[i]->FireBullet(pos);
                    mLastFiredTime = currentTime;
                    break;
                }
            }
        }
    }
}

bool Enemy::DestructionDone(){
    return mDestruction->Done();
}

void Enemy::Update(){
    if(Active()){
        HandleStates();
        HandleFiring();
    }
    else if(!Active() && !mDestruction->Done()){
        mDestruction->Update();
    }

    for(auto &bullet : mBullet)
        bullet->Update(); 
}

void Enemy::Render(){
    if(Active())
        mEnemyTex->Render();
    else if(!Active() && !mDestruction->Done()){
        mDestruction->Render();
    }

    for(auto &bullet : mBullet)
        bullet->Render();
}