#pragma once

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

namespace Delta
{

class VertexArray
{
public:
    VertexArray() = default;
    ~VertexArray() = default;
    VertexArray(VertexArray&) = delete;
    VertexArray& operator=(VertexArray&) = delete;

    bool Init();
    void Clear();

    void AddVertexBuffer(const VertexBuffer& vertexBuffer);
    void SetIndexBuffer(const IndexBuffer& indexBuffer);

    void Bind() const;
    static void Unbind();

    size_t GetVerticesCount() const { return m_VerticesCount; }
    size_t GetIndicesCount() const { return m_IndicesCount; }
    IndexBuffer::DataType GetIndexDataType() const { return m_IndexDataType; }

private:
    unsigned int m_Id{ 0 };

    size_t m_AttributesCount{ 0 };
    size_t m_VerticesCount{ 0 };
    size_t m_IndicesCount{ 0 };
    IndexBuffer::DataType m_IndexDataType{};

};

} // namespace Delta
