#include "DeltaEngine/Utils.hpp"

#include <fstream>
#include <sstream>

namespace Delta::Utils
{

std::string ReadFile(const std::string& path)
{
    std::fstream file(path);
    std::stringstream stream;
    stream << file.rdbuf();
    return stream.str();
}

} // namespace Delta::Utils
