#pragma once

#include "GlTypes.hpp"

namespace Delta
{

class GlShaderData
{
public:
	enum class Type
	{
		INT, INT2, INT3, INT4,
		UINT, UINT2, UINT3, UINT4,
		FLOAT, FLOAT2, FLOAT3, FLOAT4
	};

	GlShaderData() = default;

	void construct(Type aShaderDataType);

	GLenum getGlType() const { return type; }
	GLint getCount() const { return count; }
	GLint getSize() const { return size; }

private:
	GLenum type{ 0 };
	GLint count{ 0 };
	GLint size{ 0 };

};

class GlBufferLayout
{
public:
	struct BufferElement
	{
		GlShaderData shaderData;
		GLint offset{ 0 };
	};

	GlBufferLayout() = default;
	GlBufferLayout(const std::vector<GlShaderData::Type>& aShaderDataTypes);

	void init(const std::vector<GlShaderData::Type>& aShaderDataTypes);

	const std::vector<BufferElement>& getElements() const { return mElements; }
	GLsizei getStride() const { return mStride; }

private:

	std::vector<BufferElement> mElements;
	GLsizei mStride{ 0 };
};

} // namespace Delta
