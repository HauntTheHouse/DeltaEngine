#include "EngineCore/Rendering/OpenGL/VertexArray.hpp"

#include <glad/glad.h>

namespace Delta
{

bool VertexArray::init()
{
	if (static_cast<GLuint>(mId) != 0) return false;

	glGenVertexArrays(1, static_cast<GLuint*>(&mId));
	return true;
}

void VertexArray::clear()
{
	glDeleteVertexArrays(1, static_cast<GLuint*>(&mId));
	mId = 0;
}

void VertexArray::addVertexBuffer(const VertexBuffer& aVertexBuffer)
{
	bind();
	aVertexBuffer.bind();

	mVerticesCount += aVertexBuffer.getVerticesCount();

	const auto& layout = aVertexBuffer.getLayout();
	for (const auto& element : layout.getElements())
	{
		glEnableVertexAttribArray(static_cast<GLuint>(mAttributesCount));
		glVertexAttribPointer(
			static_cast<GLuint>(mAttributesCount),
			static_cast<GLint>(element.shaderData.getCount()),
			static_cast<GLenum>(element.shaderData.getRendererCodeType()),
			GL_FALSE,
			static_cast<GLsizei>(layout.getStride()),
			reinterpret_cast<const void*>(element.offset));
		mAttributesCount++;
	}
}

void VertexArray::setIndexBuffer(const IndexBuffer& aIndexBuffer)
{
	bind();
	aIndexBuffer.bind();

	mIndicesCount = aIndexBuffer.getIndicesCount();
}

void VertexArray::bind() const
{
	assert(mId != 0);
	glBindVertexArray(static_cast<GLuint>(mId));
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}

} // namespace Delta
