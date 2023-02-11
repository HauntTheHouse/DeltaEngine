#include "EngineCore/Rendering/OpenGL/BufferLayout.hpp"

namespace Delta
{

void ShaderData::construct(Type aShaderDataType)
{
}

BufferLayout::BufferLayout(std::initializer_list<ShaderData::Type> aInitList)
{
    init(aInitList);
}

BufferLayout::BufferLayout(const std::vector<ShaderData::Type>& aShaderDataTypes)
{
    init(aShaderDataTypes);
}

void BufferLayout::init(const std::vector<ShaderData::Type>& aShaderDataTypes)
{
}

} // namespace Delta
