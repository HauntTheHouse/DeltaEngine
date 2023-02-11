#include "EngineCore/Rendering/VertexBuffer.hpp"

namespace Delta
{

void VertexBuffer::initImpl(const void* aData, const size_t aSize, const BufferLayout& aLayout, const Usage aUsage)
{
}

void VertexBuffer::clear()
{
}

void VertexBuffer::bind() const
{
}

void VertexBuffer::unbind()
{
}

unsigned int VertexBuffer::getRendererCode(Usage aUsage)
{
    return 0;
}

} // namespace Delta
