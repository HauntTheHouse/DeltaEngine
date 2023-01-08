#pragma once

namespace Delta
{

class ShaderData
{
public:
	enum class Type
	{
		INT, INT2, INT3, INT4,
		UINT, UINT2, UINT3, UINT4,
		FLOAT, FLOAT2, FLOAT3, FLOAT4
	};

	ShaderData() = default;

	void construct(Type aShaderDataType);

	unsigned int getRendererCodeType() const { return type; }
	int getCount() const { return count; }
	int getSize() const { return size; }

private:
	unsigned int type{ 0 };
	int count{ 0 };
	int size{ 0 };

};

class BufferLayout
{
public:
	struct BufferElement
	{
		ShaderData shaderData;
		int offset{ 0 };
	};

	BufferLayout() = default;
	BufferLayout(const std::vector<ShaderData::Type>& aShaderDataTypes);

	void init(const std::vector<ShaderData::Type>& aShaderDataTypes);

	const std::vector<BufferElement>& getElements() const { return mElements; }
	int getStride() const { return mStride; }

private:

	std::vector<BufferElement> mElements;
	int mStride{ 0 };
};

} // namespace Delta
