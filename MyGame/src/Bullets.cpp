#include "Bullets.h"

Bullet::Bullet(){
    mTimer = Timer::Instance();

    mSpeed = 700.0f;
    mBullet = new Texture("bullet.png");
    mBullet->Parent(this);
    mBullet->Pos(VEC2_ZERO);
    mBullet->Rotate(-90);
    Reload();
}

// Bullet::Bullet(int damage, float rotation, BULLETTYPE bType){
//     mTimer = Timer::Instance();

//     mSpeed = 700.0f;
//     switch(bType){
//         case NORMAL:
//             mBullet = new Texture("normal.png");
//             break;
//         case P_SPECIAL:
//             mBullet = new Texture("player_special.png");
//             break;
//         case E_NORMAL:
//             mBullet = new Texture("enemy_bullet.png");
//             break;
//         case E_BOUNCING:
//             mBullet = new Texture("bouncing_bullet.png");
//             break;
//     }
//     mBullet->Parent(this);
//     mBullet->Pos(VEC2_ZERO);
//     mBullet->Rotate(rotation);
//     mDamage = damage;
//     Reload();
// }

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
}

void Bullet::Update(){
    if(Active()){
        Translate(-VEC2_UP * mSpeed * mTimer->DeltaTime());

        Vector2 pos = Pos();
        if(pos.y < -OFF_SCREEN_BUFFER || pos.y > Graphics::Instance()->SCREEN_HEIGHT + OFF_SCREEN_BUFFER){
            Reload();
        }
    }
}

void Bullet::Render(){
    if(Active()){
         mBullet->Render();
    }
}