#include "PlayScreen.h"

PlayScreen::PlayScreen(){
    mInput = InputManager::Instance();
    mTimer = Timer::Instance();
    mEnemySpawner = EnemySpawner::Instance();
    mAudio = AudioManager::Instance();

    mPlayer = new Player();
    mPlayer->Parent(this);
    mPlayer->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f, Graphics::Instance()->SCREEN_HEIGHT*0.8f));
    mPlayer->Scale(VEC2_ONE*0.5f);

    mTopBar = new GameEntity(VEC2_ZERO);
    mScore = 0;
    mScoreTex = nullptr;
    UpdateScore(mScore);

    mHpBarOuter = new Texture("hp_bar_outer_v2.png");
    mHpBarInner = new Texture("hp_bar_inner_v2.png");
    mSpecialMeter = new Texture("SpecialMeter.png");
    mSpecialMeterFrame = new Texture("SpecialMeterFrame.png");
    mScoreLabel = new Texture("SCORE", "Karmatic_Arcade.ttf", 22, {255, 255, 255});
    
    mHP = {1.0f, 1.0f};
    mScoreLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.05f, 20));
    mHpBarOuter->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.89f, 20));
    mHpBarInner->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.905f, 20));
    mSpecialMeter->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.905f, 50));
    mSpecialMeterFrame->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.89f, 50));
    
    mScoreLabel->Parent(mTopBar);
    mHpBarOuter->Parent(mTopBar);
    mHpBarInner->Parent(mTopBar);
    mSpecialMeter->Parent(mTopBar);
    mSpecialMeterFrame->Parent(mTopBar);
    mMeterState = IDLE;
    
    mTopBar->Parent(this);

    mBackGround = new GameEntity(VEC2_ZERO);
    mCosmos = new Texture("Cosmos.png");
   
    mCosmos->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f, Graphics::Instance()->SCREEN_HEIGHT*0.5f));
    mCosmos->Parent(mBackGround);
    
    mBackGround->Parent(this);
    ChangeGameFlow();

    HostileEntity::CreateEnemyPaths();
    mBoss = new Boss(0);
}


PlayScreen::~PlayScreen(){
    mInput = nullptr;
    mTimer = nullptr;
    mAudio = nullptr;

    EnemySpawner::Release();
    mEnemySpawner = nullptr;

    delete mPlayer;
    mPlayer = nullptr;

    delete mBoss;
    mBoss = nullptr;
    
    delete mCosmos;
    mCosmos = nullptr;

    delete mScoreLabel;
    mScoreLabel = nullptr;

    delete mScoreTex;
    mScoreTex = nullptr; 

    delete mHpBarOuter;
    mHpBarOuter = nullptr;

    delete mHpBarInner;
    mHpBarInner = nullptr;

    delete mSpecialMeter;
    mSpecialMeter = nullptr;

    delete mSpecialMeterFrame;
    mSpecialMeterFrame = nullptr;

    delete mTopBar;
    mTopBar = nullptr;

    delete mBackGround;
    mBackGround = nullptr;
}

void PlayScreen::PlayerToBossCollision(){
    if(mBoss->Active() && mBoss->GetHP() > 0){
        for(auto &bullet : mPlayer->mBullet){
            if(bullet->Active()){
                // Use bounding box collision detection
                Vector2 bulletPos = bullet->Pos();
                Vector2 bossPos = mBoss->Pos();
                        
                // Define the bounding box for the boss
                float bossLeft = bossPos.x - 170; 
                float bossRight = bossPos.x + 170;
                float bossTop = bossPos.y - 60;
                float bossBottom = bossPos.y + 60;
                       
                // Check for collision
                if(bulletPos.x >= bossLeft && bulletPos.x <= bossRight && bulletPos.y >= bossTop && bulletPos.y <= bossBottom){
                    bullet->Reload();
                    mBoss->LoseHP(bullet->mDamage);
                }
            }
        }
        if(mPlayer->mSpecialAttack->Active()){
            Vector2 bulletPos = mPlayer->mSpecialAttack->Pos();
            Vector2 bossPos = mBoss->Pos();
                        
            // Define the bounding box for the boss
            float bossLeft = bossPos.x - 170; 
            float bossRight = bossPos.x + 170;
            float bossTop = bossPos.y - 60;
            float bossBottom = bossPos.y + 60;
                        
            // Check for collision
            if(bulletPos.x >= bossLeft && bulletPos.x <= bossRight && bulletPos.y >= bossTop && bulletPos.y <= bossBottom){
                mPlayer->mSpecialAttack->Reload();
                mBoss->LoseHP(mPlayer->mSpecialAttack->mDamage);
            }    
        }
    }
    if(mBoss->Active() && mBoss->GetHP() <= 0) {
        mBoss->Active(false);
        UpdateScore(mBoss->mScore);
        mCurrFlow = ENEMY_WAVES;
    }
}

