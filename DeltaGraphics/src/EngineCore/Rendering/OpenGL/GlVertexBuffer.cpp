#include "EngineCore/Rendering/OpenGL/GlVertexBuffer.hpp"

#include <glad/glad.h>

namespace Delta
{

void GlVertexBuffer::initImpl(const void* aData, const size_t aSize, const GlBufferLayout& aLayout, const Usage aUsage)
{
	mLayout = aLayout;

	glGenBuffers(1, &mId);
	glBindBuffer(GL_ARRAY_BUFFER, mId);
	glBufferData(GL_ARRAY_BUFFER, aSize, aData, castToGLenum(aUsage));
}

void GlVertexBuffer::clear()
{
	glDeleteBuffers(1, &mId);
	mId = 0;
}

void GlVertexBuffer::bind() const
{
	assert(mId != 0);
	glBindBuffer(GL_ARRAY_BUFFER, mId);
}

void GlVertexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

constexpr GLenum GlVertexBuffer::castToGLenum(Usage aUsage)
{
	switch (aUsage)
	{
	case Usage::STATIC: return GL_STATIC_DRAW;
	case Usage::DYNAMIC: return GL_DYNAMIC_DRAW;
	case Usage::STREAM: return GL_STREAM_DRAW;
	default: return GL_NONE;
	}
}

} // namespace Delta
