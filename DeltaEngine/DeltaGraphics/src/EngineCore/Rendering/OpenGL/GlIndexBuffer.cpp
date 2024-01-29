#include "PCH.hpp"
#include "EngineCore/Rendering/IndexBuffer.hpp"

#include <glad/glad.h>

namespace Delta
{

void IndexBuffer::InitImpl(const void* data, const size_t size, const VertexBuffer::Usage usage)
{
    glGenBuffers(1, static_cast<GLuint*>(&m_Id));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLuint>(m_Id));
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, VertexBuffer::GetRendererCode(usage));
}

void IndexBuffer::Clear()
{
    glDeleteBuffers(1, static_cast<GLuint*>(&m_Id));
    m_Id = 0;
}

void IndexBuffer::Bind() const
{
    assert(m_Id != 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLuint>(m_Id));
}

void IndexBuffer::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

} // namespace Delta
