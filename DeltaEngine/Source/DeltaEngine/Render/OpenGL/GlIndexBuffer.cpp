#include "DeltaEngine/Render/IndexBuffer.hpp"

#include <DeltaEngine/Log.hpp>
#include <glad/glad.h>

namespace Delta
{

namespace
{
    size_t getSize(const IndexBufferType dataType)
    {
        switch (dataType)
        {
        case IndexBufferType::UNSIGNED_BYTE: return 1;
        case IndexBufferType::UNSIGNED_SHORT: return 2;
        case IndexBufferType::UNSIGNED_INT: return 4;
        default: return 0;
        }
    }
}

bool IndexBuffer::Init(const void* data, const size_t size, const IndexBufferType dataType, const BufferUsage usage)
{
    if (m_Id != 0) return false;
    m_IndicesCount = size / getSize(dataType);
    m_DataType = dataType;

    glGenBuffers(1, static_cast<GLuint*>(&m_Id));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLuint>(m_Id));
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, static_cast<GLenum>(toNativeType(usage)));

    return true;
}

void IndexBuffer::Clear()
{
    glDeleteBuffers(1, static_cast<GLuint*>(&m_Id));
    m_Id = 0;
}

void IndexBuffer::Bind() const
{
    ASSERT(m_Id != 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLuint>(m_Id));
}

void IndexBuffer::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

} // namespace Delta
