#pragma once

#include <vector>

namespace Delta
{

class ShaderData
{
public:
    enum class Type
    {
        INT, INT2, INT3, INT4,
        UINT, UINT2, UINT3, UINT4,
        FLOAT, FLOAT2, FLOAT3, FLOAT4
    };

    ShaderData() = default;

    void Construct(Type shaderDataType);

    size_t GetCount() const { return m_Count; }
    size_t GetSize() const { return m_Size; }
    unsigned int GetRendererCodeType() const { return m_Type; }

private:
    unsigned int m_Type{ 0 };
    size_t m_Count{ 0 };
    size_t m_Size{ 0 };

};

class BufferLayout
{
public:
    struct BufferElement
    {
        ShaderData shaderData;
        size_t offset{ 0 };
    };

    BufferLayout() = default;
    BufferLayout(std::initializer_list<ShaderData::Type> initList);
    BufferLayout(const std::vector<ShaderData::Type>& shaderDataTypes);

    void Init(const std::vector<ShaderData::Type>& shaderDataTypes);

    const std::vector<BufferElement>& GetElements() const { return m_Elements; }
    size_t GetStride() const { return m_Stride; }

private:
    std::vector<BufferElement> m_Elements;
    size_t m_Stride{ 0 };

};

} // namespace Delta
