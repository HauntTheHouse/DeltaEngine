#include "PCH.hpp"
#include "EngineCore/Rendering/VertexBuffer.hpp"

#include <glad/glad.h>

namespace Delta
{

void VertexBuffer::InitImpl(const void* data, const size_t size, const BufferLayout& layout, const Usage usage)
{
    m_Layout = layout;

    glGenBuffers(1, static_cast<GLuint*>(&m_Id));
    glBindBuffer(GL_ARRAY_BUFFER, static_cast<GLuint>(m_Id));
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(size), data, static_cast<GLenum>(GetRendererCode(usage)));
}

void VertexBuffer::Clear()
{
    glDeleteBuffers(1, static_cast<GLuint*>(&m_Id));
    m_Id = 0;
}

void VertexBuffer::Bind() const
{
    assert(m_Id != 0);
    glBindBuffer(GL_ARRAY_BUFFER, static_cast<GLuint>(m_Id));
}

void VertexBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

unsigned int VertexBuffer::GetRendererCode(Usage usage)
{
    switch (usage)
    {
        case Usage::STATIC: return GL_STATIC_DRAW;
        case Usage::DYNAMIC: return GL_DYNAMIC_DRAW;
        case Usage::STREAM: return GL_STREAM_DRAW;
        default: return GL_NONE;
    }
}

} // namespace Delta
