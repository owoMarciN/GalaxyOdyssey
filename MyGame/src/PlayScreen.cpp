#include "PlayScreen.h"

PlayScreen::PlayScreen(){
    mInput = InputManager::Instance();

    mPlayer = new Player();
    mPlayer->Parent(this);
    mPlayer->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f, Graphics::Instance()->SCREEN_HEIGHT*0.8f));
    mPlayer->Scale(VEC2_ONE*0.5f);

    mTopBar = new GameEntity(VEC2_ZERO);
    
    mScore = 0;
    mPointsTex = nullptr;
    UpdateScore(0);

    mHPTex = new Texture("hp_bar_outer_v2.png");
    mHPBar = new Texture("hp_bar_inner_v2.png");
    mScoreTex = new Texture("SCORE", "Karmatic_Arcade.ttf", 22, {255, 255, 255});
    mScoreTex->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.05f, 20));

    mScoreTex->Parent(mTopBar);
    mHPTex->Parent(this);
    mHPBar->Parent(this);

    mHP = {1.0f, 1.0f};
    newPos = Vector2(Graphics::Instance()->SCREEN_WIDTH*0.905f, 20);

    mHPTex->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.89f, 20));
    mHPBar->Pos(newPos);
    
    mTopBar->Parent(this);

    mBackGround = new GameEntity(VEC2_ZERO);
    
    mCosmos = new Texture("Cosmos.png");
   
    mCosmos->Parent(mBackGround);
    mCosmos->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f, Graphics::Instance()->SCREEN_HEIGHT*0.5f));

    mBackGround->Parent(this);
    UnexpectedAttack();
}

void PlayScreen::UnexpectedAttack(){
    srand(time(NULL));
    if(mEnemy.empty()){
        for(int i = 0; i < MAX_ROWS; i++){
            for(int j = 0; j < MAX_COLUMNS; j++){
                float xPos = 160.0f * (j+1);
                float yPos = 70.0f * (i+1);
                Enemy::createPaths({xPos, 0.0f}, {xPos, -5.0f}, {xPos, yPos}, {xPos, yPos + 5.0f}, 10);
            }
        }    

        int counter = 0;
        for(int i = 0; i < MAX_ROWS; i++){
            mEnemy.push_back(std::vector<Enemy *>());
            for(int j = 0; j < MAX_COLUMNS; j++){
                int prob = rand() % 100 + 1;
                if(prob >= 1 && prob <= 20 && i <= 1){
                    mEnemy[i].push_back(new Enemy(counter, Enemy::BETA));
                }
                else{
                    mEnemy[i].push_back(new Enemy(counter));
                }
                mEnemy[i][j]->Parent(this);
                //mEnemy[i][j]->GetPlayerPos(mPlayer->Pos());
                counter++;
            }
        }
    }
}

void PlayScreen::SamuelsSpear(){

}

void PlayScreen::Flood(){
    
}

void PlayScreen::Annihilation(){

}
    
void PlayScreen::GodHasSinned(){

}

int PlayScreen::ProbabilityCalc(){
    return rand() % 100 + 1;
}

void PlayScreen::HandleEnemyCollision() {
    for(auto &row : mEnemy){
        for(auto &enemy : row){
            if(enemy->Active() && enemy->mHP > 0) {
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
            if(enemy->Active() && enemy->mHP <= 0) {
                enemy->Active(false);
                UpdateScore(enemy->mScore);
            }
        }
    }
}

void PlayScreen::HandlePlayerCollision() {
    if(mPlayer->Active() && mPlayer->mHP > 0){
        for(auto &row : mEnemy){
            for(auto &enemy : row){
                if(enemy->Active()){
                    for(auto &bullet : enemy->mBullet){
                        if(bullet->Active()){
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
                                Vector2 newHP = {mHP.x-=0.20f, mHP.y};
                                mHPBar->Pos(mHPBar->Pos() - Vector2(21.0f, 0.0f));
                                mHPBar->Scale(newHP);
                            }
                        }
                    }
                }
            }
        }
    } 
    if(mPlayer->Active() && mPlayer->mHP <= 0)
        mPlayer->Active(false);
}

void PlayScreen::EnemyFormation(){
    for(int i = 0; i < MAX_ROWS-1; i++){
        for(int j = 0; j < MAX_COLUMNS; j++){
            if(mEnemy[i][j]->Active() && mEnemy[i+1][j]->Active() && mEnemy[i][j]->mType == Enemy::ALPHA){
                mEnemy[i][j]->NoCollisions(false);
            }
            else{
                mEnemy[i][j]->NoCollisions(true);
            }
        }
    }
}

void PlayScreen::UpdateScore(unsigned int score){
    mScore += score;
    if(mPointsTex != nullptr){
        delete mPointsTex;
        mPointsTex = nullptr;
    }
    mPointsTex = new Texture(std::to_string(mScore), "Karmatic_Arcade.ttf", 22, {255, 255, 255});
    mPointsTex->Parent(mTopBar);
    mPointsTex->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.15f, 20));
}

int PlayScreen::GetScore(){
    return mScore;
}

PlayScreen::~PlayScreen(){
    mInput = nullptr;

    delete mPlayer;
    mPlayer = nullptr;
    
    for(auto &row : mEnemy){
        for(auto &enemy : row){
            delete enemy;
            enemy = nullptr;
        }
    }

    delete mCosmos;
    mCosmos = nullptr;

    delete mScoreTex;
    mScoreTex = nullptr;

    delete mPointsTex;
    mPointsTex = nullptr; 

    delete mHPTex;
    mHPTex = nullptr;

    delete mHPBar;
    mHPBar = nullptr;

    delete mTopBar;
    mTopBar = nullptr;

    delete mBackGround;
    mBackGround = nullptr;

}

void PlayScreen::Update(){

    mPlayer->Update();
    
    for(auto &row : mEnemy)
        for(auto &enemy : row)
            enemy->Update();
    EnemyFormation();
    HandleEnemyCollision();
    HandlePlayerCollision();
    
}

void PlayScreen::Render(){
    mCosmos->Render();
    mScoreTex->Render();
    mPointsTex->Render();
    mHPTex->Render();
    mHPBar->Render();
    mPlayer->Render();
    for(auto &row : mEnemy)
        for(auto &enemy : row)
            enemy->Render();
}