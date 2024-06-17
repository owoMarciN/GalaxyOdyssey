#include "Bullets.h"

Bullet::Bullet(int damage, BULLETTYPE bType){
    mTimer = Timer::Instance();
    
    mCurrType = bType;
    switch(bType){
        case NORMAL:
            mBulletTex = new Texture("PlayerBullet.png");
            mBulletTex->Scale(VEC2_ONE*0.5f);
            mBulletTex->Rotate(-90);
            mSpeed = 700.0f;
            break;
        case P_SPECIAL:
            mBulletTex = new Texture("player_special.png");
            mBulletTex->Rotate(-90);
            mSpeed = 1000.0f;
            break;
        case E_NORMAL:
            mBulletTex = new Texture("enemy_bullet.png");
            mBulletTex->Scale(VEC2_ONE*0.75f);
            mBulletTex->Rotate(90);
            mSpeed = -240.0f;
            break;
        case E_BOUNCING:
            mBulletTex = new Texture("bouncy_bullet.png");
            mBulletTex->Scale(VEC2_ONE*0.05f);
            mBulletTex->Rotate(45);
            mSpeed = -270.0f;
            break;
        case E_TRACKING:
            mBulletTex = new Texture("tracking_bullet.png");
            mBulletTex->Rotate(90);
            mSpeed = -250.0f;
            break;
    }
    
    mBulletTex->Parent(this);
    mBulletTex->Pos(VEC2_ZERO);
    mDamage = damage;
    mCountBounces = 0;

    Reload();
}

Bullet::~Bullet(){
    mTimer = nullptr;

    delete mBulletTex;
    mBulletTex = nullptr;
}

void Bullet::FireBullet(Vector2 pos){
    //Firing the bullet form the given position
    Pos(pos);   

    //Setting the X and Y directions, which are used by BETA - EnemyType2
    if(pos.x > 640){
        DirectionX = -1.0f;
        DirectionY = -1.0f;
        }
    else{
        DirectionX = 1.0f;
        DirectionY = -1.0f;   
    }

    //Activating the bullet
    Active(true);   
}

void Bullet::Reload(){
    Active(false);  //Deactivating the bullet
    mCountBounces = 0;  //The number of bounces is set to zero for BETA - EnemyType2
}

void Bullet::Update(){
    if (Active()) {
        Vector2 bulletPos = Pos();
        switch(mCurrType){
            case NORMAL:
            case P_SPECIAL:
            case E_NORMAL:
                //Changing the current 'world' position of the bullet
                Translate(-VEC2_UP * mSpeed * mTimer->DeltaTime(), world);
                //Checking if there's a collision with the window's bottom edge with the current position of the bullet
                if(bulletPos.y < -OFF_SCREEN_BUFFER || bulletPos.y > Graphics::Instance()->SCREEN_HEIGHT + OFF_SCREEN_BUFFER){
                    Reload();
                }
                break;
            case E_BOUNCING:
                //Changing the current 'world' position of the bullet
                /*
                Checking if there's a collision with any of the window's edges with the current position and 
                updating the bullets direction on the X-axis or Y-axis, also the number of bounces is increased by 1
                */
                if(bulletPos.x < -OFF_SCREEN_BUFFER || bulletPos.x > Graphics::Instance()->SCREEN_WIDTH + OFF_SCREEN_BUFFER){
                    DirectionX *= -1.0f;
                    mCountBounces++;
                    bulletPos.x += DirectionX * mSpeed * mTimer->DeltaTime();
                }
                if(bulletPos.y < -OFF_SCREEN_BUFFER || bulletPos.y > Graphics::Instance()->SCREEN_HEIGHT + OFF_SCREEN_BUFFER){
                    DirectionY *= -1.0f;
                    mCountBounces++;
                    bulletPos.y += DirectionY * mSpeed * mTimer->DeltaTime();
                }
                //Updating the new position
                Translate(Vector2(DirectionX, DirectionY) * mSpeed * mTimer->DeltaTime(), world); 
                //Making the bullet inactive after bounces of the window 4 or more times
                if(mCountBounces >= 5)
                    Reload();
                break;
            case E_TRACKING:
                Vector2 directionToPlayer = mPlayerPos - bulletPos;

                if(directionToPlayer.y < 220.0f){
                    //Setting the X and Y directions
                    DirectionX = PrevDirection.x;
                    DirectionY = PrevDirection.y;
                }
                else{
                    directionToPlayer.Normalized();     //Calculating the unit vector of the distance to the player

                    //Setting the X and Y directions
                    DirectionX = -directionToPlayer.x;
                    DirectionY = -directionToPlayer.y;

                    //Remembering the previous direction
                    PrevDirection = Vector2(DirectionX, DirectionY);

                    //Calculating the angle between the Player and the bullet position
                    float angleToPlayer = atan2(directionToPlayer.y, directionToPlayer.x);

                    //Rotating the texture of the bullet by the given amount
                    mBulletTex->Rotation(angleToPlayer * RAD_TO_DEG);
                }

                Translate(Vector2(DirectionX, DirectionY) * mSpeed * mTimer->DeltaTime(), world);

                if(bulletPos.y < -OFF_SCREEN_BUFFER || bulletPos.y > Graphics::Instance()->SCREEN_HEIGHT + OFF_SCREEN_BUFFER 
                    || bulletPos.x < -OFF_SCREEN_BUFFER || bulletPos.x > Graphics::Instance()->SCREEN_WIDTH + OFF_SCREEN_BUFFER){
                    Reload();
                }
                break;
        }
    }
}

void Bullet::Render(){
    if (Active())
        mBulletTex->Render();
}

void Bullet::GetPlayerPos(Vector2 pos){
    mPlayerPos = pos;
}