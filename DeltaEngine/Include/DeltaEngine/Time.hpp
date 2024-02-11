#pragma once

namespace Delta
{

class Time
{
public:
    template<typename T>
    inline static T GetSeconds()
    {
        return static_cast<T>(GetNativeTime());
    }
    template<typename T>
    inline static T GetMilliseconds()
    {
        return static_cast<T>(GetNativeTime() * 1000.0);
    }
private:
    static double GetNativeTime();
};

class Timestep
{
public:
    Timestep(double time = 0) : m_Time(time) {}

    template<typename T>
    inline T GetSeconds() const { return static_cast<T>(m_Time); }
    template<typename T>
    inline T GetMilliseconds() const { return static_cast<T>(m_Time * 1000.0); }

private:
    double m_Time;
};

} // namespace Delta
