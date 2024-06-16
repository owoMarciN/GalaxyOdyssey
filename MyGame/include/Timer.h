#ifndef TIMER_H_
#define TIMER_H_

#include <SDL2/SDL.h>

class Timer{
private:

    static Timer * sInstance;
    unsigned int mStartTicks;
    unsigned int mElapsedTicks;
    float mDeltaTime;
    float mTimeScale;

public:

    static Timer * Instance();
    static void Release();

    void Reset();
    float DeltaTime();
    void TimeScale(float t = 1.0f);
    float TimeScale();
    void Update();

private:

    Timer();
    ~Timer() = default;

};

#endif