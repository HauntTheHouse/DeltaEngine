#pragma once

#include "GlBufferLayout.hpp"
#include "GlTypes.hpp"

namespace Delta
{

class GlVertexBuffer
{
public:
	enum class Usage
	{
		STATIC,
		DYNAMIC,
		STREAM
	};

	GlVertexBuffer() = default;
	~GlVertexBuffer() = default;
	GlVertexBuffer(GlVertexBuffer&) = delete;
	GlVertexBuffer& operator=(GlVertexBuffer&) = delete;

	template<typename T>
	bool init(const std::vector<T>& aVertices, const GlBufferLayout& aLayout, const Usage aUsage = Usage::STATIC)
	{
		if (mId != 0) return false;

		size_t size = aVertices.size() * sizeof(T);
		mVerticesCount = size / aLayout.getStride();

		initImpl(aVertices.data(), size, aLayout, aUsage);
		return true;
	}
	void clear();

	void bind() const;
	static void unbind();

	const GlBufferLayout& getLayout() const { return mLayout; }
	GLsizei getVerticesCount() const { return mVerticesCount; }

	constexpr static GLenum castToGLenum(Usage aUsage);

private:
	void initImpl(const void* aData, const size_t aSize, const GlBufferLayout& aLayout, const Usage aUsage);

	GLuint mId{ 0 };
	GlBufferLayout mLayout;

	GLsizei mVerticesCount{ 0 };

};

} // namespace Delta
