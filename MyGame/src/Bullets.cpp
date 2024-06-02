#include "Bullets.h"

Bullet::Bullet(int damage, float speed, float rotation, BULLETTYPE bType){
    mTimer = Timer::Instance();
    mCurrType = bType;

    switch(bType){
        case NORMAL:
            mBullet = new Texture("bullet.png");
            break;
        case P_SPECIAL:
            mBullet = new Texture("player_special.png");
            break;
        case E_NORMAL:
            mBullet = new Texture("enemy_bullet.png");
            break;
        case E_BOUNCING:
            mBullet = new Texture("04.png");
            break;
    }
    
    mBullet->Parent(this);
    mBullet->Pos(VEC2_ZERO);
    mBullet->Rotate(rotation);
    mDamage = damage;
    mSpeed = speed;

    DirectionX = -1.0f;
    DirectionY = -1.0f;
    mCountBounces = 0;

    Reload();
}

Bullet::~Bullet(){
    mTimer = nullptr;

    delete mBullet;
    mBullet = nullptr;
}

void Bullet::FireBullet(Vector2 pos){
    Pos(pos);
    Active(true);
}

void Bullet::Reload(){
    Active(false);
    mCountBounces = 0;
}

void Bullet::Update(){
    switch(mCurrType){
        case NORMAL:
        case P_SPECIAL:
        case E_NORMAL:
            if(Active()){
                Translate(-VEC2_UP * mSpeed * mTimer->DeltaTime(), world);

                Vector2 pos = Pos();
                if(pos.y < -OFF_SCREEN_BUFFER || pos.y > Graphics::Instance()->SCREEN_HEIGHT + OFF_SCREEN_BUFFER){
                    Reload();
                }
            }
            break;
        case E_BOUNCING:
            if(Active()){
                Translate(Vector2(DirectionX, DirectionY) * mSpeed * mTimer->DeltaTime(), world);

                Vector2 pos = Pos();

                if(mCountBounces >= 5)
                    Reload();

                if(pos.x < -OFF_SCREEN_BUFFER || pos.x > Graphics::Instance()->SCREEN_WIDTH + OFF_SCREEN_BUFFER){
                    DirectionX *= -1.0f;
                    mCountBounces++;
                    pos.x += DirectionX * mSpeed * mTimer->DeltaTime();
                    Rotate(90*DirectionX);
                }

                if(pos.y < -OFF_SCREEN_BUFFER || pos.y > Graphics::Instance()->SCREEN_HEIGHT + OFF_SCREEN_BUFFER){
                    DirectionY *= -1.0f;
                    mCountBounces++;
                    pos.y += DirectionY * mSpeed * mTimer->DeltaTime();
                    Rotate(90*DirectionY);
                }
                Pos(pos);
            }
            break;
    }
}

void Bullet::Render(){
    if(Active()){
         mBullet->Render();
    }
}
