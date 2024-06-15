#include "GameEntity.h"

GameEntity::GameEntity(Vector2 pos){
    
    mPos = pos;
    mParent = nullptr;
    mRotation = 0.0f;
    mActive = true;
    mScale = VEC2_ONE;
    
}

GameEntity::~GameEntity(){
    Parent(nullptr);    
}

void GameEntity::Pos(Vector2 pos){
    mPos = pos;
}

Vector2 GameEntity::Pos(SPACE space){
    if(space == local || mParent == nullptr)
        return mPos;
    
    Vector2 parentScale = mParent->Scale(world);
    Vector2 rotPos(mPos.x * parentScale.x, mPos.y * parentScale.y);
    rotPos = Rotatevector(rotPos, mParent->Rotation(local));

    return mParent->Pos(world) + rotPos;
}

void GameEntity::Rotation(float rotation){
    mRotation = rotation;
    if(mRotation > 360.0f){
        int mul = mRotation / 360;
        mRotation -= (360.0f*mul);
    }
    else if(mRotation < 0.0f){
        int mul = (mRotation / 360)-1;
        mRotation -= (360.0f*mul);
    }
}

float GameEntity::Rotation(SPACE space){
    if(space == local || mParent == nullptr)
        return mRotation;
    else    
        return mParent->Rotation(world) + mRotation;
}

void GameEntity::Active(bool active){
    mActive = active;
}

bool GameEntity::Active(){
    return mActive;
}

void GameEntity::Parent(GameEntity * parent){
    if(parent == nullptr){
        mPos = Pos(world);
        mScale = Scale(world);
        mRotation = Rotation(world);
    }
    else{
        if(mParent != nullptr)
            Parent(nullptr);
        Vector2 parentScale = parent->Scale(world);
        Vector2 pom(Pos(world) - parent->Pos(world));
        mPos = Rotatevector(pom, -parent->Rotation(world));
        mPos.x /= parentScale.x;
        mPos.y /= parentScale.y;

        mRotation = mRotation - parent->Rotation(world);
        mScale = Vector2(mScale.x / parentScale.x, mScale.y / parentScale.y);
    }
    mParent = parent;  
}

GameEntity * GameEntity::Parent(){
    return mParent;
}

void GameEntity::Update(){

}

void GameEntity::Render(){

}

void GameEntity::Translate(Vector2 vec, SPACE space){
    if(space == world)
        mPos += vec;
    else
        mPos += Rotatevector(vec, Rotation());
}

void GameEntity::Scale(Vector2 scale){
    mScale = scale;
}

Vector2 GameEntity::Scale(SPACE space){
    if(space == local || mParent == nullptr)
			return mScale;

	Vector2 scale = mParent->Scale(world);
	scale.x *= mScale.x;
	scale.y *= mScale.y;

    return scale;
}

void GameEntity::Rotate(float amount){
    mRotation += amount;
}