void PlayScreen::BossToPlayerCollision(){
    if(mPlayer->Active() && mPlayer->GetHP() > 0){
        for(auto &bullet : mBoss->mBullet){
            if(bullet->Active()){
                //Giving the position of the Player to the bullet
                bullet->GetPlayerPos(mPlayer->Pos());

                // Use bounding box collision detection
                Vector2 bulletPos = bullet->Pos();
                Vector2 playerPos = mPlayer->Pos();
                            
                // Define the bounding box for the player
                float playerLeft = playerPos.x - 40;  
                float playerRight = playerPos.x + 40;
                float playerTop = playerPos.y - 50;   
                float playerBottom = playerPos.y + 50;
                            
                 // Check for collision
                if(bulletPos.x >= playerLeft && bulletPos.x <= playerRight && bulletPos.y >= playerTop && bulletPos.y <= playerBottom){
                    bullet->Reload();
                    mPlayer->LoseHP(bullet->mDamage);
                    HPcalculator();
                }
            }
        }
    }
    if(mPlayer->Active() && mPlayer->GetHP() <= 0){
        mPlayer->Active(false);
    }
}

void PlayScreen::ChangeGameFlow() {
    if(mEnemySpawner->CurrentWave() == 5){
        mCurrFlow = BOSSBATTLE;
        if(!Mix_Playing(3))
            mAudio->PlaySFX("FinalBoss.wav", -1, 3);
    }
    else
        mCurrFlow = ENEMY_WAVES;
}

void PlayScreen::PlayerToEnemyCollision() {
    for(auto &row : mEnemySpawner->Instance()->mWave){
        for(auto &enemy : row){
            if(enemy->Active() && enemy->GetHP() > 0){
                for(auto &bullet : mPlayer->mBullet){
                    if(bullet->Active()){
                        // Use bounding box collision detection
                        Vector2 bulletPos = bullet->Pos();
                        Vector2 enemyPos = enemy->Pos();
                        
                        // Define the bounding box for the boss
                        float enemyLeft = enemyPos.x - 32; 
                        float enemyRight = enemyPos.x + 32;
                        float enemyTop = enemyPos.y - 32;
                        float enemyBottom = enemyPos.y + 50;
                        
                        // Check for collision
                        if(bulletPos.x >= enemyLeft && bulletPos.x <= enemyRight && bulletPos.y >= enemyTop && bulletPos.y <= enemyBottom){
                            bullet->Reload();
                            enemy->LoseHP(bullet->mDamage);
                        }
                    }
                }
                if(mPlayer->mSpecialAttack->Active()){
                    Vector2 bulletPos = mPlayer->mSpecialAttack->Pos();
                    Vector2 enemyPos = enemy->Pos();
                        
                        // Define the bounding box for the boss
                    float enemyLeft = enemyPos.x - 32; 
                    float enemyRight = enemyPos.x + 32;
                    float enemyTop = enemyPos.y - 32;
                    float enemyBottom = enemyPos.y + 50;
                        
                        // Check for collision
                    if(bulletPos.x >= enemyLeft && bulletPos.x <= enemyRight && bulletPos.y >= enemyTop && bulletPos.y <= enemyBottom){
                        mPlayer->mSpecialAttack->Reload();
                        enemy->LoseHP(mPlayer->mSpecialAttack->mDamage);
                    }    
                }
            }
            if(enemy->Active() && enemy->GetHP() <= 0) {
                enemy->Active(false);
                UpdateScore(enemy->mScore);
            }
        }
    }
}

