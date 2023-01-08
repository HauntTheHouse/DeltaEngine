#include "EngineCore/Rendering/OpenGL/VertexBuffer.hpp"

#include <glad/glad.h>

namespace Delta
{

void VertexBuffer::initImpl(const void* aData, const size_t aSize, const BufferLayout& aLayout, const Usage aUsage)
{
	mLayout = aLayout;

	glGenBuffers(1, static_cast<GLuint*>(&mId));
	glBindBuffer(GL_ARRAY_BUFFER, static_cast<GLuint>(mId));
	glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(aSize), aData, static_cast<GLenum>(getRendererCode(aUsage)));
}

void VertexBuffer::clear()
{
	glDeleteBuffers(1, static_cast<GLuint*>(&mId));
	mId = 0;
}

void VertexBuffer::bind() const
{
	assert(mId != 0);
	glBindBuffer(GL_ARRAY_BUFFER, static_cast<GLuint>(mId));
}

void VertexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

constexpr unsigned int VertexBuffer::getRendererCode(Usage aUsage)
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
