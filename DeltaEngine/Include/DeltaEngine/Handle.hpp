#pragma once

#include "Log.hpp"

namespace Delta
{

    template <typename TAG>
    class Handle
    {
    public:
        Handle() : m_Handle(0) {}

        void Init(unsigned int index);

        unsigned int GetIndex() const { return m_Index; }
        unsigned int GetMagic() const { return m_Magic; }
        unsigned int GetHandle() const { return m_Handle; }
        bool IsNull() const { return !m_Handle; }

        operator unsigned int() const { return m_Handle; }

    private:
        union
        {
            enum
            {
                // sizes to use for bit fields
                MAX_BITS_INDEX = 16,
                MAX_BITS_MAGIC = 16,

                // sizes to compare against for asserting dereferences
                MAX_INDEX = (1 << MAX_BITS_INDEX) - 1,
                MAX_MAGIC = (1 << MAX_BITS_MAGIC) - 1
            };
            struct
            {
                unsigned int m_Index : MAX_BITS_INDEX; // index into resource array
                unsigned int m_Magic : MAX_BITS_MAGIC; // magic number to check
            };
            unsigned int m_Handle;
        };
    };

    template <typename TAG>
    void Handle<TAG>::Init(unsigned int index)
    {
        ASSERT(IsNull());
        ASSERT(index <= MAX_INDEX);

        static unsigned int s_AutoMagic{ 0 };
        if (++s_AutoMagic > MAX_MAGIC)
            s_AutoMagic = 1; // 0 is used for "null handle"

        m_Index = index;
        m_Magic = s_AutoMagic;
    }

    template<typename TAG>
    inline bool operator!= (Handle<TAG> l, Handle<TAG> r) { return l.GetHandle() != r.GetHandle(); }
    template<typename TAG>
    inline bool operator== (Handle<TAG> l, Handle<TAG> r) { return l.GetHandle() == r.GetHandle(); }

} // namespace BattleCity
