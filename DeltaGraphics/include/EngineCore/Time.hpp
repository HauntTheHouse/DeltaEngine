#pragma once

namespace Delta
{

class Time
{
public:
    static double get();

};

class Timestep
{
public:
    Timestep(double aTime = 0.0) : mTime(aTime) {}
    explicit operator double() const { return mTime; }
    explicit operator float() const { return static_cast<float>(mTime); }

    double getSeconds() const { return mTime; }
    double getMilliseconds() const { return mTime * 1000.0; }

private:
    double mTime;

};

}
