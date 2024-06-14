#include "HostileEntity.h"

std::vector<std::vector<Vector2>> HostileEntity::sPaths;
unsigned int HostileEntity::sPathsNumber = 0;

void HostileEntity::createPaths(Vector2 vec1, Vector2 vec2, Vector2 vec3, Vector2 vec4, int samples){
    BezierPath * path = new BezierPath;
    path->AddCurve({vec1, vec2, vec3, vec4}, samples);
    sPaths.push_back(std::vector<Vector2>());
    path->Sample(&sPaths[sPathsNumber]);
    sPathsNumber += 1;
    
    delete path;
    path = nullptr;
}

void HostileEntity::CreateEnemyPaths(){
    if(sPaths.empty()){
        createPaths({640.f, 0.0f}, {640.0f, -5.0f}, {640.0f, 200.0f}, {640.0f, 210.0f}, 2);
        createPaths({640.0f, 200.0f}, {1280.0f, 0.0f}, {1280.0f, 600.0f}, {500.0f, 200.0f}, 20);
        createPaths({640.0f, 200.0f}, {0.0f, 0.0f}, {0.0f, 600.0f}, {780.0f, 200.0f}, 20);
        float offset = 100.0f;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 5; j++){
                float xPos = 213.3f * (j+1);
                float yPos = offset + 80.0f * i;
                createPaths({xPos, -40.0f}, {xPos, -45.0f}, {xPos, yPos}, {xPos, yPos + 5.0f}, 10);
            }
        }
    }
}

HostileEntity::HostileEntity(){
    mTimer = Timer::Instance();

    mInPosition = false;
    mNoCollisions = true;
    mCurrState = FLY;
}

HostileEntity::~HostileEntity(){
    mTimer = nullptr;
}

void HostileEntity::HandleFlyState(){
    if(((sPaths[mCurrPath][mCurrWayPoint] - Pos())).MagnitudeSqrt() < EPSIOLON)
        mCurrWayPoint++;

    if(mCurrWayPoint < sPaths[mCurrPath].size()){
        Vector2 distance = sPaths[mCurrPath][mCurrWayPoint] - Pos();
        Translate(distance.Normalized() * mTimer->DeltaTime() * mSpeed);
    }
    else
        mCurrState = FORMATION;
}

void HostileEntity::HandleFormationState(){
    InPosition(true);
}

void HostileEntity::HandleStates(){
    switch(mCurrState){
        case FLY:
            HandleFlyState();
            break;
        case FORMATION:
            HandleFormationState();
            break;
    }
}

HostileEntity::STATES HostileEntity::currState(){
    return mCurrState;
}

void HostileEntity::InPosition(bool inPos){
    mInPosition = inPos;
}

bool HostileEntity::InPosition(){
    return mInPosition;
}

void HostileEntity::NoCollisions(bool noCol){
    mNoCollisions = noCol;
}

bool HostileEntity::NoCollisions(){
    return mNoCollisions;
}

void HostileEntity::HandleFiring() {
    
}

void HostileEntity::LoseHP(int change) {
    mHP -= change;
}

int HostileEntity::GetHP(){
    return mHP;
}

void HostileEntity::Update(){

}

void HostileEntity::Render(){

}