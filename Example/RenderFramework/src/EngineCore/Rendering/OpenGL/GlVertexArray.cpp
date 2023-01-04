#include "EngineCore/Rendering/OpenGL/GlVertexArray.hpp"

#include <glad/glad.h>

bool GlVertexArray::init()
{
	if (mId != 0) return false;

	glGenVertexArrays(1, &mId);
	return true;
}

void GlVertexArray::clear()
{
	glDeleteVertexArrays(1, &mId);
	mId = 0;
}

void GlVertexArray::addVertexBuffer(const GlVertexBuffer& aVertexBuffer)
{
	bind();
	aVertexBuffer.bind();

	mVerticesCount += aVertexBuffer.getVerticesCount();

	const auto& layout = aVertexBuffer.getLayout();
	for (const auto& element : layout.getElements())
	{
		glEnableVertexAttribArray(mAttributesCount);
		glVertexAttribPointer(mAttributesCount++, element.shaderData.getCount(), element.shaderData.getGlType(), GL_FALSE, layout.getStride(), (const void*)(element.offset));
	}
}

void GlVertexArray::setIndexBuffer(const GlIndexBuffer& aIndexBuffer)
{
	bind();
	aIndexBuffer.bind();

	mIndicesCount = aIndexBuffer.getIndicesCount();
}

void GlVertexArray::bind() const
{
	assert(mId != 0);
	glBindVertexArray(mId);
}

void GlVertexArray::unbind()
{
	glBindVertexArray(0);
}
