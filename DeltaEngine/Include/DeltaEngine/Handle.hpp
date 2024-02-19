#pragma once

#include <cstdint>
#include "Log.hpp"

namespace Delta
{

template <typename TAG>
class Handle
{
public:
    Handle() : m_Handle(0) {}

    void Init(uint32_t index);

    uint16_t GetIndex() const { return m_Index; }
    uint16_t GetMagic() const { return m_Magic; }
    uint32_t GetHandle() const { return m_Handle; }
    bool IsNull() const { return !m_Handle; }

    operator uint32_t() const { return m_Handle; }

    bool operator!= (Handle<TAG> rhs)
    { return m_Handle != rhs.m_Handle; }
    bool operator== (Handle<TAG> rhs)
    { return m_Handle == rhs.m_Handle; }

private:
    union
    {
        struct
        {
            uint16_t m_Index; // Index into resource array
            uint16_t m_Magic; // Magic number to check
        };
        uint32_t m_Handle;
    };
};

template <typename TAG>
void Handle<TAG>::Init(uint32_t index)
{
    ASSERT(IsNull());
    ASSERT(index <= UINT16_MAX);

    static uint32_t s_AutoMagic{ 0 };
    if (++s_AutoMagic > UINT16_MAX)
        s_AutoMagic = 1; // 0 is used for "null handle"

    m_Index = index;
    m_Magic = s_AutoMagic;
}

} // namespace BattleCity
