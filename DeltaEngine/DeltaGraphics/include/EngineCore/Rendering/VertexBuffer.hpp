#pragma once

#include "BufferLayout.hpp"
#include "EngineCore/Utils.hpp"

namespace Delta
{

class VertexBuffer
{
public:
    enum class Usage
    {
        STATIC,
        DYNAMIC,
        STREAM
    };

    VertexBuffer() = default;
    ~VertexBuffer() = default;
    VertexBuffer(VertexBuffer&) = delete;
    VertexBuffer& operator=(VertexBuffer&) = delete;

    template<typename Container>
    bool Init(Container&& vertices, const BufferLayout& layout, const Usage usage = Usage::STATIC)
    {
        return Init(vertices.data(), Utils::getSizeInBytes(vertices), layout, usage);
    }
    bool Init(const void* data, const size_t size, const BufferLayout& layout, const Usage usage);
    void Clear();

    void Bind() const;
    static void Unbind();

    const BufferLayout& GetLayout() const { return m_Layout; }
    size_t GetVerticesCount() const { return m_VerticesCount; }

    static unsigned int GetRendererCode(Usage usage);

private:
    unsigned int m_Id{ 0 };
    BufferLayout m_Layout;

    size_t m_VerticesCount{ 0 };

};

} // namespace Delta