void PlayScreen::EnemyToPlayerCollision() {    
    if(mPlayer->Active() && mPlayer->GetHP() > 0){
        for(auto &row : mEnemySpawner->Instance()->mWave){
            for(auto &enemy : row){
                for(auto &bullet : enemy->mBullet){
                    if(bullet->Active()){
                        //Giving the position of the Player to the bullet
                        bullet->GetPlayerPos(mPlayer->Pos());

                        // Use bounding box collision detection
                        Vector2 bulletPos = bullet->Pos();
                        Vector2 playerPos = mPlayer->Pos();
                            
                        // Define the bounding box for the player
                        float playerLeft = playerPos.x - 40;  
                        float playerRight = playerPos.x + 40;
                        float playerTop = playerPos.y - 50;   
                        float playerBottom = playerPos.y + 50;
                            
                        // Check for collision
                        if(bulletPos.x >= playerLeft && bulletPos.x <= playerRight && bulletPos.y >= playerTop && bulletPos.y <= playerBottom){
                            bullet->Reload();
                            mPlayer->LoseHP(bullet->mDamage);
                            HPcalculator();
                        }
                    }
                } //}
            }
        }
    } 
    if(mPlayer->Active() && mPlayer->GetHP() <= 0){
        mPlayer->Active(false);
    }
}

void PlayScreen::HPcalculator() {
    Vector2 newHP = {mHP.x-=0.20f, mHP.y};
    mHpBarInner->Pos(mHpBarInner->Pos() - Vector2(21.0f, 0.0f));
    mHpBarInner->Scale(newHP);
}

void PlayScreen::UpdateSpecial() {
    Uint32 currentTime = SDL_GetTicks();
    switch(mMeterState){
        case IDLE:
            if(mPlayer->SpecialFired()){
                mCurrentScale = mMinScale;
                mSpecialMeter->Scale(Vector2(mCurrentScale, 1.0f));
                //AdjustSpecialMeter();
                mMeterState = SHRINK;
                mTimeFired = currentTime; // Store the current time
            }
            break;
        case SHRINK:
            // After shrinking, move to WAIT state
            mMeterState = WAIT;
            break;
        case WAIT:
            if(currentTime - mTimeFired >= mDelay){
                // Increment the scale of the meter
                mCurrentScale += mScaleIncrement;
                if(mCurrentScale > mMaxScale)
                    mCurrentScale = mMaxScale; // Ensure it doesn't exceed the maximum scale

                mSpecialMeter->Scale(Vector2(mCurrentScale, 1.0f));
                //AdjustSpecialMeter();
                // Check if the meter has reached its maximum scale
                if(mCurrentScale >= mMaxScale)
                    mMeterState = GROW;
                else
                    mTimeFired = currentTime; // Reset the timer for the next increment
            }
            break;
        case GROW:
            // After growing, go back to IDLE state
            mMeterState = IDLE;
            mPlayer->SpecialFired(false); // Reset the special fired flag
            break;
    }
}

void PlayScreen::UpdateScore(int score) {
    mScore += score;
    if(mScoreTex != nullptr){
        delete mScoreTex;
        mScoreTex = nullptr;
    }
    mScoreTex = new Texture(std::to_string(mScore), "Karmatic_Arcade.ttf", 22, {255, 255, 255});
    mScoreTex->Parent(mTopBar);
    mScoreTex->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.15f, 20));
}

int PlayScreen::GetScore() {
    return mScore;
}

void PlayScreen::Update() {
    switch (mCurrFlow) {
        case ENEMY_WAVES:
            mEnemySpawner->Instance()->Update();
            EnemyToPlayerCollision();
            PlayerToEnemyCollision();
            break;
        case BOSSBATTLE:
            mBoss->Update();
            BossToPlayerCollision();
            PlayerToBossCollision();
            break;
    }
    
    mPlayer->Update();
    UpdateSpecial();
}

void PlayScreen::Render(){
    mCosmos->Render();
    mPlayer->Render();

    ChangeGameFlow();
    switch (mCurrFlow) {
        case ENEMY_WAVES:
            mEnemySpawner->Instance()->Render();
            break;
        case BOSSBATTLE:
            mBoss->Render();
            break;
    }

    mScoreLabel->Render();
    mScoreTex->Render();
    mHpBarOuter->Render();
    mHpBarInner->Render();
    mSpecialMeterFrame->Render();
    mSpecialMeter->Render();
}

bool PlayScreen::PlayerActive(){
    return mPlayer->Active();
}

bool PlayScreen::BossActive(){
    return mBoss->Active();
}