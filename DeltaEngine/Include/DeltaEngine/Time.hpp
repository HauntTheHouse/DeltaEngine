#pragma once

namespace Delta
{

class Time
{
public:
    static float GetSeconds();
    static float GetMilliseconds() { return GetSeconds() * 1000.0f; }
};

class Timestep
{
public:
    Timestep(float time = 0.0f) : m_Time(time) {}
    operator float() const { return m_Time; }

    float GetSeconds() const { return m_Time; }
    float GetMilliseconds() const { return m_Time * 1000.0f; }

private:
    float m_Time;

};

} // namespace Delta
