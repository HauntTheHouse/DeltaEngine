#pragma once

#include "Handle.hpp"
#include <vector>

namespace Delta
{

template <typename Data, typename Handle>
class HandleManager
{
public:
    HandleManager() = default;
    ~HandleManager() = default;

    Data& Acquire(Handle& handle);
    void Release(Handle handle);
    void ReleaseAll();

    Data& Dereference(Handle handle);
    const Data& Dereference(Handle handle) const;

    unsigned int GetUsedHandleCount() const { return m_MagicNumbers.size() - m_FreeSlots.size(); }
    bool HasUsedHandleCount() const { return !!GetUsedHandleCount(); }

    template<typename Function>
    void ForEach(Function func)
    {
        for (size_t i = 0; i < m_UserData.size(); ++i)
        {
            if (m_MagicNumbers[i] != 0)
            {
                func(m_UserData[i]);
            }
        }
    }

private:
    std::vector<Data> m_UserData;
    std::vector<unsigned int> m_MagicNumbers;
    std::vector<unsigned int> m_FreeSlots;

};


template <typename Data, typename Handle>
inline Data& HandleManager<Data, Handle>::Acquire(Handle& handle)
{
    // If free list is empty, add a new one, otherwise use first one found
    unsigned int index;
    if (m_FreeSlots.empty())
    {
        index = static_cast<unsigned int>(m_MagicNumbers.size());
        handle.Init(index);
        m_UserData.emplace_back(Data());
        m_MagicNumbers.push_back(handle.GetMagic());
    }
    else
    {
        index = m_FreeSlots.back();
        handle.Init(index);
        m_FreeSlots.pop_back();
        m_MagicNumbers[index] = handle.GetMagic();
    }
    return m_UserData[index];
}

template <typename Data, typename Handle>
inline void HandleManager<Data, Handle>::Release(Handle handle)
{
    unsigned int index = handle.GetIndex();

    ASSERT(index < m_UserData.size());
    ASSERT(m_MagicNumbers[index] == handle.GetMagic());

    // Remove it - tag as unused and add to free list
    m_MagicNumbers[index] = 0;
    m_FreeSlots.push_back(index);
}

template<typename Data, typename Handle>
inline void HandleManager<Data, Handle>::ReleaseAll()
{
    m_UserData.clear();
    m_MagicNumbers.clear();
    m_FreeSlots.clear();
}

template <typename Data, typename Handle>
inline Data& HandleManager<Data, Handle>::Dereference(Handle handle)
{
    ASSERT(!handle.IsNull());

    unsigned int index = handle.GetIndex();

    ASSERT(index < m_UserData.size());
    ASSERT(m_MagicNumbers[index] == handle.GetMagic());

    return m_UserData[index];
}

template <typename Data, typename Handle>
inline const Data& HandleManager<Data, Handle>::Dereference(Handle handle) const
{
    return const_cast<HandleManager<Data, Handle>*>(this)->Dereference(handle);
}

} // namespace Delta
