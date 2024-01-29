#pragma once

#include "BufferLayout.hpp"

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

    template<typename T>
    bool Init(const std::vector<T>& vertices, const BufferLayout& layout, const Usage usage = Usage::STATIC)
    {
        if (m_Id != 0) return false;

        size_t size = vertices.size() * sizeof(T);
        m_VerticesCount = size / layout.GetStride();

        InitImpl(vertices.data(), size, layout, usage);
        return true;
    }
    void Clear();

    void Bind() const;
    static void Unbind();

    const BufferLayout& GetLayout() const { return m_Layout; }
    int GetVerticesCount() const { return m_VerticesCount; }

    static unsigned int GetRendererCode(Usage usage);

private:
    void InitImpl(const void* data, const size_t size, const BufferLayout& layout, const Usage usage);

    unsigned int m_Id{ 0 };
    BufferLayout m_Layout;

    int m_VerticesCount{ 0 };

};

} // namespace Delta
