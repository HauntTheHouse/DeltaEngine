#pragma once

#include "VertexBuffer.hpp"

namespace Delta
{

class IndexBuffer
{
public:
    IndexBuffer() = default;
    ~IndexBuffer() = default;
    IndexBuffer(IndexBuffer&) = delete;
    IndexBuffer& operator=(IndexBuffer&) = delete;

    template<typename T>
    bool Init(const std::vector<T>& indices, const VertexBuffer::Usage usage = VertexBuffer::Usage::STATIC)
    {
        if (m_Id != 0) return false;

        m_IndicesCount = indices.size();

        InitImpl(indices.data(), m_IndicesCount * sizeof(T), usage);
        return true;
    }
    void Clear();

    void Bind() const;
    static void Unbind();

    int GetIndicesCount() const { return m_IndicesCount; }

private:
    void InitImpl(const void* data, const size_t size, const VertexBuffer::Usage usage);

    unsigned int m_Id{ 0 };
    int m_IndicesCount{ 0 };

};

} // namespace Delta
