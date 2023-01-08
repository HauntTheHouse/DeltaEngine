#include "EngineCore/Rendering/OpenGL/BufferLayout.hpp"

#include <glad/glad.h>

namespace Delta
{

void ShaderData::construct(Type aShaderDataType)
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

BufferLayout::BufferLayout(const std::vector<ShaderData::Type>& aShaderDataTypes)
{
	init(aShaderDataTypes);
}

void BufferLayout::init(const std::vector<ShaderData::Type>& aShaderDataTypes)
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

} // namespace Delta
