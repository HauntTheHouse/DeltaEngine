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

    unsigned int GetVerticesCount() const { return m_VerticesCount; }
    int GetIndicesCount() const { return m_IndicesCount; }

private:
    unsigned int m_Id{ 0 };

    unsigned int m_AttributesCount{ 0 };
    int m_VerticesCount{ 0 };
    int m_IndicesCount{ 0 };

};

} // namespace Delta
