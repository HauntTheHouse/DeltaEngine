#pragma once

#include "GfxEnums.hpp"
#include "BufferLayout.hpp"
#include "DeltaEngine/Utils.hpp"

namespace Delta
{

class VertexBuffer
{
public:
    VertexBuffer() = default;
    ~VertexBuffer() = default;
    VertexBuffer(VertexBuffer&) = delete;
    VertexBuffer& operator=(VertexBuffer&) = delete;

    template<typename Container>
    bool Init(Container&& vertices, const BufferLayout& layout, const BufferUsage usage = BufferUsage::STATIC)
    {
        return Init(vertices.data(), Utils::getSizeInBytes(vertices), layout, usage);
    }
    bool Init(const void* data, const size_t size, const BufferLayout& layout, const BufferUsage usage);
    void Clear();

    void Bind() const;
    static void Unbind();

    const BufferLayout& GetLayout() const { return m_Layout; }
    size_t GetVerticesCount() const { return m_VerticesCount; }

private:
    unsigned int m_Id{ 0 };
    BufferLayout m_Layout;

    size_t m_VerticesCount{ 0 };

};

} // namespace Delta
