#include "PlayScreen.h"

PlayScreen::PlayScreen(){
    mInput = InputManager::Instance();

    mPlayer = new Player();
    mPlayer->Parent(this);
    mPlayer->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f, Graphics::Instance()->SCREEN_HEIGHT*0.8f));
    mPlayer->Scale(VEC2_ONE*0.5f);

    mTopBar = new GameEntity(VEC2_ZERO);
    
    mScore = 0;
    mScoreTex = nullptr;
    UpdateScore(0);

    mHpBarOuter = new Texture("hp_bar_outer_v2.png");
    mHpBarInner = new Texture("hp_bar_inner_v2.png");
    mScoreLabel = new Texture("SCORE", "Karmatic_Arcade.ttf", 22, {255, 255, 255});
    mScoreLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.05f, 20));

    mScoreLabel->Parent(mTopBar);
    mHpBarOuter->Parent(mTopBar);
    mHpBarInner->Parent(mTopBar);

    mHP = {1.0f, 1.0f};
    mHpBarOuter->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.89f, 20));
    mHpBarInner->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.905f, 20));
    
    mTopBar->Parent(this);

    mBackGround = new GameEntity(VEC2_ZERO);
    
    mCosmos = new Texture("Cosmos.png");
   
    mCosmos->Parent(mBackGround);
    mCosmos->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f, Graphics::Instance()->SCREEN_HEIGHT*0.5f));

    mBackGround->Parent(this);

    mWaveCounter = 0;

    // Enemy::createPaths({670, 0.0f}, {670, -5.0f}, {670, 100}, {670, 100 + 5.0f}, 10);
    // mEnemy.push_back(std::vector<Enemy *>());
    // mEnemy[0].push_back(new Enemy(0, Enemy::GAMMA));
    // mEnemy[0][0]->Parent(this);
}

void PlayScreen::CreateEnemyPaths(){
    if(Enemy::sPathsEmpty()){
        for(int i = 0; i < MAX_ROWS; i++){
            for(int j = 0; j < MAX_COLUMNS; j++){
                float xPos = 213.3f * (j+1);
                float yPos = 70.0f * (i+1);
                Enemy::createPaths({xPos, 0.0f}, {xPos, -5.0f}, {xPos, yPos}, {xPos, yPos + 5.0f}, 10);
            }
        }
    } 
}

std::vector<std::vector<Enemy *>> PlayScreen::CreateEnemies(std::vector<std::vector<Enemy *>> &EnemyMatrix){
    srand(time(NULL));
    int counter = 0;
    for(int i = 0; i < MAX_ROWS; i++){
        EnemyMatrix.push_back(std::vector<Enemy *>());
        for(int j = 0; j < MAX_COLUMNS; j++){
            int prob = rand() % 100 + 1;
            if(prob >= 10 && prob < 20 && i <= 1){
                EnemyMatrix[i].push_back(new Enemy(counter, Enemy::BETA));
            }
            else if(prob >= 20 && prob <= 25 && i >= 1){
                EnemyMatrix[i].push_back(new Enemy(counter, Enemy::GAMMA));
            }
            else{
                EnemyMatrix[i].push_back(new Enemy(counter));
            }
            EnemyMatrix[i][j]->Parent(this);
            counter++;
        }
    }
    return EnemyMatrix;
}

bool PlayScreen::CheckEnemyActivity(){
    for(auto &row : mEnemy)
        for(auto &enemy : row)
            if(enemy->Active())
                return false;
    return true;
}

void PlayScreen::UnexpectedAttack(){
    CreateEnemyPaths();
    if(mEnemy.empty())
        mEnemy = CreateEnemies(mEnemy);
    
    if(CheckEnemyActivity()){
        mNextEnemy = CreateEnemies(mNextEnemy);
        mEnemy = mNextEnemy;
        mNextEnemy.clear();
        mWaveCounter++;
    }

    if(mWaveCounter > 1){
        std::cout << "You've won!" << '\n';
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
                                Vector2 newHP = {mHP.x-=0.20f, mHP.y};
                                mHpBarInner->Pos(mHpBarInner->Pos() - Vector2(21.0f, 0.0f));
                                mHpBarInner->Scale(newHP);
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
    UnexpectedAttack();
    for(int i = 0; i < MAX_ROWS-1; i++){
        for(int j = 0; j < MAX_COLUMNS; j++){
            if(mEnemy[i][j]->Active() && mEnemy[i+1][j]->Active() && mEnemy[i][j]->mType != Enemy::BETA){
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
    if(mScoreTex != nullptr){
        delete mScoreTex;
        mScoreTex = nullptr;
    }
    mScoreTex = new Texture(std::to_string(mScore), "Karmatic_Arcade.ttf", 22, {255, 255, 255});
    mScoreTex->Parent(mTopBar);
    mScoreTex->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.15f, 20));
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

    delete mScoreLabel;
    mScoreLabel = nullptr;

    delete mScoreTex;
    mScoreTex = nullptr; 

    delete mHpBarOuter;
    mHpBarOuter = nullptr;

    delete mHpBarInner;
    mHpBarInner = nullptr;

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
    mScoreLabel->Render();
    mScoreTex->Render();
    mHpBarOuter->Render();
    mHpBarInner->Render();
    mPlayer->Render();

    for(auto &row : mEnemy)
        for(auto &enemy : row)
            enemy->Render();
}