#include "Boss.h"

const int Boss::MAX_BULLETS = 6;

Boss::Boss(int path){
    mSpeed = 70.0f;
    mHP = 10000;
    mScore = 10000;

    for(int i = 0; i < MAX_BULLETS; i++)
        mBullet.push_back(new Bullet(1, Bullet::E_NORMAL));

    for(int i = 0; i < MAX_BULLETS/2; i++)
        mBullet.push_back(new Bullet(1, Bullet::E_TRACKING));

    for(int i = 0; i < MAX_BULLETS; i++)
        mBullet.push_back(new Bullet(1, Bullet::E_BOUNCING));

    mBossTex = new Texture("AlienBoss.gif");
    mBossTex->Scale(VEC2_ONE*0.4f);

    mCurrPath = path;
    mCurrWayPoint = 0;
    Pos(sPaths[mCurrPath][mCurrWayPoint]);

    mBossTex->Parent(this);
    mBossTex->Pos(VEC2_ZERO);

    mCurrentAttack = NORMAL;
}

Boss::~Boss(){
    for(auto &bullet : mBullet){
        delete bullet;
        bullet = nullptr;
    }

    delete mBossTex;
    mBossTex = nullptr;
}

void Boss::HandleFiring(){
    switch(mCurrentAttack){
        case NORMAL:
            if(Active() && InPosition() && NoCollisions()){
                Uint32 currentTime = SDL_GetTicks();
                if(currentTime - mLastFiredNormal >= mNormalDelay){
                    for(int i = 0; i < MAX_BULLETS-1; i++){
                        if(!mBullet[i]->Active() && !mBullet[i+1]->Active()){
                            Vector2 pos = Vector2(Pos().x - 138.0f, Pos().y + 80.0f);
                            Vector2 pos2 = Vector2(Pos().x + 130.0f, Pos().y + 80.0f);
                            mBullet[i]->FireBullet(pos);
                            mBullet[i+1]->FireBullet(pos2);
                            mLastFiredNormal = currentTime;
                            break;
                        }
                    }
                }
                mCurrentAttack = SERIES_TRACKING;
            }
            break;
        case SERIES_TRACKING:
            if(Active() && InPosition() && NoCollisions()){
                Uint32 currentTime = SDL_GetTicks();
                if(currentTime - mLastFiredSeries >= mSeriesDelay){
                    for(int i = MAX_BULLETS; i < MAX_BULLETS + 3; i++){
                        if(!mBullet[i]->Active()){
                            mBullet[i]->FireBullet(Pos());
                            mLastFiredSeries = currentTime;
                            break;
                        }
                    }
                }
                mCurrentAttack = SERIES_BOUNCING;
            }
            break;
        case SERIES_BOUNCING:
            if(Active() && InPosition() && NoCollisions()){
                Uint32 currentTime = SDL_GetTicks();
                if(currentTime - mLastFiredSeries >= mSeriesDelay){
                    for(int i = MAX_BULLETS+3; i < (MAX_BULLETS*2)+3; i++){
                        if(!mBullet[i]->Active()){
                            mBullet[i]->FireBullet(Pos());
                            mLastFiredSeries = currentTime;
                            break;
                        }
                    }
                }
                mCurrentAttack = NORMAL;
            }
            break;
    }
}

void Boss::HandleFormationState() {
    static Uint32 waitStartTime = 0;  // Start time of the wait period

    if(InPosition()){
        Uint32 currTime = SDL_GetTicks();
        if (waitStartTime == 0) {
            waitStartTime = currTime;  // Initialize the wait timer
        }

        // Check if the boss has waited long enough
        if(currTime - waitStartTime >= mMoveDelay) {
            mCurrWayPoint = 0;
            mCurrState = FLY;
            mLastMove = currTime;
            waitStartTime = 0;  // Reset the wait timer
        }
    } 
    else{
        waitStartTime = 0;  // Reset the wait timer if not in position
    }

    // Adjust the current path
    if(mCurrPath >= 2){
        mCurrPath--;
    } 
    else if(mCurrPath < 2){
        mCurrPath++;
    }

    InPosition(true);
}


void Boss::Update(){
    if(Active()){
        HandleStates();
        HandleFiring();
    } 

    for(auto &bullet : mBullet)
        bullet->Update();     
}

void Boss::Render(){
    if(Active())
        mBossTex->Render();

    for(auto &bullet : mBullet)
        bullet->Render();

    // for(unsigned int i = 0; i < sPaths[mCurrPath].size()-1; i++){
    //     Graphics::Instance()->DrawLine(sPaths[mCurrPath][i].x, sPaths[mCurrPath][i].y, sPaths[mCurrPath][i+1].x, sPaths[mCurrPath][i+1].y);
    // }  
}

