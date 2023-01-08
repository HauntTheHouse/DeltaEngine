#include "EngineCore/Rendering/OpenGL/IndexBuffer.hpp"

#include <glad/glad.h>

namespace Delta
{

void IndexBuffer::initImpl(const void* aData, const size_t aSize, const VertexBuffer::Usage aUsage)
{
    glGenBuffers(1, static_cast<GLuint*>(&mId));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLuint>(mId));
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, aSize, aData, VertexBuffer::getRendererCode(aUsage));
}

void IndexBuffer::clear()
{
    glDeleteBuffers(1, static_cast<GLuint*>(&mId));
    mId = 0;
}

void IndexBuffer::bind() const
{
    assert(mId != 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLuint>(mId));
}

void IndexBuffer::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

} // namespace Delta
