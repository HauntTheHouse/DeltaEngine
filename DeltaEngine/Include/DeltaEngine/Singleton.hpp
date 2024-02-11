#pragma once

#include "Log.hpp"

namespace Delta
{

template <typename T>
class Singleton
{
public:
    Singleton()
    {
        ASSERT(!s_Singleton);
        s_Singleton = (T*)this;
    }
    ~Singleton() { ASSERT(s_Singleton); s_Singleton = nullptr; }

    static T& GetInstance() { ASSERT(s_Singleton); return *s_Singleton; }

private:
    static inline T* s_Singleton{ nullptr };

};

} // namespace Delta
