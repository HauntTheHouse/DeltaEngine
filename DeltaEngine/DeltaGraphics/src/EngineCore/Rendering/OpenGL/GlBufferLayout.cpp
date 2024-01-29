#include "PCH.hpp"
#include "EngineCore/Rendering/BufferLayout.hpp"

#include <glad/glad.h>

namespace Delta
{

void ShaderData::Construct(Type shaderDataType)
{
    switch (shaderDataType)
    {
    case Type::INT:
    case Type::INT2:
    case Type::INT3:
    case Type::INT4:
        m_Type = GL_INT;
        m_Count = ((GLint)shaderDataType - (GLint)Type::INT + 1);
        m_Size = sizeof(GLint) * m_Count;
        break;
    case Type::UINT:
    case Type::UINT2:
    case Type::UINT3:
    case Type::UINT4:
        m_Type = GL_UNSIGNED_INT;
        m_Count = ((GLint)shaderDataType - (GLint)Type::UINT + 1);
        m_Size = sizeof(GLuint) * m_Count;
        break;
    case Type::FLOAT:
    case Type::FLOAT2:
    case Type::FLOAT3:
    case Type::FLOAT4:
        m_Type = GL_FLOAT;
        m_Count = ((GLint)shaderDataType - (GLint)Type::FLOAT + 1);
        m_Size = sizeof(GLfloat) * m_Count;
        break;
    }
}

BufferLayout::BufferLayout(std::initializer_list<ShaderData::Type> initList)
{
    Init(initList);
}

BufferLayout::BufferLayout(const std::vector<ShaderData::Type>& shaderDataTypes)
{
    Init(shaderDataTypes);
}

void BufferLayout::Init(const std::vector<ShaderData::Type>& shaderDataTypes)
{
    m_Elements.reserve(shaderDataTypes.size());

    GLint offset = 0;
    for (const auto& shaderDataType : shaderDataTypes)
    {
        BufferElement element;
        element.shaderData.Construct(shaderDataType);
        element.offset = offset;

        offset += element.shaderData.GetSize();
        m_Stride += element.shaderData.GetSize();

        m_Elements.push_back(std::move(element));
    }
}

} // namespace Delta
