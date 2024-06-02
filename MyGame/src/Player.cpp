#include "Player.h"

Player::Player(){
    mTimer = Timer::Instance();
    mInput = InputManager::Instance();
    mAudio = AudioManager::Instance();

    mShip = new Texture("Ship.png");
    mShip->Parent(this);
    mShip->Pos(VEC2_ZERO);

    mSpeed = 250.0f;
    mHP = 5;

    for(int i = 0; i < MAX_BULLETS; i++)
        mBullet.push_back(new Bullet(20, 700.0f, -90, Bullet::NORMAL));
    for(int i = 0; i < MAX_BULLETS; i++){
        mBullet[i]->Scale(VEC2_ONE*0.5f);
    }

    mSpecialAttack = new Bullet(120, 1000.0f, -90, Bullet::P_SPECIAL);
}

Player::~Player(){
    mInput = nullptr;
    mTimer = nullptr;
    mAudio = nullptr;

    for(auto &bullet : mBullet){
        delete bullet;
        bullet = nullptr;
    }

    delete mSpecialAttack;
    mSpecialAttack = nullptr;

    delete mShip;
    mShip = nullptr;
}

void Player::HandleMovement(){
    if(mInput->KeyDown(SDL_SCANCODE_D))
        Translate(VEC2_RIGHT*mSpeed*mTimer->DeltaTime(), world);
    if(mInput->KeyDown(SDL_SCANCODE_A)){
        Translate(-VEC2_RIGHT*mSpeed*mTimer->DeltaTime(), world);
    }
    if(mInput->KeyDown(SDL_SCANCODE_W)){
        Translate(-VEC2_UP*mSpeed*mTimer->DeltaTime(), world);
    }
    if(mInput->KeyDown(SDL_SCANCODE_S)){
        Translate(VEC2_UP*mSpeed*mTimer->DeltaTime(), world);
    }

    Vector2 pos = Pos(local);
    if(pos.x < mBoundsX.x)
        pos.x = mBoundsX.x;
    else if(pos.x > mBoundsX.y)
        pos.x = mBoundsX.y;
    else if(pos.y > mBoundsY.x)
        pos.y = mBoundsY.x;
    else if(pos.y < mBoundsY.y)
        pos.y = mBoundsY.y;
    Pos(pos);
}

void Player::HandleFiring() {
    if(Active() && mInput->KeyDown(SDL_SCANCODE_SPACE)) {
        Uint32 currentTime = SDL_GetTicks();
        if(currentTime - mLastFiredTime >= mFireDelay){
            for(int i = 0; i < MAX_BULLETS; i++) {
                if(!mBullet[i]->Active()) {
                    mBullet[i]->FireBullet(Pos());
                    mAudio->PlayMusic("LaserSound_Normal.mp3", 0);
                    mLastFiredTime = currentTime;
                    break;
                }
            }
        }
    }

    if(Active() && mInput->KeyPressed(SDL_SCANCODE_X)) {
        Uint32 currentTime = SDL_GetTicks();
        if(currentTime - mLastFiredTime >= mFireSpecialDelay){
            if(!mSpecialAttack->Active()) {
                mSpecialAttack->FireBullet(Pos());
                mAudio->PlayMusic("LaserSound_Heavy.mp3", 0);
                mLastFiredTime = currentTime;
            }
        }
    }
}

void Player::LoseHP(int change){
    mHP -= change;
}

void Player::Update(){
    if(Active()){
        HandleMovement();
        HandleFiring();
        for(int i = 0; i < MAX_BULLETS; i++)
            mBullet[i]->Update();
        mSpecialAttack->Update();
    }
}

void Player::Render(){
    if(Active()){
        mShip->Render();
        for(int i = 0; i < MAX_BULLETS; i++)
            mBullet[i]->Render();
        mSpecialAttack->Render();
    }
}
