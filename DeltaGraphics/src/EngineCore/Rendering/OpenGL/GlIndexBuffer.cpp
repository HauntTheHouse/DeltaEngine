#include "EngineCore/Rendering/OpenGL/GlIndexBuffer.hpp"

#include <glad/glad.h>

namespace Delta
{

void GlIndexBuffer::initImpl(const void* aData, const size_t aSize, const GlVertexBuffer::Usage aUsage)
{
    glGenBuffers(1, &mId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, aSize, aData, GlVertexBuffer::castToGLenum(aUsage));
}

void GlIndexBuffer::clear()
{
    glDeleteBuffers(1, &mId);
    mId = 0;
}

void GlIndexBuffer::bind() const
{
    assert(mId != 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId);
}

void GlIndexBuffer::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

} // namespace Delta
