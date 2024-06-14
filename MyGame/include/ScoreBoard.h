#ifndef SCOREBOARD_H_
#define SCOREBOARD_H_

#include "InputManager.h"
#include "Texture.h"
#include <fstream>

class ScoreBoard : public GameEntity{
private:

    InputManager * mInput;

    GameEntity * mTopBar;
    GameEntity * mMidBar;
    GameEntity * mDownBar;
    
    Texture * mScoreBoardTitle;

    Texture * mScoreOne;
    Texture * mScoreTwo;
    Texture * mScoreThree;
    Texture * mScoreFour;
    Texture * mScoreFive;

    Texture * mOne;
    Texture * mTwo;
    Texture * mThree;
    Texture * mFour;
    Texture * mFive;

    Texture * mCursor;
    Texture * mExitButton;

    std::string mScoreFile;
    static const int MAX_SCORES = 5;
    std::vector<int> mScoreArray;
    int mScore;

public:

    ScoreBoard();
    ~ScoreBoard();

    void SetNewScore(int newScore = 0);
    void Update();
    void Render();

private:

    void ChangeMode(int mode);
    void CreateScoreTable();
    void InitScores();
    void ScoreBoardUpdate();
    void ManageFile();
    void WriteToFile();

};

#endif