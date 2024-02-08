#include "DeltaEngine/Render/VertexArray.hpp"

#include "DeltaEngine/Log.hpp"
#include <glad/glad.h>

namespace Delta
{

bool VertexArray::Init()
{
    if (static_cast<GLuint>(m_Id) != 0) return false;

    glGenVertexArrays(1, static_cast<GLuint*>(&m_Id));
    return true;
}

void VertexArray::Clear()
{
    glDeleteVertexArrays(1, static_cast<GLuint*>(&m_Id));
    m_Id = 0;
}

void VertexArray::AddVertexBuffer(const VertexBuffer& vertexBuffer)
{
    Bind();
    vertexBuffer.Bind();

    m_VerticesCount += vertexBuffer.GetVerticesCount();

    const auto& layout = vertexBuffer.GetLayout();
    for (const auto& element : layout.GetElements())
    {
        glEnableVertexAttribArray(static_cast<GLuint>(m_AttributesCount));
        glVertexAttribPointer(
            static_cast<GLuint>(m_AttributesCount),
            static_cast<GLint>(element.shaderData.GetCount()),
            static_cast<GLenum>(element.shaderData.GetRendererCodeType()),
            GL_FALSE,
            static_cast<GLsizei>(layout.GetStride()),
            reinterpret_cast<const void*>(element.offset));
        m_AttributesCount++;
    }
}

void VertexArray::SetIndexBuffer(const IndexBuffer& indexBuffer)
{
    Bind();
    indexBuffer.Bind();

    m_IndicesCount = indexBuffer.GetIndicesCount();
    m_IndexDataType = indexBuffer.GetDataType();
}

void VertexArray::Bind() const
{
    ASSERT(m_Id != 0);
    glBindVertexArray(static_cast<GLuint>(m_Id));
}

void VertexArray::Unbind()
{
    glBindVertexArray(0);
}

} // namespace Delta
