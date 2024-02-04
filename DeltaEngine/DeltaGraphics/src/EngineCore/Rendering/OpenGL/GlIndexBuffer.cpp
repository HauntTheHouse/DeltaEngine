#include "EngineCore/Rendering/IndexBuffer.hpp"

#include <EngineCore/Log.hpp>
#include <glad/glad.h>

namespace Delta
{

namespace
{
    size_t getSize(const IndexBuffer::DataType dataType)
    {
        switch (dataType)
        {
        case IndexBuffer::DataType::BYTE:
        case IndexBuffer::DataType::UNSIGNED_BYTE: return 1;
        case IndexBuffer::DataType::SHORT:
        case IndexBuffer::DataType::UNSIGNED_SHORT: return 2;
        case IndexBuffer::DataType::INT:
        case IndexBuffer::DataType::UNSIGNED_INT: return 4;
        default: return GL_NONE;
        }
    }
}

bool IndexBuffer::Init(const void* data, const size_t size, const DataType dataType, const VertexBuffer::Usage usage)
{
    if (m_Id != 0) return false;
    m_IndicesCount = size / getSize(dataType);
    m_DataType = dataType;

    glGenBuffers(1, static_cast<GLuint*>(&m_Id));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLuint>(m_Id));
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, VertexBuffer::GetRendererCode(usage));

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
