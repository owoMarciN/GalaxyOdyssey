#include "Boss.h"

Boss::Boss()
    : mBullet(new Bullet[MAX_BULLETS]) { // Initialize unique_ptr for array
    mTimer = Timer::Instance();

    mTexture = new Texture("Boss.png");
    mTexture->Parent(this);
    mTexture->Pos(VEC2_ZERO);
    mSpeed = 50.0f;
    mHP = 1000;
    mDamage = 1;
    mDirection = -1;

    for (int i = 0; i < MAX_BULLETS; i++) {
        mBullet[i].Rotate(-180);
        mBullet[i].Scale(VEC2_ONE * 0.5f);
    }
}

Boss::~Boss() {
    delete mTexture;
    mTexture = nullptr;
}

void Boss::HandleMovement() {
    if(Active()) {
        Vector2 pos = Pos(local);
        if (pos.x < mBounds.x)
            mDirection = 1;
        else if (pos.x > mBounds.y)
            mDirection = -1;
        Translate(VEC2_RIGHT * mTimer->DeltaTime() * mSpeed * mDirection);
    }
}

void Boss::HandleFiring() {
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

void Boss::LoseHP(int change) {
    mHP -= change;
}

void Boss::Update() {
    if (Active()) {
        HandleMovement();
        HandleFiring();
    }
    for (int i = 0; i < MAX_BULLETS; i++)
        mBullet[i].Update();
}

void Boss::Render() {
    mTexture->Render();
    for (int i = 0; i < MAX_BULLETS; i++)
        mBullet[i].Render();
}