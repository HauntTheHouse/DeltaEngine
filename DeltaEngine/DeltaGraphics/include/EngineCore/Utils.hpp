#pragma once

namespace Delta
{

namespace Utils
{
    template<typename Container>
    size_t getSizeInBytes(Container&& container)
    {
        return container.size() * sizeof(typename std::remove_reference<Container>::type::value_type);
    }
}

}