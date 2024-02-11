#pragma once

#include <string>

namespace Delta::Utils
{

template<typename Container>
size_t getSizeInBytes(Container&& container)
{
    return container.size() * sizeof(typename std::remove_reference<Container>::type::value_type);
}

std::string ReadFile(const std::string& path);

} // namespace Delta::Utils
