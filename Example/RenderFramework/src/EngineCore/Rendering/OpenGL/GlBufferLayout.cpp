#include "EngineCore/Rendering/OpenGL/GlBufferLayout.hpp"

#include <glad/glad.h>

void GlShaderData::construct(Type aShaderDataType)
{
	switch (aShaderDataType)
	{
	case Type::INT:
	case Type::INT2:
	case Type::INT3:
	case Type::INT4:
		type = GL_INT;
		count = ((GLint)aShaderDataType - (GLint)Type::INT + 1);
		size = sizeof(GLint) * count;
		break;
	case Type::UINT:
	case Type::UINT2:
	case Type::UINT3:
	case Type::UINT4:
		type = GL_UNSIGNED_INT;
		count = ((GLint)aShaderDataType - (GLint)Type::UINT + 1);
		size = sizeof(GLuint) * count;
		break;
	case Type::FLOAT:
	case Type::FLOAT2:
	case Type::FLOAT3:
	case Type::FLOAT4:
		type = GL_FLOAT;
		count = ((GLint)aShaderDataType - (GLint)Type::FLOAT + 1);
		size = sizeof(GLfloat) * count;
		break;
	}
}

GlBufferLayout::GlBufferLayout(const std::vector<GlShaderData::Type>& aShaderDataTypes)
{
	init(aShaderDataTypes);
}

void GlBufferLayout::init(const std::vector<GlShaderData::Type>& aShaderDataTypes)
{
	mElements.reserve(aShaderDataTypes.size());

	GLint offset = 0;
	for (const auto& shaderDataType : aShaderDataTypes)
	{
		BufferElement element;
		element.shaderData.construct(shaderDataType);
		element.offset = offset;

		offset += element.shaderData.getSize();
		mStride += element.shaderData.getSize();

		mElements.push_back(std::move(element));
	}
}
