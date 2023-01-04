#pragma once

#include "GlVertexBuffer.hpp"

class GlIndexBuffer
{
public:
	GlIndexBuffer() = default;
	~GlIndexBuffer() = default;
	GlIndexBuffer(GlIndexBuffer&) = delete;
	GlIndexBuffer& operator=(GlIndexBuffer&) = delete;

	template<typename T>
	bool init(const std::vector<T>& aIndices, const GlVertexBuffer::Usage aUsage = GlVertexBuffer::Usage::STATIC)
	{
		if (mId != 0) return false;

		mIndicesCount = aIndices.size();

		initImpl(aIndices.data(), mIndicesCount * sizeof(T), aUsage);
		return true;
	}
	void clear();

	void bind() const;
	static void unbind();

	GLsizei getIndicesCount() const { return mIndicesCount; }

private:
	void initImpl(const void* aData, const size_t aSize, const GlVertexBuffer::Usage aUsage);

	GLuint mId{ 0 };
	GLsizei mIndicesCount{ 0 };
};
