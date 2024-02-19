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

    template<typename Function>
    void ForEach(Function&& func);

private:
    struct HandleData
    {
        HandleData()
            : realData()
            , magicNumber(0) {};
        HandleData(uint16_t magicNumber)
            : realData()
            , magicNumber(magicNumber) {};
        HandleData(const HandleData& other)
            : realData(other.realData)
            , magicNumber(other.magicNumber) {}
        ~HandleData() {};

        union
        {
            Data realData;
            uint16_t freeSlotIndex;
        };

        uint16_t magicNumber;
    };

    std::vector<HandleData> m_UserData;
    uint16_t m_NextFreeIndex{ UINT16_MAX };

};


template <typename Data, typename Handle>
inline Data& HandleManager<Data, Handle>::Acquire(Handle& handle)
{
    uint32_t index = m_NextFreeIndex;
    if (index == UINT16_MAX)
    {
        index = static_cast<uint32_t>(m_UserData.size());
        handle.Init(index);
        m_UserData.emplace_back(HandleData(handle.GetMagic()));
    }
    else
    {
        m_NextFreeIndex = m_UserData[index].freeSlotIndex;
        handle.Init(index);
        m_UserData[index].magicNumber = handle.GetMagic();
    }
    return m_UserData[index].realData;
}

template <typename Data, typename Handle>
inline void HandleManager<Data, Handle>::Release(Handle handle)
{
    uint32_t index = handle.GetIndex();

    ASSERT(index < m_UserData.size());
    ASSERT(m_UserData[index].magicNumber == handle.GetMagic());

    m_UserData[index].freeSlotIndex = m_NextFreeIndex;
    m_UserData[index].magicNumber = 0;
    m_NextFreeIndex = index;
}

template<typename Data, typename Handle>
inline void HandleManager<Data, Handle>::ReleaseAll()
{
    m_UserData.clear();
    m_NextFreeIndex = UINT16_MAX;
}

template <typename Data, typename Handle>
inline Data& HandleManager<Data, Handle>::Dereference(Handle handle)
{
    ASSERT(!handle.IsNull());

    uint32_t index = handle.GetIndex();

    ASSERT(index < m_UserData.size());
    ASSERT(m_UserData[index].magicNumber == handle.GetMagic());

    return m_UserData[index].realData;
}

template <typename Data, typename Handle>
inline const Data& HandleManager<Data, Handle>::Dereference(Handle handle) const
{
    return const_cast<HandleManager<Data, Handle>*>(this)->Dereference(handle);
}

template <typename Data, typename Handle>
template<typename Function>
void HandleManager<Data, Handle>::ForEach(Function&& func)
{
    for (size_t i = 0; i < m_UserData.size(); ++i)
    {
        if (m_UserData[i].magicNumber != 0)
        {
            func(m_UserData[i].realData);
        }
    }
}

} // namespace Delta
