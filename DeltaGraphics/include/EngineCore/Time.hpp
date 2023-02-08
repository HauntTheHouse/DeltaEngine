#pragma once

namespace Delta
{

class Time
{
public:
    static float get();

};

class Timestep
{
public:
    Timestep(float aTime = 0.0f) : mTime(aTime) {}
    operator float() const { return mTime; }

    float getSeconds() const { return mTime; }
    float getMilliseconds() const { return mTime * 1000.0f; }

private:
    float mTime;

};

}
