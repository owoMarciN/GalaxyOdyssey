#include "Player.h"

Player::Player()
    : mBullet(new Bullet[MAX_BULLETS]){
    mTimer = Timer::Instance();
    mInput = InputManager::Instance();

    mShip = new Texture("Ship.png");
    mShip->Parent(this);
    mShip->Pos(VEC2_ZERO);

    mSpeed = 250.0f;
    mScore = 0; 
    mHP = 3;
    mDamage = 20;

    std::unique_ptr<Bullet> mSpecialAttack;
    
    for(int i = 0; i < MAX_BULLETS; i++){
        mBullet[i].Scale(VEC2_ONE*0.5f);
    }
}

Player::~Player(){
    mInput = nullptr;

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
                if(!mBullet[i].Active()) {
                    mBullet[i].FireBullet(Pos());
                    mLastFiredTime = currentTime;
                    break;
                }
            }
        }
    }
    //Special Attack
    // else if(Active() && mInput->KeyDown(SDL_SCANCODE_X)){

    // }
}

void Player::LoseHP(int change){
    mHP -= change;
}

void Player::Update(){
    if(Active()){
        HandleMovement();
        HandleFiring();
    }

    for(int i = 0; i < MAX_BULLETS; i++)
        mBullet[i].Update();
}

void Player::Render(){
    mShip->Render();
    for(int i = 0; i < MAX_BULLETS; i++)
        mBullet[i].Render();
}

int Player::Score(){
    return mScore;
}

void Player::AddScore(int change){
    mScore += change;
}
