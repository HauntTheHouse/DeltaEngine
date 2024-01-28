#pragma once

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

    int GetCount() const { return m_Count; }
    int GetSize() const { return m_Size; }
    unsigned int GetRendererCodeType() const { return m_Type; }

private:
    unsigned int m_Type{ 0 };
    int m_Count{ 0 };
    int m_Size{ 0 };

};

class BufferLayout
{
public:
    struct BufferElement
    {
        ShaderData shaderData;
        int offset{ 0 };
    };

    BufferLayout() = default;
    BufferLayout(std::initializer_list<ShaderData::Type> initList);
    BufferLayout(const std::vector<ShaderData::Type>& shaderDataTypes);

    void Init(const std::vector<ShaderData::Type>& shaderDataTypes);

    const std::vector<BufferElement>& GetElements() const { return m_Elements; }
    int GetStride() const { return m_Stride; }

private:
    std::vector<BufferElement> m_Elements;
    int m_Stride{ 0 };

};

} // namespace Delta
