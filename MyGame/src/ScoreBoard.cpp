#include "ScoreBoard.h"

ScoreBoard::ScoreBoard(){
    mScoreFile = "./Assets/ScoreBoard.txt";
    mInput = InputManager::Instance();

    mTopBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f, Graphics::Instance()->SCREEN_HEIGHT*0.2f));
    mScoreBoardTitle = new Texture("SCOREBOARD", "Arcades.ttf", 72, {230,230,230});
    mScoreBoardTitle->Parent(mTopBar);
    mScoreBoardTitle->Pos(VEC2_ZERO);
    mTopBar->Parent(this);

    mMidBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f, Graphics::Instance()->SCREEN_HEIGHT*0.35f));
    mOne = new Texture("1. ", "Arcades.ttf", 36, {230,230,230});
    mTwo = new Texture("2. ", "Arcades.ttf", 36, {230,230,230});
    mThree = new Texture("3. ", "Arcades.ttf", 36, {230,230,230});
    mFour = new Texture("4. ", "Arcades.ttf", 36, {230,230,230});
    mFive = new Texture("5. ", "Arcades.ttf", 36, {230,230,230});

    mOne->Parent(mMidBar);
    mTwo->Parent(mMidBar);
    mThree->Parent(mMidBar);
    mFour->Parent(mMidBar);
    mFive->Parent(mMidBar);

    mOne->Pos(Vector2(-100.0f, 0.0f));
    mTwo->Pos(Vector2(-100.0f, 45.0f));
    mThree->Pos(Vector2(-100.0f, 90.0f));
    mFour->Pos(Vector2(-100.0f, 135.0f));
    mFive->Pos(Vector2(-100.0f, 180.0f));

    mScoreOne = nullptr;
    mScoreTwo = nullptr;
    mScoreThree = nullptr;
    mScoreFour = nullptr;
    mScoreFive = nullptr;
    CreateScoreTable();
    mMidBar->Parent(this);

    mDownBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f, Graphics::Instance()->SCREEN_HEIGHT*0.8f));
    mCursor = new Texture("--", "Karmatic_Arcade.ttf", 32, {230,230,230});
    mExitButton = new Texture("EXIT", "Karmatic_Arcade.ttf", 32, {230,230,230});
    mCursor->Parent(mDownBar);
    mExitButton->Parent(mDownBar);

    mCursor->Pos(Vector2(-100.0f, 0.0f));
    mExitButton->Pos(VEC2_ZERO);

    mDownBar->Parent(this);

}

ScoreBoard::~ScoreBoard(){
    mInput = nullptr;

    delete mScoreBoardTitle;
    mScoreBoardTitle = nullptr;

    delete mTopBar;
    mTopBar = nullptr;

    delete mScoreOne;
    mScoreOne = nullptr;

    delete mScoreTwo;
    mScoreTwo = nullptr;

    delete mScoreThree;
    mScoreThree = nullptr;

    delete mScoreFour;
    mScoreFour = nullptr;

    delete mScoreFive;
    mScoreFive = nullptr;

    delete mOne;
    mOne = nullptr;

    delete mTwo;
    mTwo = nullptr;

    delete mThree;
    mThree = nullptr;

    delete mFour;
    mFour = nullptr;

    delete mFive;
    mFive = nullptr;

    delete mMidBar;
    mMidBar = nullptr;

    delete mCursor;
    mCursor = nullptr;

    delete mExitButton;
    mExitButton = nullptr;

    delete mDownBar;
    mDownBar = nullptr;

}

void ScoreBoard::CreateScoreTable(){
    InitScores();

    if(mScoreOne != nullptr && mScoreTwo != nullptr){
        delete mScoreOne;
        mScoreOne = nullptr;

        delete mScoreTwo;
        mScoreTwo = nullptr;

        delete mScoreThree;
        mScoreThree = nullptr;

        delete mScoreFour;
        mScoreFour = nullptr;

        delete mScoreFive;
        mScoreFive = nullptr;
    }

    std::vector<std::string> mLabels;

    for(auto &record : mScoreArray){
        if(record != 0)
            mLabels.push_back(std::to_string(record));
        else
            mLabels.push_back("--EMPTY--");
    }

    mScoreOne = new Texture(mLabels[0], "Arcades.ttf", 36, {230,230,230});
    mScoreTwo = new Texture(mLabels[1], "Arcades.ttf", 36, {230,230,230});
    mScoreThree = new Texture(mLabels[2], "Arcades.ttf", 36, {230,230,230});
    mScoreFour = new Texture(mLabels[3], "Arcades.ttf", 36, {230,230,230});
    mScoreFive = new Texture(mLabels[4], "Arcades.ttf", 36, {230,230,230});

    mScoreOne->Parent(mMidBar);
    mScoreTwo->Parent(mMidBar);
    mScoreThree->Parent(mMidBar);
    mScoreFour->Parent(mMidBar);
    mScoreFive->Parent(mMidBar);

    mScoreOne->Pos(Vector2(47.0f, 0.0f));
    mScoreTwo->Pos(Vector2(47.0f, 45.0f));
    mScoreThree->Pos(Vector2(47.0f, 90.0f));
    mScoreFour->Pos(Vector2(47.0f, 135.0f));
    mScoreFive->Pos(Vector2(47.0f, 180.0f));

    mLabels.clear();

}

void ScoreBoard::InitScores() {
    std::ifstream mFile(mScoreFile);
    if(!mFile.is_open()){
        std::cerr << "[ERROR] There's a problem with opening the file: " << mScoreFile << '\n';
        return;
    }

    mScoreArray.clear();
    std::string line;
    while(std::getline(mFile, line)){
        if(!line.empty()){
            try{
                mScoreArray.push_back(std::stoi(line));
            } 
            catch (const std::invalid_argument& e) {
                std::cerr << "[ERROR] Invalid score in file: " << line << '\n';
            }
        }
    }
    mFile.close();
}

void ScoreBoard::ScoreBoardUpdate(){
    if(mScoreArray[MAX_SCORES-1] < mScore){
        mScoreArray.pop_back();
        mScoreArray.push_back(mScore);

        for(int i = 0; i < MAX_SCORES; i++){
            for(int j = MAX_SCORES - 1; j > i; j--)
                if(mScoreArray[j] > mScoreArray[j-1])
                    std::swap(mScoreArray[j], mScoreArray[j-1]); 
        }
    }
}

void ScoreBoard::ManageFile(){
    InitScores();
    ScoreBoardUpdate();
    WriteToFile();
}

void ScoreBoard::WriteToFile() {
    std::ofstream mFile(mScoreFile);
    if(!mFile.is_open()){
        std::cerr << "[ERROR] There's a problem with opening the file: " << mScoreFile << '\n';
        return;
    }

    for(const auto& record : mScoreArray){
        mFile << record << '\n';
    }

    mFile.close();
}
    

void ScoreBoard::SetNewScore(int newScore){
    mScore = newScore;
    ManageFile();
}

void ScoreBoard::Update(){
    CreateScoreTable();
}

void ScoreBoard::Render(){
    mScoreBoardTitle->Render();

    mScoreOne->Render();
    mScoreTwo->Render();
    mScoreThree->Render();
    mScoreFour->Render();
    mScoreFive->Render();

    mOne->Render();
    mTwo->Render();
    mThree->Render();
    mFour->Render();
    mFive->Render();

    mCursor->Render();
    mExitButton->Render();

}
