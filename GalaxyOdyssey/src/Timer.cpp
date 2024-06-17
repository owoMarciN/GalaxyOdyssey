#include "Timer.h"

Timer * Timer::sInstance = nullptr;

Timer * Timer::Instance(){
    if (sInstance == nullptr)
        sInstance = new Timer;
    return sInstance;
}
void Timer::Release(){
    delete sInstance;
    sInstance = nullptr;
}

void Timer::Reset(){
    mStartTicks = SDL_GetTicks();
    mElapsedTicks = 0;
    mDeltaTime = 0.0f;
}

float Timer::DeltaTime() {
    return mDeltaTime;
}

void Timer::TimeScale(float t) {
    mTimeScale = t;
}

float Timer::TimeScale() {
    return mTimeScale;
}

void Timer::Update() {
    mElapsedTicks = SDL_GetTicks() - mStartTicks;
    mDeltaTime = mElapsedTicks * 0.001f;
}

Timer::Timer() {
    mTimeScale = 1.0f;
    Reset();
}